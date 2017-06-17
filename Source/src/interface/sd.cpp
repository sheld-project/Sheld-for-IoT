/* microsd.cpp
 MicroSDの制御
*/
#include <string>
#include <SD.h>


/* --- SDの制御クラス --- */
class SD_
{
private:
  File file;
  std::string FileBody;
  std::string PATH;
  int CS;

public:
  /* ファイルパス等の設定 */
  SD_(std::string path,int cs)
  {
    PATH = path;
    CS = cs;
  }

  /* SD カードとの接続*/
  bool connect()
  {
    bool is_sd_begin = SD.begin(CS);
    file = SD.open(PATH.c_str(), FILE_READ);

    return is_sd_begin && file;
  }

  /* ファイルを文字列として読み込む */
  std::string readfFile()
  {
    while (file.available())
    {
      char char_byte = (char)file.read();
      FileBody = FileBody + char_byte;
    }
    return FileBody;
  }

  /* SDカードの遮断 */
  ~SD_()
  {
    file.close();
  }
};
