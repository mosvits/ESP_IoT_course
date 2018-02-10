Boards
======

Adafruit HUZZAH ESP8266 (ESP-12)
--------------------------------

Розглянемо лише плату NodeMCU, з якою ми будемо працювати, інші
конфігурації ви зможете знайти за
`*посиланням* <http://arduino-esp8266.readthedocs.io/en/2.4.0/boards.html>`__.

NodeMCU 0.9
-----------

Pin mapping
~~~~~~~~~~~

Pin numbers written on the board itself do not correspond to ESP8266
GPIO pin numbers. Constants are defined to make using this board easier:

Номери контактів, написані на самій платі, не відповідають номерам
PIN-кодів ESP8266 GPIO. Константи визначаються для полегшення
використання цієї плати:

static const uint8\_t SDA = 4;

static const uint8\_t SCL = 5;

static const uint8\_t LED\_BUILTIN = 16;

static const uint8\_t BUILTIN\_LED = 16;

static const uint8\_t D0 = 16;

static const uint8\_t D1 = 5;

static const uint8\_t D2 = 4;

static const uint8\_t D3 = 0;

static const uint8\_t D4 = 2;

static const uint8\_t D5 = 14;

static const uint8\_t D6 = 12;

static const uint8\_t D7 = 13;

static const uint8\_t D8 = 15;

static const uint8\_t D9 = 3;

static const uint8\_t D10 = 1;

If you want to use NodeMCU pin 5, use D5 for pin number, and it will be
translated to ‘real’ GPIO pin 14.

Якщо ви хочете використати NodeMCU pin 5, використайте D5 для PIN-коду,
і він буде переведений на "реальний" PIN-код GPIO 14.

NodeMCU 1.0
-----------

This module is sold under many names for around $6.50 on AliExpress and
it’s one of the cheapest, fully integrated ESP8266 solutions.

Цей модуль продається під багатьма іменами за ціною близько $ 4,00 на
AliExpress, і це один з найдешевших, з повністю інтегрованою ESP8266,
рішень.

It’s an open hardware design with an ESP-12E core and 4 MB of SPI flash.

Це відкрита конструкція спроектована з ESP-12Е ядром і 4 МБ SPI
флеш-пам'яті.

According to the manufacturer, “with a micro USB cable, you can connect
NodeMCU devkit to your laptop and flash it without any trouble”. This is
more or less true: the board comes with a CP2102 onboard USB to serial
adapter which just works, well, the majority of the time. Sometimes
flashing fails and you have to reset the board by holding down FLASH +
RST, then releasing FLASH, then releasing RST. This forces the CP2102
device to power cycle and to be re-numbered by Linux.

За заявою виробника, "з мікро-USB-кабелем, ви можете підключити NodeMCU
devkit до свого ноутбука і прошити, без проблем". Це більш-менш правда:
плата поставляється з бортовим USB-послідовним адаптером CP2102 , або
CH340 (у не офіційних збірках), який просто працює, більшу частину часу.
Іноді прошити не вдається, і вам доведеться скинути плату, утримуючи
FLASH + RST, потім відпустити FLASH, а за ним відпустити RST. Це змушує
перезавантажити пристрій CP2102 (CH340) і переключитися на Linux.

The board also features a NCP1117 voltage regulator, a blue LED on
GPIO16 and a 220k/100k Ohm voltage divider on the ADC input pin.

Плата також має регулятор напруги NCP1117, синій світлодіод на GPIO16 та
подільник напруги 220к / 100к Ом на вхідному штирі АЦП.

Full pinout and PDF schematics can be
found \ `*here* <https://github.com/nodemcu/nodemcu-devkit-v1.0>`__

Повну схему пінів та PDF-файлів можна знайти
`*тут* <https://github.com/nodemcu/nodemcu-devkit-v1.0>`__.
