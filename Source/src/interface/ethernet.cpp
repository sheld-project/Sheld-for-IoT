/* ethernet.cpp
Ethernet制御＆インターフェース
*/

#include <Ethernet.h>
#include <string>


/* --- Ethernet制御クラス --- */
class Ethernet_
{
private:
  // イーサネット
  EthernetClient client;

  // マイコンのIPアドレス
  std::string Micro_Computer_IP;
  // MACアドレス
  byte MAC_ADDRESS[6];
  // WifiモジュールのIPアドレス
  IPAddress My_IP;
  // ポート
  int PORT;

public:
  /* プロパティの初期化 */
  Ethernet_(
    byte &mac_address,
    std::string microcomputer_ip,
    int port
  )
  {
    *MAC_ADDRESS = mac_address;
    Micro_Computer_IP = microcomputer_ip;
    PORT = port;
  }

  /* Ethernetでの接続先と接続 */
  void connectEthernet()
  {
    if (Ethernet.begin(MAC_ADDRESS) == 0) {
      Ethernet.begin(MAC_ADDRESS, My_IP);
    }
  }

  /* Ethernetの送信 */
  void sendEthernet(std::string message)
  {
    // 接続
    if (client.connect(Micro_Computer_IP.c_str(), PORT))
    {
      // 送信
      client.println(message.c_str());
    }
  }
};
