#include "MotorDriver.h"

const int LEFT_IR_PIN = A7;
const int RIGHT_IR_PIN = A6;

const int TRACE_SPEED = 50;
const int TRACE_STEER = 50;
const float MAX_THRES = 1024;
const float MIN_THRES = 800;

class LineTracer {
public:
  MotorDriver *driver;

  LineTracer (MotorDriver *base_driver) {
    this->driver = base_driver;
  }

  void trace_right_sensor_left() {
    float darkness = this->get_darkness(RIGHT_IR_PIN);
    float steering = darkness * TRACE_STEER;
    this->driver->drive(TRACE_SPEED, steering);
  }

  void trace_right_sensor_right() {
    float darkness = this->get_darkness(LEFT_IR_PIN);
    float steering = darkness * TRACE_STEER;
    this->driver->drive(TRACE_SPEED, -steering);
  }

  void turn_left_to_black_line(int sensor) {
    
  }

  void cross_black_line() {
    this->driver->drive(TRACE_SPEED, 0);
    const int BRIGHT_THRES = 0.2;
    const int DARK_THRES = 0.8;
    bool left_crossed, right_crossed;
    
    left_crossed = false;
    right_crossed = false;
    
    while (true) {
      float left_darkness = get_darkness(LEFT_IR_PIN);
      float right_darkness = get_darkness(RIGHT_IR_PIN);

      if (left_darkness > DARK_THRES) {
        left_crossed = true; 
      } if (right_darkness > DARK_THRES) {
        right_crossed = true;
      }

      if (left_crossed && right_crossed) { break; }
      delay(20);
    }

    left_crossed = false;
    right_crossed = false;

    while (true) {
      float left_darkness = get_darkness(LEFT_IR_PIN);
      float right_darkness = get_darkness(RIGHT_IR_PIN);

      if (left_darkness < BRIGHT_THRES) {
        left_crossed = true; 
      } if (right_darkness < BRIGHT_THRES) {
        right_crossed = true;
      }

      if (left_crossed && right_crossed) { break; }
      delay(20);
    }

    this->driver->drive(0, 0);
  }

  float remap(int val) {
    val = min(max(val, MIN_THRES), MAX_THRES);
    val = (val - MIN_THRES) / (MAX_THRES - MIN_THRES);
    return val;
  }

  float get_darkness(int pin_no) {
    int val = analogRead(pin_no);
    float darkness = this->remap(val);
    return darkness;
  }
};

/*
void trace_right_sensor_left() {
  int val = analogRead(RIGHT_IR_PIN);
  float bias = (val - 900) / 100.0;
  // bias = max(1, ) 
  driver.drive(TRACE_SPEED, bias * TRACE_STEER);
}
*/
