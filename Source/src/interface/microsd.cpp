/* microsd.cpp
 MicroSDの制御
*/
#include <string>
#include <SD.h>


class SD_
{
private:
  File file;
  std::string file_body;

public:
  /* ファイルパス等の設定 */
  SD_(std::string path)
  {
    file = SD.open(path.c_str());
  }

  /* SD カードとの接続待ち*/
  bool connectSD()
  {
    if (file) {
      return true;
    } else {
    // if the file didn't open, print an error:
    return false;
    }
  }

  /* ファイルを文字列として読み込む */
  std::string readfFile()
  {
    while (file.available())
    {
      file.read();
    }
    return file_body;
  }

  /* SDカードの遮断 */
  void close()
  {
    file.close();
  }
};
