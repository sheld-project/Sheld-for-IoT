/* wifi.cpp
Wi-Fiの制御＆インターフェース.
*/

#include <string>
#include <map>
// #include <ESP8266WiFi.h>


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
};
