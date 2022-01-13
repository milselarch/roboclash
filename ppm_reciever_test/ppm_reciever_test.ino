#include <PPMReader.h>;

const byte INTERRUPT_PIN = 3;
const byte NUM_CHANNELS = 8;
unsigned int cycles = 0;


PPMReader ppm(INTERRUPT_PIN, NUM_CHANNELS);

int readChannel(int channelNumber) {
  int read_value = ppm.latestValidChannelValue(channelNumber, 0);
  int adj_value = read_value - 1500;
  adj_value = map(adj_value, -500, 500, -255, 255);
  // adj_value = map(adj_value)
  return adj_value;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("CYCLE NO = ");
  Serial.println(cycles);
  
  for (int k=1; k<=NUM_CHANNELS; k++) {
    int read_val = readChannel(k);
    Serial.print("CH");
    Serial.print(k);
    Serial.print(": ");
    Serial.println(read_val);
  }
  
  delay(100);
  cycles += 1;
}
