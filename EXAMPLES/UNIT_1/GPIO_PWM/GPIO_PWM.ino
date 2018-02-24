// pins for the LEDs:
const int redPin = D5;        // Створення константи "redPin" що буде рівнятися номеру ніжки
                              // мікроконтролера з ім'ям "D5" (Насправді D5 = 14, див. рисунки)
const int greenPin = D6;
const int bluePin = D4;

void setup() {
  // make the pins outputs:
  pinMode(redPin, OUTPUT);    // налагтування ніжки redPin в режим виходу
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  analogWrite(redPin, random(256)); // функція - random(256) генерує випадкове число в діапазоні 0 - 255
  analogWrite(greenPin, random(256));
  analogWrite(bluePin, random(256));
  delay(300);                       // Застримка на 300  мілісекунд
}
