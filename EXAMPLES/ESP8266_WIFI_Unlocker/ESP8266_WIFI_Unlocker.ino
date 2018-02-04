#include <ESP8266WiFi.h>

const char *ssid = "DELTA_unlocker";
const char *password = "12345678";

unsigned long previousMillis = 0;
const long interval = 7000;
const int SleepTime = 7;

bool ConnectFlag = false;

WiFiEventHandler stationConnectedHandler; // событие - соединение
WiFiEventHandler stationDisconnectedHandler; // событие - разъединение

void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT); // реле на GPIO13 (D7)
  digitalWrite(13, HIGH); // начальное значение
  WiFi.persistent(false); // бережем флеш-память, не перезаписываем данные подключения, если они не изменились с прошлой загрузки
  WiFi.mode(WIFI_AP); // Режим точки доступа
  WiFi.softAP(ssid, password);

  stationConnectedHandler = WiFi.onSoftAPModeStationConnected(&onStationConnected); // при соединении переходим к функции
  stationDisconnectedHandler = WiFi.onSoftAPModeStationDisconnected(&onStationDisconnected); // при разъединении переходим к функции

}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval && ConnectFlag == false) {
    previousMillis = currentMillis;
    Serial.println("Sleep "+String(SleepTime)+" Sec.");
    ESP.deepSleep(SleepTime * 1000000, WAKE_RFCAL);
  } 
}

void onStationConnected(const WiFiEventSoftAPModeStationConnected& evt) { // при коннекте - включаем реле
  Serial.print("CONNECTED: ");
  digitalWrite(13, LOW);
  ConnectFlag = true;
  Serial.println(macToString(evt.mac)); // МАС-адрес в порт
}

void onStationDisconnected(const WiFiEventSoftAPModeStationDisconnected& evt) { // при дисконнекте - выключаем реле
  Serial.print("DISCONNECTED: ");
  digitalWrite(13, HIGH);
  ConnectFlag = false;
  Serial.println(macToString(evt.mac)); // МАС-адрес в порт
}

String macToString(const unsigned char* mac) { // Получаем МАС-адрес клиента в виде строки (может пригодиться при идентификации)
  char buf[20];
  snprintf(buf, sizeof(buf), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  return String(buf);
}
