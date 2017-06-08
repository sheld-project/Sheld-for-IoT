/* microsd.cpp
 MicroSDの制御
*/
#include <string>
#include <SD.h>


class SD_
{
private:
  File path;

public:
  SD_(std::string arg_ssid_str)
  {
    // パスの設定
    path = SD.open(arg_ssid_str.c_str());
  }
};
