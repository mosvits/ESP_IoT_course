
Table of contents
=================

<!--ts-->
   * [Робота з бібліотеками `ESP8266`](#Робота-з-бібліотеками-esp8266)
      * [Функції формування часових затримок та подій](#Функції-формування-часових-затримок-та-подій)
      * [Бібліотека "Ticker". Формування періодичних подій за перериваннями від таймера](#Бібліотека-ticker-Формування-періодичних-подій-за-перериваннями-від-таймера)
      * [Спеціальні функції та команди для ESP8266](#Спеціальні-функції-та-команди-для-esp8266)
<!--te-->

Обмін даними через протокол WebSocket
===

Посилання: 
https://tttapa.github.io/ESP8266/Chap14%20-%20WebSocket.html

Бібліотека: https://github.com/Links2004/arduinoWebSockets

Приклад:
```c
/*
 * WebSocketServer_LEDcontrol.ino
 */

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Hash.h>

#define LED_RED     0
#define LED_GREEN   4
#define LED_BLUE    2

#define USE_SERIAL Serial


ESP8266WiFiMulti WiFiMulti;

ESP8266WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

    switch(type) {
        case WStype_DISCONNECTED:
            USE_SERIAL.printf("[%u] Disconnected!\n", num);
            break;
        case WStype_CONNECTED: {
            IPAddress ip = webSocket.remoteIP(num);
            USE_SERIAL.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);

            // send message to client
            webSocket.sendTXT(num, "Connected");
        }
            break;
        case WStype_TEXT:
            USE_SERIAL.printf("[%u] get Text: %s\n", num, payload);

            if(payload[0] == '#') {
                // we get RGB data

                // decode rgb data
                uint32_t rgb = (uint32_t) strtol((const char *) &payload[1], NULL, 16);
                USE_SERIAL.printf("Analog Write: %d\n", rgb);
//                analogWrite(LED_RED,    ((rgb >> 16) & 0xFF));
//                analogWrite(LED_GREEN,  ((rgb >> 8) & 0xFF));
//                analogWrite(LED_BLUE,   ((rgb >> 0) & 0xFF));

                if(rgb >128)
                  digitalWrite(LED_BLUE, LOW);
                else
                  digitalWrite(LED_BLUE, HIGH);
            }

            break;
    }

}

void setup() {
    //USE_SERIAL.begin(921600);
    USE_SERIAL.begin(115200);

    //USE_SERIAL.setDebugOutput(true);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    pinMode(LED_RED, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);

    digitalWrite(LED_RED, 1);
    digitalWrite(LED_GREEN, 1);
    digitalWrite(LED_BLUE, 1);

    WiFiMulti.addAP("Colario", "Colar123");

    while(WiFiMulti.run() != WL_CONNECTED) {
        delay(100);
    }

    // start webSocket server
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);

    if(MDNS.begin("esp8266")) {
        USE_SERIAL.println("MDNS responder started");
    }

    // handle index
    server.on("/", []() {
        // send index.html
        server.send(200, "text/html", "<html><head><script>var connection = new WebSocket('ws://'+location.hostname+':81/', ['arduino']);connection.onopen = function () {  connection.send('Connect ' + new Date()); }; connection.onerror = function (error) {    console.log('WebSocket Error ', error);};connection.onmessage = function (e) {  console.log('Server: ', e.data);};function sendRGB() {  var r = parseInt(document.getElementById('r').value).toString(16);  var g = parseInt(document.getElementById('g').value).toString(16);  var b = parseInt(document.getElementById('b').value).toString(16);  if(r.length < 2) { r = '0' + r; }   if(g.length < 2) { g = '0' + g; }   if(b.length < 2) { b = '0' + b; }   var rgb = '#'+r+g+b;    console.log('RGB: ' + rgb); connection.send(rgb); }</script></head><body>LED Control:<br/><br/>R: <input id=\"r\" type=\"range\" min=\"0\" max=\"255\" step=\"1\" oninput=\"sendRGB();\" /><br/>G: <input id=\"g\" type=\"range\" min=\"0\" max=\"255\" step=\"1\" oninput=\"sendRGB();\" /><br/>B: <input id=\"b\" type=\"range\" min=\"0\" max=\"255\" step=\"1\" oninput=\"sendRGB();\" /><br/></body></html>");
    });

    server.begin();

    // Add service to MDNS
    MDNS.addService("http", "tcp", 80);
    MDNS.addService("ws", "tcp", 81);

    digitalWrite(LED_RED, 0);
    digitalWrite(LED_GREEN, 0);
    digitalWrite(LED_BLUE, 0);

}

void loop() {
    webSocket.loop();
    server.handleClient();
}
```



# Робота з бібліотеками `ESP8266`



### Функції формування часових затримок
    
Функції `millis()` і `micros()` повертають кількість мілісекунд і мікросекунд, що минули після скидання (`RESET`).
    
Функція `delay(ms)` призупиняє роботу основної програми на заданий час в мілісекундах і резервує цей час для обробки завдань `Wi-Fi` та `TCP/IP`. 

Функція `delayMicroseconds(us)` призначена для паузи на задане число мікросекунд.
    
> Пам'ятайте, що для стабільної роботи `Wi-Fi` потрібно періодично виділяти для нього час. Функції з бібліотек`Wi-Fi` і `TCP/IP`  отримують можливість обробляти свої події щоразу після проходження функції `loop()` або у разі виклику функції `delay`. 
    
Якщо алгоритм оброблення в `Loop()` займає час більше ніж 50 мс, то слід подбати про виклик `delay(0)` саме для підтримки нормальної роботи `Wi-Fi`. Для цього також можливо використовувати функцію `yield()`, яка є еквівалентною `delay(0)`. 

> Функція  `delayMicroseconds()` не поступається часом виконання іншим завданням, тому використання її для затримки більш ніж на 20 мілісекунд не рекомендується.


### Бібліотека "Ticker". Формування періодичних подій за перериваннями від таймера

Ця бібліотека призначена для програмного переривання за таймером. 

Щоб підключити переривання, для початку треба підключити бібліотеку :
```c
#include <Ticker.h>
```

Далі створюємо один або декілька екземплярів переривань, залежно від потреби:
```c
Ticker name, name2;
```

Для створених екземплярів `name` та `name2` ми можемо налаштувати переривання, що будуть формуватися з заданою періодичністю. 

Налаштування періодичності можливо здійснити за допомогою функцій `attach` та `attach_ms` з параметрами для визначення періоду в секундах (`seconds`) або ()мілісекундах `miliseconds`)  та функції `callback`, що має бути викликана щоразу при виникнені переривання.

``` c
name.attach(seconds, callback);
name2.attach_ms(miliseconds, callback2);
```

До функції `callback` також можливо додати аргументи `arg`:

``` c
name.attach(seconds, callback, arg);
name2.attach_ms(miliseconds, callback, arg);
```


Отже `callback` - це ім’я функції, що буде викликатися щоразу при перериванні, а її аргумент `arg` може бути лише один. 

Для налаштування формування переривання лише раз треба використовувати функції, що дуже подібні до попередніх:

``` c
name.once(seconds, callback);
name.once(seconds, callback, arg);
name.once_ms(miliseconds, callback);
name.once_ms(miliseconds, callback, arg);
```

Існує ще дві не менш важливі функції  – `detach`, що відключає переривання та `active`, що повертає стан переривання у форматі `bool`.
``` c
name.detach();
bool check = name.active();
```


> Також існує бібліотека [TickerScheduler](https://github.com/Toshik/TickerScheduler), що базується на `Ticker` і дозволяє працювати з `Task` та допомагає уникнути проблем з сторожовим таймером `WDT`. 

Приклад:

```c
void setup() {

}

void loop() {

}
```

### Спеціальні функції та команди для ESP8266

Спеціальні функції ESP пов'язані з режимом глибокого сну, RTC (точного часу) і флеш-пам'яті. Дані функції доступні в об'єкті – `ESP`. 

Так, наприклад, функція `ESP.deepSleep(microseconds, mode)` переводить модуль в режим глибокого сну. Параметр mode може приймати значення: 
* `WAKE_RF_DEFAULT`,  
* `WAKE_RFCAL`,  
* `WAKE_NO_RFCAL`,  
* `WAKE_RF_DISABLED`. 

Для виходу з режиму глибокого сну, треба з'єднати GPIO16 з RESET.

Функції `ESP.rtcUserMemoryWrite(offset, & data, sizeof (data))` та `ESP.rtcUserMemoryRead(offset, & data, sizeof (data))` дозволяють записувати та зчитувати дані з пам'яті `RTC`. Загальний розмір пам'яті `RTC` складає 512 байт, тому `offset + sizeof(data)` не повинні перевищувати 512. Змінна – `data` повинна бути рівна 4-м байтам. Збережені дані можуть зберігатися між циклами глибокого сну. 

> Інформація в `RTC` втачається після вимикання живлення.

Функції `ESP.wdtEnable()`, `ESP.wdtDisable()` і `ESP.wdtFeed()` керують сторожовим таймером.

Функція | Результат виконання
--- | --- 
`ESP.reset()` | Перезавантаження модуля
`ESP.getResetReason()` | Отримання інформації у форматі String про причину виникнення RESET.
`ESP.getFreeHeap()` | Визначити розмір вільної пам'яті
`ESP.getCoreVersion()`| Отримання інформації у форматі String з версіэю ядра процесора.
`ESP.getSdkVersion()` | Отримання інформації про версію SDK у форматі char.
`ESP.getCpuFreqMHz()` | Отримання інформації про значення частоти процесора в МГц у форматі uint 8-bit.
`ESP.getSketchSize()` | Отримання інформації про розмір завантаженого в модуль скетчу у форматі uint 32-bit.
`ESP.getFreeSketchSpace()` | Отримання інформації про наявнеий вільний простір для скетчу у формматі uint 32-bit.
`ESP.getSketchMD5()` | MD5 хеш поточного скетчу.
`ESP.getChipId()` | Отримання інформації про Id чіпа ESP8266 у форматі int 32bit
`ESP.getFlashChipId()` | Отримання інформації про Id чіпа  flash пам'яті у форматі int 32bit
`ESP.getFlashChipSize()` | Отримання інформації про розмір flash пам'яті в байтах, так, як його визначає SDK (може бути менше реального розміру).
`ESP.getFlashChipRealSize()` | Отримання інформації про дійсний розмір чіпа flash пам'яті в байтах на основі flash chip ID.
`ESP.getFlashChipSpeed(void)` | Отримання інформації про  частоту флеш пам'яті, в Герцах.
`ESP.getCycleCount()` | Отримання інформації про  кількість циклів CPU з моменту старту у форматі unsigned 32-bit. Функція може бути корисна для формування точних затримок.
`ESP.getVcc()` |  Отримання інформації про значення напруги живлення (потребує додаткового налаштування під час ініціалізації мікроконтролера)

> Для роботи функції `ESP.getVcc()` ESP має переналаштувати АЦП під час запуску. Додайте наступний рядок у верхній частині скетча, щоб скористатися цією функцією:
>``` c
>ADC_MODE(ADC_VCC);
>```
>
>Пін A0 (АЦП) не повинен бути задіяний периферією в цьому режимі.
Зверніть увагу, що по замовчанню АЦП налаштовується для зчитування напруги за допомогою `analogRead(A0)` і функція `ESP.getVCC()` недоступна.


Приклад:

```c
void setup() {

}

void loop() {

}
```


Installation
============

```bash
$ wget https://raw.githubusercontent.com/ekalinin/github-markdown-toc/master/gh-md-toc
$ chmod a+x gh-md-toc
```

Usage
=====


STDIN
-----

Here's an example of TOC creating for markdown from STDIN:

```bash
➥ cat ~/projects/Dockerfile.vim/README.md | ./gh-md-toc -
  * [Dockerfile.vim](#dockerfilevim)
  * [Screenshot](#screenshot)
  * [Installation](#installation)
        * [OR using Pathogen:](#or-using-pathogen)
        * [OR using Vundle:](#or-using-vundle)
  * [License](#license)
```

Local files
-----------

Here's an example of TOC creating for a local README.md:

```bash
➥ ./gh-md-toc ~/projects/Dockerfile.vim/README.md                                                                                                                                                Вс. марта 22 22:51:46 MSK 2015

Table of Contents
=================

  * [Dockerfile.vim](#dockerfilevim)
  * [Screenshot](#screenshot)
  * [Installation](#installation)
        * [OR using Pathogen:](#or-using-pathogen)
        * [OR using Vundle:](#or-using-vundle)
  * [License](#license)
```

Remote files
------------

And here's an example, when you have a README.md like this:

  * [README.md without TOC](https://github.com/ekalinin/envirius/blob/f939d3b6882bfb6ecb28ef7b6e62862f934ba945/README.md)

And you want to generate TOC for it.

There is nothing easier:

```bash
➥ ./gh-md-toc https://github.com/ekalinin/envirius/blob/master/README.md

Table of Contents
=================

  * [envirius](#envirius)
    * [Idea](#idea)
    * [Features](#features)
  * [Installation](#installation)
  * [Uninstallation](#uninstallation)
  * [Available plugins](#available-plugins)
  * [Usage](#usage)
    * [Check available plugins](#check-available-plugins)
    * [Check available versions for each plugin](#check-available-versions-for-each-plugin)
    * [Create an environment](#create-an-environment)
    * [Activate/deactivate environment](#activatedeactivate-environment)
      * [Activating in a new shell](#activating-in-a-new-shell)
      * [Activating in the same shell](#activating-in-the-same-shell)
    * [Get list of environments](#get-list-of-environments)
    * [Get current activated environment](#get-current-activated-environment)
    * [Do something in environment without enabling it](#do-something-in-environment-without-enabling-it)
    * [Get help](#get-help)
    * [Get help for a command](#get-help-for-a-command)
  * [How to add a plugin?](#how-to-add-a-plugin)
    * [Mandatory elements](#mandatory-elements)
      * [plug_list_versions](#plug_list_versions)
      * [plug_url_for_download](#plug_url_for_download)
      * [plug_build](#plug_build)
    * [Optional elements](#optional-elements)
      * [Variables](#variables)
      * [Functions](#functions)
    * [Examples](#examples)
  * [Example of the usage](#example-of-the-usage)
  * [Dependencies](#dependencies)
  * [Supported OS](#supported-os)
  * [Tests](#tests)
  * [Version History](#version-history)
  * [License](#license)
  * [README in another language](#readme-in-another-language)
```

That's all! Now all you need — is copy/paste result from console into original
README.md.

And here is a result:

  * [README.md with TOC](https://github.com/ekalinin/envirius/blob/24ea3be0d3cc03f4235fa4879bb33dc122d0ae29/README.md)

Moreover, it's able to work with GitHub's wiki pages:

```bash
➥ ./gh-md-toc https://github.com/ekalinin/nodeenv/wiki/Who-Uses-Nodeenv

Table of Contents
=================

  * [Who Uses Nodeenv?](#who-uses-nodeenv)
    * [OpenStack](#openstack)
    * [pre-commit.com](#pre-commitcom)
```

Multiple files
--------------

It supports multiple files as well:

```bash
➥ ./gh-md-toc \
    https://github.com/aminb/rust-for-c/blob/master/hello_world/README.md \
    https://github.com/aminb/rust-for-c/blob/master/control_flow/README.md \
    https://github.com/aminb/rust-for-c/blob/master/primitive_types_and_operators/README.md \
    https://github.com/aminb/rust-for-c/blob/master/unique_pointers/README.md

  * [Hello world](https://github.com/aminb/rust-for-c/blob/master/hello_world/README.md#hello-world)

  * [Control Flow](https://github.com/aminb/rust-for-c/blob/master/control_flow/README.md#control-flow)
    * [If](https://github.com/aminb/rust-for-c/blob/master/control_flow/README.md#if)
    * [Loops](https://github.com/aminb/rust-for-c/blob/master/control_flow/README.md#loops)
    * [For loops](https://github.com/aminb/rust-for-c/blob/master/control_flow/README.md#for-loops)
    * [Switch/Match](https://github.com/aminb/rust-for-c/blob/master/control_flow/README.md#switchmatch)
    * [Method call](https://github.com/aminb/rust-for-c/blob/master/control_flow/README.md#method-call)

  * [Primitive Types and Operators](https://github.com/aminb/rust-for-c/blob/master/primitive_types_and_operators/README.md#primitive-types-and-operators)

  * [Unique Pointers](https://github.com/aminb/rust-for-c/blob/master/unique_pointers/README.md#unique-pointers)
```

Combo
-----

You can easily combine both ways:

```bash
➥ ./gh-md-toc \
    ~/projects/Dockerfile.vim/README.md \
    https://github.com/ekalinin/sitemap.s/blob/master/README.md

  * [Dockerfile.vim](~/projects/Dockerfile.vim/README.md#dockerfilevim)
  * [Screenshot](~/projects/Dockerfile.vim/README.md#screenshot)
  * [Installation](~/projects/Dockerfile.vim/README.md#installation)
        * [OR using Pathogen:](~/projects/Dockerfile.vim/README.md#or-using-pathogen)
        * [OR using Vundle:](~/projects/Dockerfile.vim/README.md#or-using-vundle)
  * [License](~/projects/Dockerfile.vim/README.md#license)

  * [sitemap.js](https://github.com/ekalinin/sitemap.js/blob/master/README.md#sitemapjs)
    * [Installation](https://github.com/ekalinin/sitemap.js/blob/master/README.md#installation)
    * [Usage](https://github.com/ekalinin/sitemap.js/blob/master/README.md#usage)
    * [License](https://github.com/ekalinin/sitemap.js/blob/master/README.md#license)

Created by [gh-md-toc](https://github.com/ekalinin/github-markdown-toc)
```

Auto insert and update TOC
--------------------------

Just put into a file these two lines:

```
<!--ts-->
<!--te-->
```

And run:

```bash
$ ./gh-md-toc --insert README.test.md

Table of Contents
=================

   * [gh-md-toc](#gh-md-toc)
   * [Installation](#installation)
   * [Usage](#usage)
      * [STDIN](#stdin)
      * [Local files](#local-files)
      * [Remote files](#remote-files)
      * [Multiple files](#multiple-files)
      * [Combo](#combo)
   * [Tests](#tests)
   * [Dependency](#dependency)

!! TOC was added into: 'README.test.md'
!! Origin version of the file: 'README.test.md.orig.2018-02-04_192655'
!! TOC added into a separate file: 'README.test.md.toc.2018-02-04_192655'


Created by [gh-md-toc](https://github.com/ekalinin/github-markdown-toc)
```

Now check the same file:

```bash
➜ grep -A15 "<\!\-\-ts" README.test.md
<!--ts-->
   * [gh-md-toc](#gh-md-toc)
   * [Table of contents](#table-of-contents)
   * [Installation](#installation)
   * [Usage](#usage)
      * [STDIN](#stdin)
      * [Local files](#local-files)
      * [Remote files](#remote-files)
      * [Multiple files](#multiple-files)
      * [Combo](#combo)
      * [Auto insert and update TOC](#auto-insert-and-update-toc)
   * [Tests](#tests)
   * [Dependency](#dependency)

<!-- Added by: <your-user>, at: 2018-02-04T19:38+03:00 -->

<!--te-->
```

Next time when your file will be changed just repeat the command (`./gh-md-toc
--insert ...`) and TOC will be refreshed again.


Tests
=====

Done with [bats](https://github.com/sstephenson/bats).
Useful articles:

  * https://blog.engineyard.com/2014/bats-test-command-line-tools
  * http://blog.spike.cx/post/60548255435/testing-bash-scripts-with-bats


How to run tests:

```bash
➥ make test                                                                                                                                                                                                      Пн. марта 23 13:59:27 MSK 2015
 ✓ TOC for local README.md
 ✓ TOC for remote README.md
 ✓ TOC for mixed README.md (remote/local)
 ✓ TOC for markdown from stdin
 ✓ --help
 ✓ --version

6 tests, 0 failures
```

Dependency
==========

  * curl or wget
  * awk (mawk, gawk is not supported)
  * grep
  * sed
  * bats (for unit tests)

Tested on Ubuntu 14.04/14.10 in bash/zsh.



### An h3 header ###



$$I = \int \rho R^{2} dV$$

And note that you can backslash-escape any punctuation characters
which you wish to be displayed literally, ex.: \`foo\`, \*bar\*, etc.

```math #yourmathlabel
a + b = c
```
h<sub>&theta;</sub>(x) = &theta;<sub>o</sub> x + &theta;<sub>1</sub>x

![equation](http://www.sciweavers.org/tex2img.php?eq=1%2Bsin%28mc%5E2%29&bc=White&fc=Black&im=jpg&fs=12&ff=arev&edit=)
<img src="https://latex.codecogs.com/svg.latex?\Large&space;x=\frac{-b\pm\sqrt{b^2-4ac}}{2a}" title="\Large x=\frac{-b\pm\sqrt{b^2-4ac}}{2a}" />

![\Large x=\frac{-b\pm\sqrt{b^2-4ac}}{2a}](https://latex.codecogs.com/svg.latex?x%3D%5Cfrac%7B-b%5Cpm%5Csqrt%7Bb%5E2-4ac%7D%7D%7B2a%7D)

$ \sum_{\forall i}{x_i^{2}} $


Приклади оформлення:
---
<details><summary>stuff with *mark* **down**</summary><p>

## _formatted_ **heading** with [a](link)

---
{{standard 3-backtick code block omitted from here due to escaping issues}}
---

Collapsible until here.
</p></details>

Colons can be used to align columns.

| Tables        | Are           | Cool  |
| ------------- |:-------------:| -----:|
| col 3 is      | right-aligned | $1600 |
| col 2 is      | centered      |   $12 |
| zebra stripes | are neat      |    $1 |

