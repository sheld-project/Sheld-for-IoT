/**
 * @file correspondents.cpp
 * @brief sheld/packetのPacketクラスを元にHTTPSで通信する
 * @author akakou
 * @date 2018/03/08
 */
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <string>

#include "packet.cpp"


 /**
  * @brief sheld/packetのPacketクラスを元にHTTPSで通信する
  */
class Correspondent {
public:
    WiFiClient Client;

    std::string Address;  // Proxyのアドレス
    int Port;             // Proxyのポート

    std::string Log = ""; // ログ
    int Timeout = 5000;   // タイムアウト

    /**
    * @brief コンストラクタ。WiFiを起動させる。
    * @param (address) WiFiのSSID
    * @param (port) WiFiのパスワード
    */
    Correspondent(std::string address, int port){
        Address = address;
        Port = port;
    };

    /**
     * @breif 事前のTCPリクエストを送信
     * @return 成功すればtrue、その他はfalse
     */
    bool connectToProxy(){
      // コネクション
        if (!Client.connect(Address.c_str(), Port)) {
            return false;
        }else{
            return true;
      }
    }

    /**
     * @breif 引数に与えられたパケットを送信
     * @param (packet) 送信するパケットのポインタ
     * @return 成功すればtrue、その他はfalse
     */
    void sendRequest(Packet *packet){
        // リクエストの送信
        Client.println(packet -> generateRequest().c_str());
    }

    /**
     * @breif Client.available()を返却
     * @return Client.available()を返却
     */
    int isAvailable(){
        return Client.available();
    }

    /**
     * @breif Availableが1になるまで待つ
     * @return 成功すればtrue、その他はfalse
     */
    bool waitAvailable(){
        // isAvailableが0以外になるまで待つ
        unsigned long timeout = millis();

        while (isAvailable() == 0) {
            if (millis() - timeout > Timeout) {
                Client.stop();
                return false;
            }
        }

        return true;
    }

    /**
     * @breif レスポンスの文字を受け取る
     * @return 受け取った文字
     */
    char readResponse(){
        return Client.read();
    }
};
