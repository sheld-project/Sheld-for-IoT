/* wifi.cpp
Wi-Fiの制御＆インターフェース.
*/

#include <string>
#include <map>
#include <iostream>

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
      {"HOST",""}
  };
  WiFiServer server = WiFiServer(80);
  WiFiClient client;
  int status = WL_IDLE_STATUS;

public:
  /* プロパティの初期化 */
  WiFi_(
    std::string arg_ssid,
    std::string arg_password,
    std::string arg_host
  )
  {
    CONNECTION_PROPERTY["SSID"] = arg_ssid;
    CONNECTION_PROPERTY["PASS"] = arg_password;
    CONNECTION_PROPERTY["HOST"] = arg_host;
  }

  /* Wi-Fiに接続する */
  bool ConnectWifi()
  {
    // 接続
    status = WiFi.begin(
      CONNECTION_PROPERTY["SSID"].c_str(),
      CONNECTION_PROPERTY["PASS"].c_str()
    );

    // 接続できたらTrue,失敗したらFalseを返す
    if ( status == WL_CONNECTED)
    {
      server.begin();
      return true;
    }
    else
    {
      return false;
    }
  }

  /* クライアントを待つ */
  void WaitClient()
  {
        client = server.available();
  }

  /* TCPストリームを行うクラス */
  std::string TcpStream(){
    // result
    std::string response = "";

    // クライアントが来たら、受け取ったバイト列の長さが100になるまで受け取る
    while(response.length() < 100)
    {
      response += client.read();
    }

    return response;
  }
};
