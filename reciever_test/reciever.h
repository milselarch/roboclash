#include <PPMReader.h>;

const byte INTERRUPT_PIN = 3;
const byte NUM_CHANNELS = 8;

class Reciever {
public:
  int ch1Value;
  int ch2Value;
  int ch3Value;
  int ch4Value;
  int ch5Value;
  int ch6Value;
  int ch7Value;
  int ch8Value;
  int cycles = 0;

  PPMReader *ppm;

  Reciever() {
    this->ppm = new PPMReader(INTERRUPT_PIN, NUM_CHANNELS);
  }

  // Boolean to represent switch value
  // Read the number of a specified channel and convert to the range provided.
  // If the channel is off, return the default value
  int readChannel(
    int channelNumber, int minLimit, int maxLimit, int defaultValue
  ) {
    int ch = ppm->latestValidChannelValue(channelNumber, 0);
    if (ch < 100) return defaultValue;
    return map(ch, 1000, 2000, minLimit, maxLimit);
  }
  
  // Read the switch channel and return a boolean value
  int readSwitch(byte channelInput, bool defaultValue){
    int intDefaultValue = (defaultValue)? 100: 0;
    int ch = readChannel(channelInput, 0, 100, intDefaultValue);
    if (ch == 0) { return 0; }
    else if (ch > 0) {return 1; }
    else { return -1; }
  }

  void show() {
    for (int k=1; k<=NUM_CHANNELS; k++) {
      int read_val = this->readChannel(k, -100, 100, 0);
      Serial.print("CH");
      Serial.print(k);
      Serial.print(": ");
      Serial.println(read_val);
    };
  };

  void read_values() {
    this->cycles += 1;
    this->ch1Value = this->readChannel(1, -100, 100, 0);
    this->ch2Value = this->readChannel(2, -100, 100, 0);
    this->ch3Value = this->readChannel(3, -100, 100, 0);
    this->ch4Value = this->readChannel(4, -100, 100, 0);
    this->ch5Value = this->readChannel(5, -100, 100, 0);
    this->ch6Value = this->readChannel(6, -100, 100, 0);
    this->ch7Value = this->readChannel(7, -100, 100, 0);
    this->ch8Value = this->readChannel(8, -100, 100, 0);
  }

  void show_recorded() {
    Serial.print("cycles: ");
    Serial.print(this->cycles);
    Serial.print(" Ch1: ");
    Serial.print(this->ch1Value);
    Serial.print(" | Ch2: ");
    Serial.print(this->ch2Value);
    Serial.print(" | Ch3: ");
    Serial.print(this->ch3Value);
    Serial.print(" | Ch4: ");
    Serial.print(this->ch4Value);
    Serial.print(" | Ch5: ");
    Serial.print(this->ch5Value);
    Serial.print(" | Ch6: ");
    Serial.print(this->ch6Value);  
    Serial.print(" | Ch7: ");
    Serial.print(this->ch7Value);
    Serial.print(" | Ch8: ");
    Serial.print(this->ch8Value);  
    Serial.println("");
  }

  int left_joystick_x() {
    return this->ch4Value;
  }
  int left_joystick_y() {
    return this->ch2Value;
  }
  int right_joystick_x() {
    return this->ch1Value;
  }
  int right_joystick_y() {
    return this->ch3Value;
  }

  bool use_base_control() {
    if (this->ch5Value == -100) {
      return true;
    } else {
      return false;
    }
  }

  bool grab_on() {
    if (this->ch8Value == -100) {
      return false;
    } else {
      return true;
    }
  }

  int switch1() {
    int reading = this->ch5Value;
    if (reading == -100) {
      return -1;
    } else if (reading == 100) {
      return 1;
    } else {
      return 0;
    }
  }

  int switch2() {
    int reading = this->ch6Value;
    if (reading == -100) {
      return -1;
    } else if (reading == 100) {
      return 1;
    } else {
      return 0;
    }
  }

  int switch3() {
    int reading = this->ch7Value;
    if (reading == -100) {
      return -1;
    } else if (reading == 100) {
      return 1;
    } else {
      return 0;
    }
  }
};
