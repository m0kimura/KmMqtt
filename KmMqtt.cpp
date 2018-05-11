//*******1*********2*********3*********4*********5*********6*********7*********8
#include "KmMqtt.h"

WiFiClient Client;
PubSubClient MqClient(Client);

/**
 * オブジェクトコンストラクション
 * @param  {String} ssid  WiFi ID
 * @param  {String} psw   WiFi PSW
 * @param  {string} topic MQTT TOPIC ID
 * @return {Void}         none
 * @constructor
 */
KmMqtt::KmMqtt(String ssid, String psw, String server, String topic){

  ssid.toCharArray(Ssid, 16);
  psw.toCharArray(Sspsw, 16);
  server.toCharArray(Server, 16);
  topic.toCharArray(Topic, 16);
  Count=0;

}

/**
 * WiFi Connection
 * @return {Void} none
 * @method
 */
void KmMqtt::begin(std::function<void(char*, uint8_t*, unsigned int)> callback){

    delay(10);
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(Ssid);

    WiFi.begin(Ssid, Sspsw);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    randomSeed(micros());

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    MqClient.setServer(Server, 1883);
    MqClient.setCallback(callback);

}

/**
 * 接続処理
 * 2return {void} none
 * @method
 */
void KmMqtt::reconnect() {
  // Loop until we're reconnected
  while (!MqClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    String id=String(WiFi.localIP());
    if (MqClient.connect(id.c_str())) {
      Serial.println("connected");
      MqClient.subscribe(Topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(MqClient.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

/**
 * ループ時処理
 * @return {Void} none
 * @method
 */
void KmMqtt::loop(){
  if (!MqClient.connected()) {KmMqtt::reconnect();}
  MqClient.loop();
}

/**
 * 送信処理
 * @param  {string} topic トピックID
 * @param  {String} data  送信データ
 * @return {bool}         送信結果
 * @method
 */
bool KmMqtt::publish(String data){
  bool rc;
  char d[255];
  data.toCharArray(d, 255);
  rc=MqClient.publish("Server", d);
  return rc;
}

int KmMqtt::unstring(byte* payload, unsigned int length) {
  Command=""; Op1=""; Op2=""; Op3="";
  int n=0;
  for (int i = 0; i < length; i++) {
    String x;
    x=String((char)payload[i]);
    if(x=="/"){n++;}
    else{
      if(n==1){Command.concat(x);}
      else if(n==2){Op1.concat(x);}
      else if(n==3){Op2.concat(x);}
      else if(n==4){Op3.concat(x);}
    }
  }
  return n;
}
