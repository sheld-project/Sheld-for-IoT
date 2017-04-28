/* main.cpp

"Shellder" のメインソースコード.
*/

#include <Arduino.h>

#include "./interface/wifi.cpp"


WiFi_ *wifi;

void setup()
{
  Serial.begin(9600);

  // 接続
  wifi = new WiFi_("ssid","pass");
  wifi->connectWifi();

  Serial.print("Connect");

  // IPアドレス
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  // サーバの立ち上げ
  wifi->set_server();
  Serial.print("start");
}

void loop()
{
  std::string packet = "";

  // データの受け取り
  packet = wifi->tcpStream();
  Serial.print(packet.c_str());
}
