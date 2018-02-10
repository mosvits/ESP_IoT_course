**Soft Access Point Class**

Section below is ESP8266 specific as \ `*Arduino WiFi
library* <https://www.arduino.cc/en/Reference/WiFi>`__ documentation
does not cover soft access point. The API description is broken down
into three short chapters. They cover how to setup soft-AP, manage
connection, and obtain information on soft-AP interface configuration.

Нижче наведено лише специфікація ESP8266, оскільки бібліотека `*Arduino
WiFi* <https://www.arduino.cc/en/Reference/WiFi>`__ не охоплює точку
доступу. Опис API складається з трьох коротких розділів. Вони охоплюють
налаштування soft-AP, керування з'єднанням і отримування інформації про
конфігурацію soft-AP.

**Set up Network**

This section describes functions to set up and configure ESP8266 in the
soft access point (soft-AP) mode.

У цьому розділі описуються додаткові опції для налаштування і
конфігурації ESP8266 в обмеженій точці доступу (soft-AP).

**softAP**

Set up a soft access point to establish a Wi-Fi network.

Налаштування обмеженої точки доступу для встановлення мережі Wi-Fi.

The simplest version (`*an overload in C++
terms* <https://en.wikipedia.org/wiki/Function_overloading>`__) of this
function requires only one parameter and is used to set up an open Wi-Fi
network.

Найпростіша версія (`*перевантаження фукцій
C++* <https://uk.wikipedia.org/wiki/%D0%9F%D0%B5%D1%80%D0%B5%D0%B2%D0%B0%D0%BD%D1%82%D0%B0%D0%B6%D0%B5%D0%BD%D0%BD%D1%8F_%D1%84%D1%83%D0%BD%D0%BA%D1%86%D1%96%D1%97>`__)
цієї функції вимагає лише одного параметра і використовується для
налаштування відкритої мережі Wi-Fi.

WiFi\ **.**\ softAP(ssid)

To set up password protected network, or to configure additional network
parameters, use the following overload:

Щоб налаштувати захищену паролем мережу або налаштувати додаткові
параметри мережі, скористайтеся наступним перевантаженням:

WiFi\ **.**\ softAP(ssid, password, channel, hidden)

The first parameter of this function is required, remaining three are
optional.

Необхідним є лише перший параметр цієї функції, решта три є
необов'язковими.

Meaning of all parameters is as follows: - ssid - character string
containing network SSID (max. 63 characters) \* password- optional
character string with a password. For WPA2-PSK network it should be at
least 8 character long. If not specified, the access point will be open
for anybody to connect. \* channel- optional parameter to set Wi-Fi
channel, from 1 to 13. Default channel = 1. \* hidden - optional
parameter, if set to true will hide SSID

Зміст параметрів – наступний:

ssid - символьна рядок, що містить мережевий
`*SSID* <https://uk.wikipedia.org/wiki/SSID>`__ (не більше 63 символів).

password - необов'язковий символьний рядок з паролем. Для мережі
WPA2-PSK він повинен бути довжиною не менше 8 символів. Якщо його не
вказати, то точка доступу буде відкрита для підключення будь-кого (не
забувайте що ця точка може підтримувати лише 5 клієнтів одночасно).

channel - необов'язковий параметр, який необхідний щоб встановити канал
Wi-Fi, від 1 до 13. Канал за умовчанням – 1.

hidden - необов'язковий логічний параметр, при встановлені значення
true, буде приховуватися SSID

Function will return true or false depending on result of setting the
soft-AP.

Функція повертає true або false залежно від результату налаштування
soft-AP.

Notes: \* The network established by softAP will have default IP address
of 192.168.4.1. This address may be changed using softAPConfig (see
below). \* Even though ESP8266 can operate in soft-AP + station mode, it
actually has only one hardware channel. Therefore in soft-AP + station
mode, the soft-AP channel will default to the number used by station.
For more information how this may affect operation of stations connected
to ESP8266’s soft-AP, please check \ `*this FAQ
entry* <http://bbs.espressif.com/viewtopic.php?f=10&t=324>`__\ on
Espressif forum.

Примітки: Мережа, створена як softAP, матиме IP-адресу за замовчуванням
**192.168.4.1**. Ця адреса може бути змінена за допомогою softAPConfig
(див. нижче). Незважаючи на те, що ESP8266 може працювати в режимі
soft-AP + station, він насправді має лише один апаратний канал. Тому в
режимі soft-AP + station канал soft-AP буде за замовчуванням
використовувати той самий канал приєднаної станції. Щоб отримати
додаткові відомості про те, як це може вплинути на роботу станцій,
підключених до soft-AP ESP8266, будь ласка, ознайомтеся з цим
`*FAQ* <http://bbs.espressif.com/viewtopic.php?f=10&t=324>`__ на форумі
Espressif.

**softAPConfig**

Configure the soft access point’s network interface.

Налаштування мережевого інтерфейсу обмеженої точки доступу.

softAPConfig (local\_ip, gateway, subnet)

All parameters are the type of IPAddress and defined as follows:
\* local\_ip - IP address of the soft access point \* gateway - gateway
IP address

\* subnet - subnet mask

Всі параметри є типом
`*IPAddress* <https://github.com/esp8266/Arduino/blob/master/cores/esp8266/IPAddress.h>`__
і визначені наступним чином:

local\_ip - IP-адреса обмеженої точки доступу

gateway - IP-адреса шлюзу

subnet - маска підмережі

Function will return true or false depending on result of changing the
configuration.

Функція повертає true  або false залежно від результату зміни
конфігурації.

*Приклад коду:*

#include <ESP8266WiFi.h>

IPAddress local\_IP(192,168,4,22);

IPAddress gateway(192,168,4,9);

IPAddress subnet(255,255,255,0);

void setup()

{

Serial.begin(115200);

Serial.println();

Serial.print("Setting soft-AP configuration ... ");

Serial.println(WiFi.softAPConfig(local\_IP, gateway, subnet) ? "Ready" :
"Failed!");

Serial.print("Setting soft-AP ... ");

Serial.println(WiFi.softAP("ESPsoftAP\_01") ? "Ready" : "Failed!");

Serial.print("Soft-AP IP address = ");

Serial.println(WiFi.softAPIP());

}

void loop() {}

*Приклад виводу:*

Setting soft\ **-**\ AP configuration **...** Ready

Setting soft\ **-**\ AP **...** Ready

Soft\ **-**\ AP IP address **=** 192.168\ **.**\ 4.22

**Manage Network**

Once soft-AP is established you may check the number of stations
connected, or shut it down, using the following functions.

Після встановлення soft-AP ви можете перевірити кількість підключень або
скинути їх за допомогою наступних функцій.

**softAPgetStationNum**

Get the count of the stations that are connected to the soft-AP
interface.

Для отримання кількості станцій, підключених до soft-AP.

WiFi\ **.**\ softAPgetStationNum()

*Приклад коду:*

Serial\ **.**\ printf("Stations connected to soft-AP = %d\\n",
WiFi\ **.**\ softAPgetStationNum());

*Приклад виводу:*

Stations connected to soft\ **-**\ AP **=** 2

Note: the maximum number of stations that may be connected to ESP8266
soft-AP is five.

Примітка. Максимальна кількість станцій, які можуть бути підключені до
ESP8266 soft-AP, становить **п'ять**.

**softAPdisconnect**

Disconnect stations from the network established by the soft-AP.

Для відключення станцій від мережі soft-AP.

WiFi\ **.**\ softAPdisconnect(wifioff)

Function will set currently configured SSID and password of the soft-AP
to null values. The parameter wifioff is optional. If set to true it
will switch the soft-AP mode off.

Функція встановлює поточний набір SSID та пароль soft-AP на нульові
значення. Параметр wifioff є необов'язковим. Якщо встановлено значення –
true, він вимкне режим soft-AP.

Function will return true if operation was successful or false if
otherwise.

Функція повертає true , якщо операція була успішною, інакше - false.

**Network Configuration**

Functions below provide IP and MAC address of ESP8266’s soft-AP.

Нижче описані функції що забезпечують IP та MAC адресу soft-AP ESP8266.

**softAPIP**

Return IP address of the soft access point’s network interface.

Для повернення IP-адреси точки доступу.

WiFi\ **.**\ softAPIP()

Returned value is of IPAddress type.

Повернене значення має тип
`IPAddress <https://github.com/esp8266/Arduino/blob/master/cores/esp8266/IPAddress.h>`__.

*Приклад коду:*

Serial\ **.**\ print("Soft-AP IP address = ");

Serial\ **.**\ println(WiFi\ **.**\ softAPIP());

*Приклад виводу:*

Soft\ **-**\ AP IP address **=** 192.168\ **.**\ 4.1

**softAPmacAddress**

Return MAC address of soft access point. This function comes in two
versions, which differ in type of returned values. First returns a
pointer, the second a String.

Повернення MAC-адреси обмеженої точки доступу. Ця функція представлена в
двох версіях, які відрізняються за типом повернутих значень. Перша
повертає – вказівник, друга – String.

**Pointer to MAC**

WiFi\ **.**\ softAPmacAddress(mac)

Function accepts one parameter mac that is a pointer to memory location
(an uint8\_t array the size of 6 elements) to save the mac address. The
same pointer value is returned by the function itself.

Функція приймає один параметр – mac, який є вказівником на розташування
пам'яті (масив uint8\_t розміром 6 елементів) для збереження MAC-адреси.
Той самий вказівник змінної повертається самою функцією..

*Приклад коду:*

uint8\_t macAddr[6];

WiFi\ **.**\ softAPmacAddress(macAddr);

Serial\ **.**\ printf("MAC address = %02x:%02x:%02x:%02x:%02x:%02x\\n",
macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5]);

*Приклад виводу:*

MAC address **=** 5e:cf:7f:8b:10:13

**MAC as a String**

Optionally you can use function without any parameters that returns
a String type value.

За бажанням, ви можете використовувати функцію без будь-яких параметрів,
що повертає значення типу – String .

WiFi\ **.**\ softAPmacAddress()

*Приклад коду:*

Serial\ **.**\ printf("MAC address = %s\\n",
WiFi\ **.**\ softAPmacAddress()\ **.**\ c\_str());

*Приклад виводу:*

MAC address **=** 5E:CF:7F:8B:10:13

For code samples please refer to separate section
with \ `examples <http://arduino-esp8266.readthedocs.io/en/2.4.0/esp8266wifi/soft-access-point-examples.html>`__ dedicated
specifically to the Soft Access Point Class.

**EXAMPLES**

Soft Access Point
=================

Example below presents how to configure ESP8266 to run in soft access
point mode so Wi-Fi stations can connect to it. The Wi-Fi network
established by the soft-AP will be identified with the SSID set during
configuration. The network may be protected with a password. The network
may be also open, if no password is set during configuration.

Нижче наведено приклад, як налаштувати ESP8266 для роботи в режимі
обмеженої точки доступу, щоб Wi-Fi станції могли підключитися до неї.
Мережа Wi-Fi, створена soft-AP, буде ідентифікована під час налаштування
SSID. Мережа може бути захищена паролем, або бути відкритою, якщо під
час налаштування пароль не встановлено.

The Sketch
----------

Setting up soft-AP with ESP8266 can be done with just couple lines of
code.

Налаштування soft-AP з ESP8266 можна виконати кількома рядками коду.

*#include <ESP8266WiFi.h>*

void setup()

{

Serial\ **.**\ begin(115200);

Serial\ **.**\ println();

Serial\ **.**\ print("Setting soft-AP ... ");

boolean result **=** WiFi\ **.**\ softAP("ESPsoftAP\_01",
"pass-to-soft-AP");

**if**\ (result **==** true)

{

Serial\ **.**\ println("Ready");

}

**else**

{

Serial\ **.**\ println("Failed!");

}

}

void loop()

{

Serial\ **.**\ printf("Stations connected = %d\\n",
WiFi\ **.**\ softAPgetStationNum());

delay(3000);

}

How to Use It?
--------------

In
line boolean result = WiFi.softAP("ESPsoftAP\_01", "pass-to-soft-AP")change pass-to-soft-AP to
some meaningful password and upload sketch. Open serial monitor and you
should see:

В рядку boolean result = WiFi.softAP("ESPsoftAP\_01", "pass-to-soft-AP")
змініть пароль – pass-to-soft-AP на більш значущий і завантажити скетч.
Відкривши послідовний монітор, ви повинні побачити:

Setting soft\ **-**\ AP **...** Ready

Stations connected **=** 0

Stations connected **=** 0

**...**

Then take your mobile phone or a PC, open the list of available access
points, find ESPsoftAP\_01 and connect to it. This should be reflected
on serial monitor as a new station connected:

Потім візьміть свій мобільний телефон або ПК, відкрийте список доступних
точок доступу, знайдіть ESPsoftAP\_01 та підключіться до нього. Це
повинно відобразитися на послідовному моніторі в якості нової
підключеної станції:

Stations connected **=** 1

Stations connected **=** 1

**...**

If you have another Wi-Fi station available then connect it as well.
Check serial monitor again where you should now see two stations
reported.

Якщо у вас є інша доступна Wi-Fi станція, підключіть її також. Перевірте
послідовний монітор знову, де ви тепер повинні побачити дві станції, про
які повідомляється.

How Does it Work?
-----------------

Sketch is small so analysis shouldn’t be difficult. In first line we are
including ESP8266WiFi library:

Програма невеличка, тому аналіз не повинен бути складним. У першому
рядку ми підключаємо
`*ESP8266WiFi* <https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi>`__
бібліотеку:

*#include <ESP8266WiFi.h>*

Setting up of the access point ESPsoftAP\_01 is done by executing:

Налаштування точки доступу ESPsoftAP\_01 виконується шляхом виконання:

boolean result = WiFi.softAP("ESPsoftAP\_01", "pass-to-soft-AP");

If this operation is successful then result will be true or false if
otherwise. Basing on that either Ready or Failed! will be printed out by
the following if - else conditional statement.

Якщо ця операція буде успішною, то результат буде true або false в
іншому випадку. Виходячи з цього, Ready  або Failed! буде роздрукований
наступним умовним твердженням if - else.

Can we Make it Simpler?
-----------------------

Can we make this sketch even simpler? Yes, we can! We can do it by using
alternate if - else statement as below:

Чи можемо ми зробити цей приклад ще простіше? Так, ми можемо! Ми можемо
зробити це, використовуючи альтернативний оператор if - else, як
показано нижче:

WiFi.softAP("ESPsoftAP\_01", "pass-to-soft-AP") ? "Ready" : "Failed!"

Such statement will return either Ready or Failed! depending on result
of WiFi.softAP(...). This way we can considerably shorten our sketch
without any changes to functionality:

Таке твердження поверне або Ready, або Failed! в залежності від
результату WiFi.softAP(...). Таким чином ми можемо значно скоротити наш
приклад без будь-яких змін у функціональності:

#include <ESP8266WiFi.h>

void setup()

{

Serial.begin(115200);

Serial.println();

Serial.print("Setting soft-AP ... ");

Serial.println(WiFi.softAP("ESPsoftAP\_01", "pass-to-soft-AP") ? "Ready"
: "Failed!");

}

void loop()

{

Serial.printf("Stations connected = %d\\n", WiFi.softAPgetStationNum());

delay(3000);

}

I believe this is very neat piece of code. If ? : conditional operator
is new to you, I recommend to start using it and make your code shorter
and more elegant.

Я вважаю, що це дуже витончений фрагмент коду. Якщо умовний оператор – ?
: є новим для вас, я рекомендую почати використовувати його і зробити
ваш код коротшим і елегантним.

Conclusion
----------

`*ESP8266WiFi* <https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi>`__ library
makes it easy to turn ESP8266 into soft access point.

`*ESP8266WiFi* <https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi>`__
бібліотека дозволяє легко перетворити ESP8266 в обмежену точку доступу.

Once you try above sketch check
out \ `*WiFiAccessPoint.ino* <https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/examples/WiFiAccessPoint/WiFiAccessPoint.ino>`__ as
a next step. It demonstrates how to access ESP operating in soft-AP mode
from a web browser.

Як тільки ви пройшли всі приклади, наступним кроком спробуйте розібрати
програму -
`*WiFiAccessPoint.ino* <https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/examples/WiFiAccessPoint/WiFiAccessPoint.ino>`__.
Вона демонструє, як отримати доступ до ESP, що працює в режимі soft-AP з
веб-браузера.

For the list of functions to manage ESP module in soft-AP mode please
refer to the \ `Soft Access Point
Class <http://arduino-esp8266.readthedocs.io/en/2.4.0/esp8266wifi/soft-access-point-class.html>`__ documentation.
