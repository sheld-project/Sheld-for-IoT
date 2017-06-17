/* main.cpp

"Shellder" のメインソースコード.
*/

#include <string>
#include <Arduino.h>

#include "./interface/wifi.cpp"
#include "./interface/sd.cpp"


WiFi_ *wifi;
SD_ *sd;
static std::string config;

void setup()
{
  Serial.begin(115200);

  // SD接続
  sd = new SD_("config", 16);
  while (!sd->connect()){
  }  // 接続待ち

  // SD読み取り
  config = sd->readfFile();
  // 接続を切る
  delete sd;

  // Wifi接続
  wifi = new WiFi_("netoneto-NET","pythonhaiizo");
  wifi->connectWifi();

  Serial.print("Connect");

  // IPアドレス
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  // サーバの立ち上げ
  wifi->setServer();
  Serial.print("start");
}

void loop()
{
  std::string packet = "";

  // データの受け取り
  packet = wifi->tcpStream();
  Serial.print(packet.c_str());
}
