#include <Servo.h>;

Servo gripper_servo;
Servo base_servo;
Servo left_servo;
Servo right_servo;
Servo box_servo;

class RobotArm {
public:
  unsigned int gripper_pin = 7;
  unsigned int base_pin = 9;
  unsigned int left_pin = 10;
  unsigned int right_pin = 11;

  unsigned int box_pin = 13;

  float base_pos = 90;
  float left_pos = 80;
  float right_pos = 135;
  float gripper_pos = 1;

  RobotArm() {
    // pinMode(base_pin, OUTPUT);
    // pinMode(left_pin, OUTPUT);
    // pinMode(right_pin, OUTPUT);
    box_servo.attach(this->box_pin);

    gripper_servo.attach(this->gripper_pin);
    base_servo.attach(this->base_pin);
    left_servo.attach(this->left_pin);
    right_servo.attach(this->right_pin);

    this->neutral_box();
    this->deactivate_gripper();
    base_servo.write(base_pos);
    left_servo.write(left_pos);
    right_servo.write(right_pos);
  }

  void neutral_box() {
    box_servo.write(89);
  }

  void deploy_box() {
    box_servo.write(180);
  }

  void retract_box() {
    box_servo.write(0);
  }

  void set_base_pos(float angle) {
    angle = max(min(angle, 180), 0);
    
    if (angle != this->base_pos) {
      base_servo.write(int(angle));
      this->base_pos = angle;
    }

    // Serial.print("BASE SERVO ");
    // Serial.println(angle);
  }

  void set_left_pos(float angle) {
    angle = max(min(angle, 167), 80);
    
    if (angle != this->left_pos) {
      left_servo.write(int(angle));
      this->left_pos = angle;
    }

    Serial.print("LEFT SERVO ");
    Serial.println(angle);
  }

  void set_right_pos(float angle) {
    angle = max(min(angle, 135), 55);
    
    if (angle != this->right_pos) {
      right_servo.write(int(angle));
      this->right_pos = angle;
    }

    Serial.print("RIGHT SERVO ");
    Serial.println(angle);
  }

  void rotate_base(float degree) {
    float new_angle = this->base_pos + degree;
    // new_angle = max(min(new_angle, 180), 0);
    this->set_base_pos(new_angle);
  }

  void rotate_left_motor(float degree) {
    float new_angle = this->left_pos + degree;
    // new_angle = max(min(new_angle, 180), 0);
    this->set_left_pos(new_angle);
  }

  void rotate_right_motor(float degree) {
    float new_angle = this->right_pos + degree;
    // new_angle = max(min(new_angle, 180), 0);
    this->set_right_pos(new_angle);
  }

  void activate_gripper() {
    const int angle = 45;
    if (this->gripper_pos != angle) {
      this->gripper_pos = angle;
      gripper_servo.write(angle);
    }
  }
  void deactivate_gripper() {
   const int angle = 0;
    if (this->gripper_pos != angle) {
      this->gripper_pos = angle;
      gripper_servo.write(angle);
    }
  }

  void set_pos(int left_pos, int right_pos, int base_pos) {
    return;
  }
};
