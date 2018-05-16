
unsigned long BAUD __attribute__((section("CFG_BAUD"))) = 115200;
unsigned long DELAY __attribute__((section("CFG_DELAY"))) = 1000;
char BUILD_UUID[] __attribute__((section("CFG_UUID"))) =
    "06d8aed8-877c-4bdc-83c0-9284998f05b2";

unsigned long arbitration_id = 0x0;
unsigned long time_millis = 0b0;
unsigned long timestamp = 0x0;

uint8_t counter8 = 0x00;
uint16_t counter16 = 0x0000;
uint32_t counter32 = 0x00000000;

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
  Serial.write(0x00);

  // End of frame
  Serial.write(0xBB);
  return;
}

// Arduino Main Loop
void loop() {
  time_millis = millis();
  // Start of frame
  Serial.write(0xAA);

  // Timestamp
  timestamp = time_millis / 10;
  for (char shift = 0; shift < 32; shift += 8) {
    Serial.write((char)(((unsigned long)timestamp >> shift) & 0b11111111));
  }

  // DLC
  Serial.write(0x04);

  // Arbitration ID
  arbitration_id = 1;
  for (char shift = 0; shift < 32; shift += 8) {
    Serial.write((char)(((unsigned long)arbitration_id >> shift) & 0xFF));
  }

  // Payload
  for (char shift = 0; shift < 32; shift += 8) {
    Serial.write((unsigned long)time_millis >> shift & 0b11111111);
  }
  Serial.write(0xBB);
}