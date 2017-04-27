/* main.cpp

"Shellder" のメインソースコード.
*/

#include <Arduino.h>

#include "./interface/wifi.cpp"


WiFi_ *wifi;

void setup()
{
  bool is_connected = false;
  while (!is_connected)
  {
    // 接続
    wifi = new WiFi_("ssid","password","host");
    is_connected = wifi->connectWifi();
    delay(50);
  }
}

void loop()
{
  std::string result = "";
  // クライアントを待つ
  wifi->waitClient();

  while(true)
  {
    // データの受け取り
    result += wifi->tcpStream();
  }
}
