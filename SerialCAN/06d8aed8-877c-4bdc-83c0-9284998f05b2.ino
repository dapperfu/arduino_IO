
unsigned long BAUD = 115200;
unsigned long DELAY = 1000;
char BUILD_UUID[] = "06d8aed8-877c-4bdc-83c0-9284998f05b2";

char ARBITRATION_ID = 0x0;
unsigned long time = 0b0;
unsigned char counter = 0;

// Arduino Setup
void setup() {
  Serial.begin(BAUD);
  Serial.print("Build UUID: ");
  Serial.println(BUILD_UUID);
    // Start of frame
  Serial.write(0xAA);
// Timestamp
  Serial.write(0x00);
  Serial.write(0x00);
  Serial.write(0x00);
  Serial.write(0x00);
// DLC
  Serial.write(0x00);
// Arbitration ID
  Serial.write(0x00);
  Serial.write(0x00);
  Serial.write(0x00);
  Serial.write(0xFF);
// End of frame
  Serial.write(0xBB);
  return; 
}

// Arduino Main Loop
void loop() {
   time = millis();
// Start of frame
  Serial.write(0xAA);
// Timestamp
for(char shift=0;shift<32;shift+=8) {
  Serial.write((unsigned long)time>>shift&0b11111111);
}
// DLC
  Serial.write(0x04);
// Arbitration ID
ARBITRATION_ID=0xFF;
for(char shift=0;shift<32;shift+=8) {
  Serial.write(((unsigned long)ARBITRATION_ID>>shift)&0b11111111);
}
// Payload

for(char shift=0;shift<32;shift+=8) {
  Serial.write((unsigned long)time>>shift&0b11111111);
}
  Serial.write(0xBB);
  
  
   time = millis();
// Start of frame
  Serial.write(0xAA);
// Timestamp
for(char shift=0;shift<32;shift+=8) {
  Serial.write((unsigned long)time>>shift&0b11111111);
}
// DLC
  Serial.write(0x04);
// Arbitration ID
ARBITRATION_ID=0xEE;
for(char shift=0;shift<32;shift+=8) {
  Serial.write(((unsigned long)ARBITRATION_ID>>shift)&0b11111111);
}
// Payload

uint16_t sine_value = (float)(pow(2,15)*(sin((float)time)+1));

for(char shift=0;shift<32;shift+=8) {
  Serial.write((unsigned long)sine_value>>shift&0b11111111);
}
  Serial.write(0xBB);
  
  delay(DELAY);
  
  return;
}