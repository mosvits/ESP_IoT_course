void setup() {
  // Set Baud rate to 57600
  // Установити бод швидкість 57600 

  Serial.begin(57600);

  // Get current baud rate
  // Отримати поточну бод швидкість 

  int br = Serial.baudRate();

  // Will print "Serial is 57600 bps"
  // Надрукує "Serial is 57600 bps"
  Serial.printf("Serial is %d bps", br);
}

void loop() {
  while(Serial.available() > 0) {
    Serial.write(Serial.read()); // Ехо - те що буде відіслано те і повернеться
    if(Serial.available() == 0)
      Serial.println();
  }
}
