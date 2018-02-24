
**Урок 1.  Знайомство з Wi-Fi модулем ESP8266 та Arduino IDE. Керування портами вводу-виводу**
=================


Зміст
-------

   * [Wi-Fi модуль ESP8266](#Wi-Fi-модуль-ESP8266)
   * [Встановлення Arduino IDE](#Встановлення-Arduino-IDE-та-його-налаштування-для-роботи-з-ESP8266)
   * [Навчальні приклади для програмування ESP8266](#Навчальні-приклади-для-програмування-ESP8266)
      * [Перший скетч "Blink". ](#Перший-скетч-"Blink".-Програмування-мікроконтролера)
      * [Керування портами вводу-виводу](#Керування-портами-вводу-виводу)
      * [Налаштування та використання ШІМ (PWM)](#Налаштування-та-використання-ШІМ-(PWM))
      * [Аналогово-цифрове перетворення](#Аналогово-цифрове-перетворення)
      * [Передавання даних на комп'ютер](#Передавання-даних-на-комп'ютер)
   * [Завдання](#tests)
   * [Перелік посилань](#Перелік-посилань)

***



## Wi-Fi модуль ESP8266




## Встановлення Arduino IDE та його налаштування для роботи з ESP8266


1.	Завантажте та встановіть `Arduino IDE` з офіційного веб-сайту.
1.	Запустіть `Arduino IDE` та відкрийте вікно налаштувань.
1.	Додайте наступну URL стрічку в поле «Менеджер додаткових плат». http://arduino.esp8266.com/stable/package_esp8266com_index
 ![Налаштування](ESP8266/image1.png)
1.	Відкрийте Менеджер плат з меню Інструменти > Плата: та знайдіть платформу `ESP8266`.
1.	Виберіть найактуальнішу версію успадному списку (на момент написання цієї документації це є версія 2.3.0).
1.	Натисніть кнопку "Встановити".
1.	Незабудьте обрати вашу конфігурацію плати `ESP8266`, задопомогоюменю Інструменти > Плата: після встановлення.

> P.S. Також, за бажанням, ви можете використати тестовий пакунок менеджера плат: http://arduino.esp8266.com/staging/package_esp8266com_index.json. 
Він може містити деякі нові функції, але в той же час деякі речі можуть неправильно працювати.

## Навчальні приклади для програмування `ESP8266`


### Перший скетч "Blink"

```
/*
 ESP8266 Blink by Simon Peter
 Blink the blue LED on the ESP-01 module
 This example code is in the public domain
 
 The blue LED on the ESP-01 module is connected to GPIO1 
 (which is also the TXD pin; so we cannot use Serial.print() at the same time)
 
 Note that this sketch uses LED_BUILTIN to find the pin with the internal LED
*/
```


``` c
#define LED_BUILTIN D4
 
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
}
   
// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
                                    // but actually the LED is on; this is because 
                                    // it is active low on the ESP-01)
  delay(1000);                      // Wait for a second
  digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(2000);                      // Wait for two seconds (to demonstrate the active low LED)
}
```

### Керування портами вводу-виводу

Приклад роботи з GPIO та збирання схеми з світлодіодами.

```c
// pins for the LEDs:
const int redPin   = D6;
const int greenPin = D5;
const int bluePin  = D4;
 
void setup() {
  // make the pins outputs:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}
 
void loop() {
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, LOW);
  delay(500);
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, HIGH);
  delay(500);
}
```
# Налаштування та використання ШІМ (PWM)
```c
// pins for the LEDs:
const int redPin = D5;  // Створення константи "redPin" що буде рівнятися номеру ніжки
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

```

# Аналогово-цифрове перетворення

Використання аналогового входу для вимірювання напруги з подільникка напруги або сенсорів.

```c
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
```
# Передавання даних на комп'ютер

Приклад керування світлодіодами з терміналу комп'ютера через послідовний порт.

```c
void setup() {
  // Встановити швидкість 57600 біт/с
  Serial.begin(57600);
 
  // Перевірити поточну швидкість передавання даних 
  int br = Serial.baudRate();
 
  // Маємо отримати повідомлення "Serial is 57600 bps"
  Serial.printf("Serial is %d bps", br);
}
 
void loop() {
  while(Serial.available() > 0) {
    Serial.write(Serial.read()); // Ехо - те що буде відіслано те і повернеться
    if(Serial.available() == 0)
      Serial.println();
  }
}
```



Перелік посилань:	
---
1. http://esp8266.github.io/Arduino/versions/2.3.0/


Приклади оформлення:
---
Colons can be used to align columns.

| Tables        | Are           | Cool  |
| ------------- |:-------------:| -----:|
| col 3 is      | right-aligned | $1600 |
| col 2 is      | centered      |   $12 |
| zebra stripes | are neat      |    $1 |

There must be at least 3 dashes separating each header cell.
The outer pipes (|) are optional, and you don't need to make the 
raw Markdown line up prettily. You can also use inline Markdown.

Markdown | Less | Pretty
--- | --- | ---
*Still* | `renders` | **nicely**
1 | 2 | 3

Three or more...

---

Hyphens
***

Asterisks

___

Underscores