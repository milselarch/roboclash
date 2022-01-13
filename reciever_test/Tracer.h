/*
const int LEFT_IR_PIN = A7;
const int RIGHT_IR_PIN = A6;

const int TRACE_SPEED = 50;
const int TRACE_STEER = 50;

void trace_right_sensor_left() {
  int val = analogRead(RIGHT_IR_PIN);
  float bias = (val - 900) / 100.0;
  // bias = max(1, ) 
  driver.drive(TRACE_SPEED, bias * TRACE_STEER);
}
*/
