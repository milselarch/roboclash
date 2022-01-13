class MotorDriver {
private:
  /*
  const int left_back_pin1 = 5;
  const int left_back_pin2 = 4;
  const int right_back_pin1 = 7;
  const int right_back_pin2 = 6;

  const int left_front_pin1 = 8;
  const int left_front_pin2 = 9;
  const int right_front_pin1 = 11;
  const int right_front_pin2 = 10;
  */

  const int left_front_pin1 = A0;
  const int left_front_pin2 = A1;
  const int right_front_pin1 = A3;
  const int right_front_pin2 = A2;
  
  const int right_back_pin1 = A5;
  const int right_back_pin2 = A4;
  const int left_back_pin1 = 5;
  const int left_back_pin2 = 4;
  
public:
  MotorDriver() {
    pinMode(left_back_pin1, OUTPUT);
    pinMode(left_back_pin2, OUTPUT);
    pinMode(right_back_pin1, OUTPUT);
    pinMode(right_back_pin2, OUTPUT);
    
    pinMode(left_front_pin1, OUTPUT);
    pinMode(left_front_pin2, OUTPUT);
    pinMode(right_front_pin1, OUTPUT);
    pinMode(right_front_pin2, OUTPUT);
  }

  void drive(int forward_speed, int steer) {
    float left_speed = forward_speed + steer;
    float right_speed = forward_speed - steer;

    // Serial.print("WEIGHTAGE ");
    // Serial.println(right_weightage);
    // Serial.print("FORWARD SPEED ");
    // Serial.println(forward_speed);

    // Serial.print("LSPEED ");
    // Serial.println(left_speed);
    // Serial.print("RSPEED ");
    // Serial.println(right_speed);

    this->wheel_speed(left_speed, true, true);
    this->wheel_speed(left_speed, true, false);
    this->wheel_speed(right_speed, false, true);
    this->wheel_speed(right_speed, false, false);
  }

  void wheel_speed(int val, bool left, bool front) {
    int pin1, pin2;
    
    if (left) {
      if (front) {
        pin1 = this->left_front_pin1;
        pin2 = this->left_front_pin2;
      } else {
        pin1 = this->left_back_pin1;
        pin2 = this->left_back_pin2;
      }
    } else {
      if (front) {
        pin1 = this->right_front_pin1;
        pin2 = this->right_front_pin2;
      } else {
        pin1 = this->right_back_pin1;
        pin2 = this->right_back_pin2;
      }
    }

    this->set_speed(val, pin1, pin2);
  }

  void set_speed(int val, int pin1, int pin2) {
    int motor_speed = abs(val * 2.55);
    motor_speed = min(motor_speed, 255);
    
    // Serial.print("SPEED ");
    // Serial.println(motor_speed);
    
    if (val >= 0) {
      analogWrite(pin1, motor_speed);
      analogWrite(pin2, 0);
    } else {
      analogWrite(pin2, motor_speed);
      analogWrite(pin1, 0);
    }
  }
  
  void brake() {
    analogWrite(left_back_pin1, 0);
    analogWrite(left_back_pin2, 0);
    analogWrite(right_back_pin1, 0);
    analogWrite(right_back_pin2, 0);
  }
};
