// pins for the LEDs:
const int redPin = D6;        // Створення константи "redPin" що буде рівнятися номеру ніжки
                              // мікроконтролера з ім'ям "D6" (Насправді D6 = 12, див. рисунки)
const int greenPin = D5;
const int bluePin = D4;

void setup() {
  // make the pins outputs:
  pinMode(redPin, OUTPUT);    // налагтування ніжки redPin в режим виходу
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  int value = analogRead(A0); // Зчитування напруги з аналогово входу А0 в діапазоні 0 - 1.0 Вольт 
                              // та представлення результату в діапазоні 0 - 1023
  value = map(value, 0, 1023, 0, 255); // Конвертування значенння "value" з діапазона 0-1023 в 0-255
  analogWrite(redPin, value); // На ніжці redPin генерування Широтно Імпульсної Маніпуляції (див. урок)
  delay(100);                 // Застримка на 100  мілісекунд
  value = analogRead(A0);
  value = map(value, 0, 1023, 0, 255);
  analogWrite(greenPin, value);
  delay(100);
  value = analogRead(A0);
  value = map(value, 0, 1023, 0, 255);
  analogWrite(bluePin, value);
  delay(100);
}
