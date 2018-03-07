/**
 * @file packet.cpp
 * @brief Sheldwallを通した通信で送信されるオブジェクト
 * @author akakou
 * @date 2018/03/07
 */

#include <string>
#include <map>


/**
 * @brief Sheldwallを通した通信で送信されるオブジェクト
 */
class Packet {
public:
    // SheldのURL
    std::string SheldURL;
    // メソッド等
    std::map<std::string, std::string> Headers;
    // パラメータ
    std::map<std::string, std::string> Parameters;

    /**
     * @brief コンストラクタ
     * @param (sheld_url) SheldのURL
     * @param (headers) ヘッダ情報
     * @param (parameters) パラメータ
     */
    Packet(
        std::string sheld_url,
        std::map<std::string, std::string> headers,
        std::map<std::string, std::string> parameters
      ){
        // 引数を各フィールドに格納
        SheldURL = sheld_url;
        Headers = headers;
        Parameters = parameters;
    }

    /**
     * @brief HTTPリクエストの生成
     * @return 生成されたHTTPリクエスト
     */
     std::string generateRequest(){
        /* リクエストヘッダの生成 */
        // 1行目を生成
        std::string request = Headers["Method"] + " "
            + Headers["URL"] + " "
            + "HTTP/" + Headers["Version"];

        if (0 < Headers.count("Host")){
            // HostがあればHostも足す
            request +=  "\nHost: " + Headers["Host"];
        }

        if (0 < Headers.count("Connection")){
            // ConnectionがあればConnectionも足す
            request  += "\nConnection: " + Headers["Connection"];
        }

        if (Headers["Method"] == "POST"){
            // ConnectionがあればConnectionも足す
            request  += "\nContent-Length: " + Headers["Content-Length"];
        }


        std::map<std::string, std::string>::iterator it;
        for(it = Headers.begin(); it!=Headers.end(); it++) {
            // メソッドとホストではない、
            // 各ヘッダをリクエストに足していく
            if(
              it -> first != "Method"
              && it -> first != "URL"
              && it -> first != "Version"
              && it -> first != "Host"
              && it -> first != "Connection"
              && it -> first != "Content-Length"
            ){
                request += "\n" + it -> first + ": " + it -> second;
            }
        }

        /* リクエストボディの作成 */
        if (Headers["Method"] == "POST"){

            request += "\n\n";

            for(it = Parameters.begin(); it!=Parameters.end(); it++) {
                // メソッドとホストではない、
                // 各ヘッダをリクエストに足していく
                request += it -> first + "=" + it -> second + "&";
            }
            // 最後の文字を消す
            request.pop_back();
        }

        return request;
     }
};
