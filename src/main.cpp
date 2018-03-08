#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>

#include <string>
#include <map>

#include "sheld/factory.cpp"
#include "sheld/correspondent.cpp"

#define SSID "hoge"
#define PASSWORD "hugahuga"
#define ADDRESS "192.168.43.209"
#define PORT 80

const std::map<std::string, std::string> HEADERS = {
    {"Method", "GET"},
    {"URL", "http://akakou.hatenablog.com/"},
    {"Version", "1.1"},
    {"Connection", "close"},
    {"Host", "akakou.hatenablog.com"},
    {"Connection", "close"},
    {"Cookie", "Cookie is yummy !"}
};
const std::map<std::string, std::string> PARAMETERS = {
    {"a", "b"},
    {"b", "c"}
};

Factory *factory;

void setup() {
    // シリアルの開始
    Serial.begin(115200);
    Serial.println("Start serial!");

    delay(5000);

    // WiFiへの接続
    Serial.print("Connecting to ");
    Serial.println(SSID);

    WiFi.begin(SSID, PASSWORD);

    // 接続待ち
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    // ステータスの表示
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    // プロキシとの接続
    Correspondent *correspondent = new Correspondent(ADDRESS, PORT);
    Serial.println("Connect to proxy");
    bool is_connected = correspondent -> connectToProxy();
    if(!is_connected){
        Serial.println("Connection failed");
        return;
    }

    // リクエストの送信
    Packet *packet = factory -> generatePacket(HEADERS);
    Serial.println("*-*-*-*-* REQUEST *-*-*-*-*");
    std::string request = packet -> generateRequest();
    Serial.println(request.c_str());
    Serial.println("*-*-*-*-*   E N D   *-*-*-*-*\n");

    Serial.println("Send request");
    correspondent -> sendRequest(packet);

    // 有効になるまで待つ
    Serial.println("Wait available");
    is_connected = correspondent -> waitAvailable();
    if(!is_connected){
        Serial.println("Time out !");
        return;
    }

    // レスポンスの受取
    Serial.println("Get response ");
    //std::string response =
    Serial.println("*-*-*-*-* RESPONSE *-*-*-*-*");

    while(correspondent -> isAvailable()) {
        char response = correspondent -> readResponse();
        Serial.print(response);
    }
    
    Serial.println("*-*-*-*-*   E N D   *-*-*-*-*\n");
}


void loop() {

}
