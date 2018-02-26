
**Урок 1.  Знайомство з `Wi-Fi` модулем `ESP8266` та `Arduino IDE`. Керування портами вводу-виводу**
=================


Зміст
-------

   * [`Wi-Fi` модуль `ESP8266`](#wi-fi-модуль-esp8266)
      * [Карта виводів плати розробника `"NodeMCU"`](#Карта-виводів-плати-розробника-nodemcu)
      * [Функції контактів](#Функції-контактів)
   * [Встановлення `Arduino IDE`](#Встановлення-arduino-ide-та-його-налаштування-для-роботи-з-esp8266)
      * [Структура програм в `ARDUINO IDE`](#Структура-програм-в-arduino-ide) 
      * [Перший скетч "`Blink`"](#Перший-скетч-blink)   
   * [Навчальні приклади для програмування `ESP8266`](#Навчальні-приклади-для-програмування-esp8266)
      * [Керування портами вводу-виводу](#Керування-портами-вводу-виводу)
      * [Переривання на портах вводу-виводу](#Переривання-на-портах-вводу-виводу)
      * [Налаштування та використання ШІМ (`PWM`)](#Налаштування-та-використання-ШІМ-pwm)
      * [Аналогово-цифрове перетворення](#Аналогово-цифрове-перетворення)
      * [Передавання даних на комп'ютер](#Передавання-даних-на-компютер)
   * [Завдання](#tests)
   * [Перелік посилань](#Перелік-посилань)

***



## `Wi-Fi` модуль `ESP8266`

У курсі ми будемо використовувати плату для розробки `"NodeMCU"`, що забезпечує живлилення та можливість комунікації `ESP8266` з комп'ютером через інтерфейс USB. Під час роботи з `"NodeMCU"` його програмування відбувається аналогічно `"Arduino"`. 


 ![Плата NodeMCU devkit](https://raw.githubusercontent.com/nodemcu/nodemcu-devkit-v1.0/master/Documents/NodeMCU_DEVKIT_1.0.jpg)

Приведена плата розробника з  модулем `ESP8266` є однією з найдешевших на ринку і продається за ціною близько $4,00.


У складі `NodeMCU devkit` є перетворювач протоколів UART-USB  `CP2102` або `CH340`. Плата також має регулятор напруги `NCP1117`, синій світлодіод на `GPIO16` та подільник напруги 220к / 100к Ом на вході штирі АЦП.

>Якщо плату не вдається запрограмувати можна спробувати скористатися _RESET_, утримуючи  кнопки FLASH + RST, потім відпустити FLASH, а за ним відпустити RST, тим самиам перезавантажуючи `CP2102` (`CH340`).




### Карта виводів плати розробника `"NodeMCU"`

Оскільки номери виводів на платі не відповідають номерам виводів `GPIO` `ESP8266`, то для полегшення використання плати розробника пропонується виконати перевизначення виводів через константи, що ідентичні надписам на платі розробника.

```c
static const uint8_t SDA = 4;
static const uint8_t SCL = 5;

static const uint8_t LED_BUILTIN = 16;
static const uint8_t BUILTIN_LED = 16;

static const uint8_t D0   = 16;
static const uint8_t D1   = 5;
static const uint8_t D2   = 4;
static const uint8_t D3   = 0;
static const uint8_t D4   = 2;
static const uint8_t D5   = 14;
static const uint8_t D6   = 12;
static const uint8_t D7   = 13;
static const uint8_t D8   = 15;
static const uint8_t D9   = 3;
static const uint8_t D10  = 1;
```

Тобто, якщо ви хочете використати вивід D5 на `'NodeMCU'` слід використовувати константу `D5`. В той час як "реальний" вивід на `ESP8266` буде використаний `GPIO 14`.

### Функції контактів

 ![Плата NodeMCU devkit](ESP8266/esp8266_devkit_horizontal-01.png)


			

Позначення | Призначення
--- | --- 
POWER   | Живлення 
ADC | АЦП 
SP.FUN  | Спец. функції 
PWM   | ШІМ (широтно-імпульсна модуляція)
I/O   | Контакти входу/виходу інформації 
CONTROL | Контакти для регулювання режимів 
COMM. INT  | Функції різних інтерфейсів  
PIN NUM    | Номер ніжки 

>Зверніть увагу на застереження.
>-	Типове значення струму від `GPIO` 6 мА (max. 12 мА)
>-	Для переведення модуля в енергозберігаючий режим необхідно з’єднати `GPIO16` та `EXT_RSTB` між собою. Для виходу з енергозбергігаючого режиму треба встановити на `GPIO16` лог. нуль, або перезавантажити модуль.
>-	Для перезавантаження модуля або виходу з енергозбергігаючого режиму необхідно встановити на `GPIO15`  лог. нуль, а на`GPIO2`  лог. одиницю. (Необхідно слідкувати, шоб такі умови не виникнули випадково!)



## Встановлення `Arduino IDE` та його налаштування для роботи з `ESP8266`


1.	Завантажте та встановіть `Arduino IDE` з офіційного веб-сайту.
1.	Запустіть `Arduino IDE` та відкрийте вікно налаштувань.
1.	Додайте наступну URL стрічку в поле «_Менеджер додаткових плат_». http://arduino.esp8266.com/stable/package_esp8266com_index
 ![Налаштування](ESP8266/image1.png)
1.	Відкрийте "_Менеджер плат_" в меню _Інструменти_ > _Плата_: та знайдіть платформу `ESP8266`.
1.	Виберіть найактуальнішу версію успадному списку (на момент написання цієї документації це є версія `2.4.0`).
1.	Натисніть кнопку "_Встановити_".
1.	Незабудьте обрати вашу конфігурацію плати `ESP8266`, за допомогою меню _Інструменти_ > _Плата_: після встановлення.

> P.S. Також, за бажанням, ви можете використати тестовий пакунок менеджера плат: http://arduino.esp8266.com/staging/package_esp8266com_index.json. 
Він може містити деякі нові функції, але в той же час деякі речі можуть неправильно працювати.

### Структура програм в `ARDUINO IDE`

```c
void setup() {
     // функція налаштувань мікроконтролера
     // виконується лише один раз, після вмикання живленя або скидання
}

void loop() {
     // функція для виконання основного алгоритму 
     // виконується періодично через кожну 1 мс
}
```

### Перший скетч "Blink"
   
   
Blink the blue LED on the ESP-01 module
This example code is in the public domain
    
The blue LED on the ESP-01 module is connected to `GPIO1` 
    (which is also the TXD pin; so we cannot use Serial.print() at the same time)
    
> Note that this sketch uses LED_BUILTIN to find the pin with the internal LED
   
   
   
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
   
   
   
## Навчальні приклади для програмування `ESP8266`


### Керування портами вводу-виводу

Існують спрощені функції налаштування – `pinMode`, зчитування стану – `digitalRead` та запису – `digitalWrite`. Номери цифрових входів/виходів в `Arduino` безпосередньо відповідають номерам `GPIO` `ESP8266`, так що щоб зчитати стан `GPIO2` треба викликати функцію – `digitalRead(2)`.

За замовчуванням всі `GPIO` налаштовані як – `INPUT`.

Цифрові контакти 0-15 можуть бути налаштовані на вхід – `INPUT`, вихід – `OUTPUT` або вхід з підтяжкою до логічної одиниці – `INPUT_PULLUP`. 

> Порт`GPIO16` не має налаштування – `INPUT_PULLUP`, але натомість він має можливіть налаштування на вхід з підтяжкою до логічної нуля – `INPUT_PULLDOWN_16`.  

Майже всі `GPIO` мають можливість працювати у складі інтерфейсів до переферійних пристроїв. Наприклад, у складі апаратних інтерфейсів обміну даних таких як `SPI`, `I2C` тощо. Ці функції, як правило, активується у разі підключення відповідних бібліотек в `Arduino IDE`. 

> Модуль `ESP8266` для розширення `flash` пам'яті містить додаткову мікросхему пам’яті яка підключається до `GPIO6,7,8,9,10,11` і тому їх не можна використовувати за звичним призначенням, щоб мати змогу користуватися додатковою пам’яттю. Не вірне застосування може призвести до збою програми, адже ці контакти відповідають за  запис прошивки в ESP8266. Контакти `GPIO9, 10` можуть бути задіяні в якості IO, якщо флеш-чіп працює в режимі DIO (на відміну від QIO, який за замовчуванням один).



Приклад роботи з `GPIO` для схеми з світлодіодами.

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
### Переривання на портах вводу-виводу

Переривання контактів задається за допомогою функції – `attachInterrupt` , а відключається за допомогою – `detachInterrupt` і можуть бути налаштовані на всіх `GPIO` окрім `GPIO16`. Підтримуються такі типи переривання: `CHANGE`,  `RISING`,  `FALLING`, так щоб налаштувати переривання по зміні рівня з 1 в 0 для GPIO2 треба викликати функцію – `attachInterrupt(GPIO2,callback, FALLING);` , де `callback` – це функція що буде викликана в результаті переривання.

Приклад налаштування переривань `GPIO` для схеми з конопкою.

```c
const int interruptPin = 0; //GPIO 0 (Flash Button) 
const int LED = 2; // On board blue LED 
 
void setup() { 
  Serial.begin(115200); 
  pinMode(LED, OUTPUT); 
  pinMode(interruptPin, INPUT_PULLUP); 
  attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, CHANGE); 
  // CHANGE, RISING, FALLING
} 
 
void loop() 
{ 
    digitalWrite(LED,HIGH); // LED off 
    delay(1000); 
    digitalWrite(LED,LOW); // LED on 
    delay(1000); 
} 
 
//This program get executed when interrupt is occures i.e.change of input state
void handleInterrupt() { 
    Serial.println("Interrupt Detected"); 
}
```

### Налаштування та використання ШІМ (PWM)

Для формування аналогових сигналів цифровим способом існують спеціальні пристрої - ЦАП (цифро-аналогові перетворювачі). Проте у разі якщо виги до точності формування таких сигналів не високі, можливо скористатися широтно-імпульсною модуляцією (ШІМ) або PWM (pulse-width modulation). Приклад такого сигналу наведено на рисунку.

![PWM](ESP8266/pwm.png)

У модуля `ESP8266` всі цифрові `GPIO` підтримують ШІМ. Для того, щоб налаштувати таку функцію на `GPIO` необхідно викликати функцію – `analogWrite(pin, value)`, де `pin` – це `GPIO`, що підтримує PWM, `value` – це значення заповненості (`duty cycle`) періоду і регулюється від `0` до `PWMRANGE` (по замовчуванням 1023) відповідно `0%` та `100%` заповненості.

Також за допомогою функції - `analogWriteFreq(frequency)` ви можете змінювати частоту (період) ШІМ, що по замовчуванню рівна 1 кГц, а за допомогою - `analogWriteRange(range)` ви можете змінювати `PWMRANGE`.


  
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


### Аналогово-цифрове перетворення

Використання аналогового входу для вимірювання напруги з подільникка напруги або сенсорів.

модуль `ESP8266` має лише один канал 10-розрядного АЦП. Він може бути використаний або для зчитування напруги з контакту АЦП, або для визначення напруги живлення модуля (VCC), що інколи може бути корисним.

Для зчитування зовнішньої напруги, що подається на АЦП, використовують функцію – `analogRead(A0)`, що повертає значення в діапазоні `0-1023`. При цьому вхідна напруга має бути в межах  `0 - 1.0 В`, але можна подавати на вхід напругу вище, рекомендовано до напруги живлення (`VCC – 3.3V`).

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
Для вимірювання напруги живлення `VCC` використовується функція – `ESP.getVcc()`. У цьому разі ADC контакт повинен бути не підключеним! Крім того, у налаштуваннях контролера `setup()` обов’язково необхідно додати команду – `ADC_MODE(ADC_VCC)`.

### Передавання даних на комп'ютер

Об'єкт `Serial` працює так само, як і з `Arduino`. Крім апаратного `FIFO` (128 байт для передачі – `TX` та прийому – `RX`), `Serial` має додаткові 256-байт для `TX` та `RX` в буфері. Передача, і прийом даних виконується по перериваннях, прозоро до вашого скетчу. Функції запису та читання блокують виконання програми лише тоді, коли `FIFO` – заповнений, або буфер – пустий. Зверніть увагу, що довжину додаткового 256-бітового буфера можна налаштувати.

`Serial` використовує `UART0`, який зіставляється з пінами `GPIO1` (`TX`) та `GPIO3` (`RX`). Ці контакти можуть бути переназначені на `GPIO15` (`TX`) і `GPIO13` (`RX`), викликом функції – `Serial.swap()` після `Serial.begin()`. Повторний виклик – `Serial.swap()` знову повертає `UART0` назад. 

Також, паралельно можна запустити `Serial1` , що використовує UART1 та зіставляється лише з `GPIO2(TX)`, адже пін що відповідає за отримання даних (`RX`) належить контактній групі контактів для підключення flash чіпу. Отже `UART1` не може використовуватися для отримання даних. Для використання `Serial1`, викличте функцію – `Serial1.begin(baudrate)`, де `baudrate` – це швидкість передачі в бод (baud). 

Якщо `Serial1` не використовується, а `Serial` не був перекинутий, то `TX` для `UART0` може бути зіставлений з `GPIO2` викликом команди `Serial.set_tx(2)` після `Serial.begin` або безпосередньо `Serial.begin(Baud, Config, Mode, 2)`.

За замовчанням діагностична інформація від бібліотек `Wi-Fi` вимикається після виклику `Serial.begin()`. Для моніторингу налагоджувальної інформації на `UART0` використайте – `Serial.setDebugOutput(true)`. Щоб спрямувати вивід – інформації на `Serial1` використайте – `Serial1.setDebugOutput(true)`.

Вам також слід використовувати – `Serial.setDebugOutput(true)`, щоб активувати стандартну функцію виводу – `printf()`.

Метод – `Serial.setRxBufferSize(size_t size)` дозволяє задати розмір приймального буфера. Значення за замовчуванням - 256.

`Serial` та `Serial1` підтримують 5, 6, 7, 8 біт даних, odd(O), even(E), no (N) режими парності, 1 або 2 стоп біта. Для вибору потрібного режиму викличте – `Serial.begin(baudrate, SERIAL_8N1)`; або `Serial.begin(baudrate, SERIAL_6E2)`; і т.д.

Нижче приведено приклад програми перевірки послідовного порта, яка виконує функцію ехо, тобто повернення у термінал даних. що були відправлені на мікроконтролер. 
  
Функції `Serial.baudRate()`, `Serial1.baudRate()` використовуються для перевірки поточної швидкості передачі даних.

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
    Serial.write(Serial.read()); // Еchо - те що буде відіслано те і повернеться
    if(Serial.available() == 0)
      Serial.println();
  }
}
```

Описаний вище метод, також підтримується офіційною `ESP8266 Software Serial` бібліотекою.

Зверніть увагу , що ця реалізація дійсна тільки для плат на базі `ESP8266`, і не буде працювати з іншими платами `Arduino`.

Існують багато різноманітних функцій для роботи з типом `String`, і об’єкт – `Serial` співпрацює з ними, тому їх застосування буде доречним, а сам `Serial` є типом `Stream`.

Далі наведено приклад реалізації керування світлодіодами з терміналу комп'ютера через послідовний порт.

```c
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
```

[//]: ## "Завдання" 



Перелік посилань:	
---
1. http://esp8266.github.io/Arduino/versions/2.3.0/


