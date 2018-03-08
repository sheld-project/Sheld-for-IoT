/**
 * @file factory.cpp
 * @brief sheld/packetのPacketクラスにおけるインスタンスを量産
 * @author akakou
 * @date 2018/03/07
 */
#include <stdio.h>

#include <string>
#include <sstream>
#include <map>

#include "packet.cpp"


 /**
  * @brief sheld/packetのPacketクラスにおけるインスタンスを量産
  */
class Factory {
private:
    /**
    * @brief 引数が正しいかを判定
    * @param (sheld_url) SheldのURL
    * @param (headers) ヘッダ情報
    * @param (parameters) パラメータ
    */
    bool isCorrectArgument(
      //std::string sheld_url,
      std::map<std::string, std::string> headers,
      std::map<std::string, std::string> parameters
    ){
        if(0 >= headers.count("Method")){
            Log = "Method is not defined";
        }
        if(0 >= headers.count("URI")){
            Log = "URI is not defined";
        }
        if(0 >= headers.count("Version")){
          Log = "Version is not defined";
        }
        if(0 >= headers.count("Host")){
          Log = "Host is not defined";
        }

        return false;
    }
    /**
    * @brief Content-Lengthを計算
    * @param (headers) ヘッダ情報
    * @param (parameters) パラメータ
    */
    int calculateContentLength(
      // メソッド等
      std::map<std::string, std::string> headers,
      // パラメータ
      std::map<std::string, std::string> parameters
    ){
        /* Content Lengthを設定 */
        // Conent Lengthを計算
        int parameter_length = 0;

        std::map<std::string, std::string>::iterator it;
        for(it = parameters.begin(); it!=parameters.end(); it++) {
            parameter_length += it -> first.length() + it -> second.length()  + 2;
        }

        parameter_length --;

        return parameter_length;
    }

public:
    // エラーメッセージ
    std::string Log = "";

    /**
    * @brief コンストラクタ
    */
    Factory(){}

    /**
     * @brief Packetインスタンスの生成
     * @param (headers) ヘッダ情報
     */
    Packet* generatePacket(std::map<std::string, std::string> headers){
        std::map<std::string, std::string> parameters = {};
        return generatePacket(headers, parameters);
    }

    /**
     * @brief Packetインスタンスの生成
     * @param (headers) ヘッダ情報
     * @param (parameters) パラメータ
     */
    Packet* generatePacket(
      //std::string sheld_url,
      std::map<std::string, std::string> headers,
      std::map<std::string, std::string> parameters
    ){
        if (headers["Method"] == "POST"){
            // Content-Lengthを取得
            int content_length = calculateContentLength(headers, parameters);

            // intをstringに変換
            std::stringstream stream;
            stream << content_length;
            std::string length_string = stream.str();

            // 格納
            headers["Content-Length"] = length_string;
        }

        return new Packet(headers, parameters);
    }
 };
