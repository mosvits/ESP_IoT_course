#ifdef ESP8266

#define Project_DEBUG

#ifdef Project_DEBUG

#define DEBUG_Serial Serial
#define DEBUG_print(...)    DEBUG_Serial.print(__VA_ARGS__)
#define DEBUG_println(...)  DEBUG_Serial.println(__VA_ARGS__)
#define DEBUG_begin(...)    DEBUG_Serial.begin(__VA_ARGS__)
#define DEBUG_printf(...)   DEBUG_Serial.printf(__VA_ARGS__)
#define DEBUG_flush(...)    DEBUG_Serial.flush(__VA_ARGS__)
// Один з найпростіших способів дебагу. (ще можна передавати повідамнення на сервер, але весь алгоритм треба прописувати вручну, хоча це всерівно треба робити - відпрваляти логи помилок)
#define DEBUG_var(token)  { DEBUG_print( #token " = "); DEBUG_println(token); }

#else

#define DEBUG_Serial
#define DEBUG_print(...)
#define DEBUG_println(...)
#define DEBUG_begin(...)
#define DEBUG_printf(...)
#define DEBUG_flush(...)
#define DEBUG_var(token)

#endif // Project_DEBUG

#define PIN_DMD_nOE       D8    // GPIO15, active low Output Enable, setting this low lights all the LEDs in the selected rows. Can pwm it at very high frequency for brightness control.
#define PIN_DMD_A         D3    // GPIO0
#define PIN_DMD_B         D1    // GPIO5
#define PIN_DMD_CLK       D5    // GPIO14_SCK  is SPI Clock if SPI is used
#define PIN_DMD_SCLK      D4    // GPIO2
#define PIN_DMD_R_DATA    D7    // GPIO13_MOSI is SPI Master Out if SPI is used
// Not used
#define PIN_FEEDBACK      D6    // GPIO12_MISO is SPI Master In if SPI is used

//DMD I/O pin macros
#define LIGHT_DMD_ROW_01_05_09_13()       { digitalWrite( PIN_DMD_B,  LOW ); digitalWrite( PIN_DMD_A,  LOW ); }
#define LIGHT_DMD_ROW_02_06_10_14()       { digitalWrite( PIN_DMD_B,  LOW ); digitalWrite( PIN_DMD_A, HIGH ); }
#define LIGHT_DMD_ROW_03_07_11_15()       { digitalWrite( PIN_DMD_B, HIGH ); digitalWrite( PIN_DMD_A,  LOW ); }
#define LIGHT_DMD_ROW_04_08_12_16()       { digitalWrite( PIN_DMD_B, HIGH ); digitalWrite( PIN_DMD_A, HIGH ); }
#define LATCH_DMD_SHIFT_REG_TO_OUTPUT()   { digitalWrite( PIN_DMD_SCLK, HIGH ); digitalWrite( PIN_DMD_SCLK,  LOW ); }
#define CLK_SHIFT_REG_TO_OUTPUT()         { digitalWrite( PIN_DMD_CLK, HIGH ); digitalWrite( PIN_DMD_CLK,  LOW ); }
#define OE_DMD_ROWS_OFF()                 { analogWrite(PIN_DMD_nOE, 0); }       //{ digitalWrite( PIN_DMD_nOE, LOW  ); }
#define OE_DMD_ROWS_ON()                  { analogWrite(PIN_DMD_nOE, Spacing); } //{ digitalWrite( PIN_DMD_nOE, HIGH ); }

#include <SPI.h>

const byte bPixelLookupTable[8] =
{
  0x80,   //0, bit 7
  0x40,   //1, bit 6
  0x20,   //2. bit 5
  0x10,   //3, bit 4
  0x08,   //4, bit 3
  0x04,   //5, bit 2
  0x02,   //6, bit 1
  0x01    //7, bit 0
};

uint8_t test1[] = { // Вертикальний масив РТФ
  0x78, 0x78, 0x30, 0x30,  0x30, 0x30, 0x30, 0x30,  0x3C, 0x3C, 0x33, 0x13,  0x13, 0x33, 0x3C, 0x3C,
  0x0F, 0x06, 0x06, 0x06,  0x06, 0x06, 0x06, 0x06,  0x06, 0x06, 0x06, 0x86,  0x86, 0x06, 0x3F, 0x3F,
  0x01, 0x01, 0x00, 0x00,  0x00, 0x00, 0x00, 0x01,  0x03, 0x06, 0x0C, 0x0C,  0x0C, 0x06, 0xC3, 0xC1,
  0xE0, 0xE0, 0xC0, 0xC0,  0xC0, 0xC0, 0xC0, 0xE0,  0xF0, 0x18, 0xCC, 0xCC,  0xCC, 0x18, 0xF0, 0xE0,
  
  0x78, 0x78, 0x30, 0x30,  0x30, 0x30, 0x30, 0x30,  0x3C, 0x3C, 0x33, 0x13,  0x13, 0x33, 0x3C, 0x3C,
  0x0F, 0x06, 0x06, 0x06,  0x06, 0x06, 0x06, 0x06,  0x06, 0x06, 0x06, 0x86,  0x86, 0x06, 0x3F, 0x3F,
};

byte Spacing = 30;

void setup() {
  // Serial
  DEBUG_begin(115200);
  // SPI // https://github.com/esp8266/Arduino/tree/master/libraries/SPI
  SPI.begin();
  SPI.setHwCs(false);
  //SPI.setClockDivider(SPI_CLOCK_DIV2);
  /*
    SPI_CLOCK_DIV2    0x00101001 //8 MHz
    SPI_CLOCK_DIV4    0x00241001 //4 MHz
    SPI_CLOCK_DIV8    0x004c1001 //2 MHz
    SPI_CLOCK_DIV16   0x009c1001 //1 MHz
    SPI_CLOCK_DIV32   0x013c1001 //500 KHz
    SPI_CLOCK_DIV64   0x027c1001 //250 KHz
    SPI_CLOCK_DIV128  0x04fc1001 //125 KHz
  */
  SPISettings settings(1000000, MSBFIRST, SPI_MODE2);
  /*
    LSBFIRST // Не підходить
    MSBFIRST
    SPI_MODE0 0x00 - CPOL: 0  CPHA: 0
    SPI_MODE1 0x01 - CPOL: 0  CPHA: 1
    SPI_MODE2 0x10 - CPOL: 1  CPHA: 0
    SPI_MODE3 0x11 - CPOL: 1  CPHA: 1 // Не підходить
  */
  SPI.beginTransaction(settings);
  // GPIO
  pinMode(PIN_DMD_A, OUTPUT);
  pinMode(PIN_DMD_B, OUTPUT);
  pinMode(PIN_DMD_SCLK, OUTPUT);

  // PWM - ШИМ - ШІМ // PIN_DMD_nOE
  analogWriteRange(256); // "Скважность" - шпаруватість (256 - максимальне допустиме значення, з більшим значеням автоматично виставляє 256)
  analogWriteFreq(1000); // Частота ШІМ
  /*
     uint32_t freq = 10;
     uint32_t range = 5;
     ESP8266_CLOCK = 80000000UL; // 80 MHz
     pwm_multiplier = ESP8266_CLOCK/(pwm_range * pwm_freq); // 80 MHz / 50 Hz

     \AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.3.0\cores\esp8266/core_esp8266_wiring_pwm.c  esp8266_peri.h
  */
  digitalWrite(PIN_DMD_A, LOW);  //
  digitalWrite(PIN_DMD_B, LOW); //
  digitalWrite(PIN_DMD_CLK, LOW); //
  digitalWrite(PIN_DMD_SCLK, LOW);  //
  digitalWrite(PIN_DMD_R_DATA, HIGH); //
  digitalWrite(PIN_DMD_nOE, LOW);   //
}

const unsigned long timeDelay = 100; // затримка в мікросекундах для регулювання мерехтіння // Регулювати з вимкнутим дебаг режимом!

void writeData(int shift_h, uint8_t *data, unsigned int size_data) {
  unsigned int colons = size_data / 16; // Кількість стовпців в рядку
  for (byte shift_v = 0; shift_v < 4; shift_v++) { // 4 елемента в секторі
    // shift_v - перемикає 4 горизонтальні рядки по 8 біт
    // shift_h - робить горизонтальний зсув вліво зображення на панелі
    // data - назва масиву даних
    for (int i = 0; i < colons * 4 ; i++ ) { // colons*4 кількість секторів 4*8 в масиві
      int var = (i * 4) % 16 + (3 - shift_v); // номер першого елементу в деякому рядку
      // Зобораження в секторі по 8 біт формується з лівої та правої частин.
      //                      рядок     стовбець         стовбець зсуву      остача   формування посереднього елементу
      uint8_t sector_8 = ((data[var + 16 * (( (int)(i / 4) +     (int)(shift_h / 8) ) % colons)] <<      (shift_h % 8) ) // ліва частина 8-мибітового сектора
                          | (data[var + 16 * (( (int)(i / 4) + 1 + (int)(shift_h / 8) ) % colons)] >> (8 - (shift_h % 8)))); // права частина 8-мибітового сектора
      //byte response =
      SPI.transfer(~sector_8);
      //*/
    }
    OE_DMD_ROWS_OFF(); // Панель гасне перед командою вивести нові дані
    switch (shift_v) { // Вибір горизонтального рядка
      case 0:
        LIGHT_DMD_ROW_01_05_09_13(); // А=0,В=0
        break;
      case 1:
        LIGHT_DMD_ROW_02_06_10_14(); // А=1,В=0
        break;
      case 2:
        LIGHT_DMD_ROW_03_07_11_15(); // А=0,В=1
        break;
      case 3:
        LIGHT_DMD_ROW_04_08_12_16(); // А=1,В=1
        break;
    }
    LATCH_DMD_SHIFT_REG_TO_OUTPUT(); // Виведення на панель завантажених даних
    OE_DMD_ROWS_ON(); // Панель загорається з новими даними
    delayMicroseconds(timeDelay);
  }
}

int shift = 0; // Змінна зміщення зображення
double speed_shift = (double)1 / 100000; // Відносна швидкість зміщення
int w; // Змінна інкременту (лінійно зростаючого)


void loop() {
  writeData(shift, test1, sizeof(test1));
  int amplitude = 30; //128;
  Spacing = amplitude - (int)(amplitude * sin((double)w / 100)); //Динамічне управління яскравістю за рахунок шпароватісті ШІМ від 0 до 256
  //shift = (int)(5 * w * speed_shift * (timeDelay + 0)); // Або так
  shift = (int)(micros() * speed_shift); // millis() - мілісекунд з моменту запуску контролера
  //DEBUG_var(w * speed_shift * (timeDelay + 0)); //--> "w * speed_shift * (timeDelay + 0) = 0.00"
  w++;
}

#endif // ESP8266
