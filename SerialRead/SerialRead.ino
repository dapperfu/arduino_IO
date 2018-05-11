unsigned long BAUD = 115200;
unsigned long DELAY = 1000;

// Arduino Setup
void setup() {
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);	
  pinMode(10, INPUT_PULLUP);	
  pinMode(11, INPUT_PULLUP);	
	
  Serial.begin(BAUD);
  Serial.write(0x001);
  Serial.write("");
  Serial.write(0x019); 
  Serial.write(0x002);
  Serial.write(0x003);
  Serial.write(0x004);
}

// Arduino Main Loop
void loop() {
  Serial.write(0x001);
  Serial.write(0x002);
  Serial.write(8);
  Serial.write(digitalRead(8));
  Serial.write(0x003);
  Serial.write(0x002);
  Serial.write(9);
  Serial.write(digitalRead(8));
  Serial.write(0x003);
  
  Serial.write(0x002);
  Serial.write(10);
  Serial.write(digitalRead(10));
  Serial.write(0x003); 
   
  Serial.write(0x002);
  Serial.write(11);
  Serial.write(digitalRead(11));
  Serial.write(0x003);
  
  Serial.write(0x004);
  delay(DELAY);
}
