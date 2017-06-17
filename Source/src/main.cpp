/* main.cpp

"Shellder" のメインソースコード.
*/

#include <string>
#include <vector>

#include <Arduino.h>

#include "./interface/wifi.cpp"
#include "./interface/sd.cpp"
#include "./tool.cpp"

WiFi_ *wifi;
SD_ *sd;
Tool *tool;
std::vector<std::string> config;


void setup()
{
  Serial.begin(115200);

  tool = new Tool();

  // SD接続
  sd = new SD_("config", 16);
  while (!sd->connect()){
  }  // 接続待ち

  // SD内のコンフィグを読み取り
  std::string config_str = sd->readfFile();
  config = tool->split(config_str,'\n');

  // 接続を切る
  delete sd;

  Serial.print(config_str.c_str());
  Serial.print("Get Config");


  // Wifi接続
  wifi = new WiFi_(config[0], config[1]);
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

  // チェック
  bool is_secure_packet = tool -> checkInTarget(packet, config);
  if(is_secure_packet){
    Serial.print(packet.c_str());
  }else{
    Serial.print("not secure packet");
  }
}
