/* wifi.cpp
Wi-Fiの制御＆インターフェース.
*/

#include <string>
#include <map>

#include <ESP8266WiFi.h>


/* --- Wi-Fi制御クラス --- */
class WiFi_
{
private:
  // プロパティ（ID,パスワード,ホスト）
  std::map<std::string, std::string> CONNECTION_PROPERTY =
  {
      {"SSID",""},
      {"PASS",""},
  };
  WiFiServer server  = WiFiServer(4000);


public:
  /* プロパティの初期化 */
  WiFi_(
    std::string arg_ssid,
    std::string arg_password
  )
  {
    CONNECTION_PROPERTY["SSID"] = arg_ssid;
    CONNECTION_PROPERTY["PASS"] = arg_password;
  }

  /* Wi-Fiに接続する */
  void connectWifi()
  {
    // 接続
    WiFi.mode(WIFI_STA);
    WiFi.begin("netoneto-NET","pythonhaiizo");

    while (WiFi.status() != WL_CONNECTED)
    {
      delay(1000);
      Serial.print(".");
    }
  }

  /* サーバの立ち上げ */
  void setServer()
  {
    server.begin();
  }

  /* TCPストリーム */
  std::string tcpStream()
  {
    std::string packet = "";
    WiFiClient client = server.available();

    while (client && client.available() > 0)
    {
      packet += client.read();
    }

    return packet;
  }
};
