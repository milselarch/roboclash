/*
  Arduino FS-I6X Demo
  fsi6x-arduino-uno.ino
  Read output ports from FS-IA6B receiver module
  Display values on Serial Monitor
  
  Channel functions by Ricardo Paiva - https://gist.github.com/werneckpaiva/
  
  DroneBot Workshop 2021
  https://dronebotworkshop.com
*/

#include <EEPROM.h>
#include "RobotArm.h"
#include "MotorDriver.h"
#include "reciever.h"
#include "Tracer.h"

const float BASE_SPEED = 2.5;
const float ARM_SPEED = 0.5;

Reciever reciever;
MotorDriver driver;
RobotArm *robot_arm;

int last_command = 0;

void setup(){
  // Set up serial monitor
  Serial.begin(115200);
  Serial.println("RESET");
  robot_arm = new RobotArm();
  last_command = EEPROM[0];

  pinMode(12, INPUT); // push button
  
  Serial.print("last_command ");
  Serial.println(last_command);
  
  // base_servo.attach(9);
  // driver.forward();
  // delay(400);
  // driver.brake();
}
  
void loop() { 
  // Print to Serial Monitor
  reciever.read_values();
  // reciever.show_recorded();

  /*
  Serial.print("Ch1: ");
  Serial.print(reciever.ch1Value);
  Serial.print(" | Ch2: ");
  Serial.print(reciever.ch2Value);
  Serial.print(" | Ch3: ");
  Serial.print(reciever.ch3Value);
  Serial.print(" | Ch4: ");
  Serial.print(reciever.ch4Value);
  Serial.print(" | Ch5: ");
  Serial.print(reciever.ch5Value);
  Serial.print(" | Ch6: ");
  Serial.println(reciever.ch6Value);
  */

  // Serial.print("JOYSTICK Y: ");
  // Serial.println(reciever.left_joystick_y());
  
  // driver.set_speed(reciever.left_joystick_y(), 4, 5);
  driver.drive(
    reciever.left_joystick_y(), reciever.left_joystick_x()
  );

  int right_joystick_x = reciever.right_joystick_x();
  int right_joystick_y = reciever.right_joystick_y();
  bool use_base_control = reciever.use_base_control();
  bool gripper_on = reciever.grab_on();
  
  // Serial.print("USE BASE CONTROL: ");
  // Serial.println(use_base_control);
  
  /*
  Serial.print("right_joystick_x ");
  Serial.println(right_joystick_x);
  Serial.print("base_rotate_speed ");
  Serial.println(base_rotate_speed);
  */

  float base_rotate_speed = 0;
  float left_arm_motor_speed = 0;
  float right_arm_motor_speed = 0;

  if (right_joystick_x > 40) {
    left_arm_motor_speed = ARM_SPEED;
  } else if (right_joystick_x < -40) {
    left_arm_motor_speed = -ARM_SPEED;
  }

  if (right_joystick_y > 60) {
    right_arm_motor_speed = ARM_SPEED;
  } else if (right_joystick_y < -60) {
    right_arm_motor_speed = -ARM_SPEED;
  }

  // Serial.print("GRIPPER ");
  // Serial.println(gripper_on);

  if (gripper_on) {
    robot_arm->activate_gripper();
  } else {
    robot_arm->deactivate_gripper();
  }

  robot_arm->rotate_base(base_rotate_speed);
  robot_arm->rotate_left_motor(left_arm_motor_speed);
  robot_arm->rotate_right_motor(right_arm_motor_speed);

  int command = 0;
  
  if ((reciever.switch2() == 1) && (reciever.switch3() == -1)) {
    // Serial.println("LEFT");
    command = -1;
  } else if ((reciever.switch2() == -1) && (reciever.switch3() == 1)) {
    // Serial.println("RIGHT");
    command = 1;
  }

  if ((command != last_command) && (command != 0)) {
    last_command = command;
    EEPROM.write(0, last_command);
    Serial.print("LOG ");
    Serial.print(command);
    Serial.print(" CYCLES ");
    Serial.println(reciever.cycles);
  };

  int pressed = digitalRead(12);
  Serial.print("PRESSED ");
  Serial.println(pressed);

  if (pressed == 1) {
    Serial.print("MOVING ");
    Serial.println(last_command);
    
    delay(100);
    int fast = 100;
    int slow = 20;

    if (abs(last_command) == 1) {
      driver.drive(100, -12);
      delay(2500); 
    
      if (last_command == 1) {
        driver.drive(0, fast);
        delay(600);
        driver.drive(0, slow);
        delay(300);
      } else if (last_command == -1) {
        // left
        driver.drive(0, -fast);
        delay(700);
        driver.drive(0, -slow);
        delay(300);
      }

      driver.drive(100, 0);
      delay(1000); 
    }
    
    driver.drive(0, 0);
  }

  /*
  if (reciever.switch2() == 0) {
     if (reciever.switch3() == -1) {
        trace_right_sensor_left();
     }
  }
  */

  delay(10);
}
