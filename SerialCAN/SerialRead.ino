unsigned long BAUD = 115200;
unsigned long DELAY = 1000;
char ARBITRATION_ID = 12;

unsigned long time;

unsigned char counter = 0;

// Arduino Setup
void setup() {
  Serial.begin(BAUD);
    // Start of frame
  Serial.write(0xAA);
// Timestamp
  Serial.write(0x00);
  Serial.write(0x00);
  Serial.write(0x00);
  Serial.write(0x00);
// DLC
  Serial.write(0x01);
// Arbitration ID
  Serial.write(0x00);
  Serial.write(0x00);
  Serial.write(0x00);
  Serial.write(0xFF);
// Payload
  Serial.write(counter);
// End of frame
  Serial.write(0xBB);
    
  counter++;
}

// Arduino Main Loop
void loop() {
   time = millis();
// Start of frame
  Serial.write(0xAA);
// Timestamp
for(char shift=0;shift<32;shift+=8) {
  Serial.write(time>>shift&0b11111111);
}
// DLC
  Serial.write(0x01);
// Arbitration ID
for(char shift=0;shift<32;shift+=8) {
  Serial.write(((unsigned long)ARBITRATION_ID>>shift)&0b11111111);
}
// Payload
  Serial.write(counter);
// End of frame
  Serial.write(0xBB);
    
  counter++;
  delay(DELAY);
}