// pins for the LEDs:
const int redPin = D1;
const int greenPin = D2;
const int bluePin = D4;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // make the pins outputs:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // if there's any serial available, read it:
  while (Serial.available() > 0) {

    // look for the next valid integer in the incoming serial stream:
    int red = Serial.parseInt();
    Serial.print(red, DEC);
    Serial.print(" ");
    // do it again:
    int green = Serial.parseInt();
    Serial.print(green, HEX);
    Serial.print(" ");
    // do it again:
    int blue = Serial.parseInt();
    Serial.print(blue, BIN);
    Serial.print(" ");

    // fade the red, green, and blue legs of the LED:
    analogWrite(redPin, red);
    analogWrite(greenPin, green);
    analogWrite(bluePin, blue);

    // print the three numbers in one string as hexadecimal:
    Serial.print(red, HEX);
    Serial.print(green, HEX);
    Serial.println(blue, HEX);
  }
}
