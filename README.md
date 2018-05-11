MQTTクラス for ESP8266
====

ESP8266でMqttでのコミュニケーションをするためのツール。
publish, subscribeとしてのクライアント処理ができます。

## Description
1. ブローカーが別途必要です。
2. 基本１トピック受信のみで、オブジェクト作成時に指定します。
3. 送信トピックは「Server」に固定されています。  

## Requirement
  - Arduino.h
  - ESP8266WiFi.h
  - PubSubClient.h

## Usage
### オブジェクト作成
KmMqtt Mq(「wifiのssid」, 「wifiのパスワード」, 「ブローカーのアドレス」, 「受信トピック」);

### 初期処理
begin　(「トピック受信ルーチン」); 別途、ルーチンを作成します。

### 送信処理
publish　(「送信メッセージ」);

### 受信時のメッセージ分解
unstring　(「payload」, 「length」); 受信時ルーチンの引数をそのまま受け継ぐ


### Sample

~~~c++
＜オブジェクトコンストラクション＞
KmMqtt Mq(「wifiのssid」, 「wifiのパスワード」, 「ブローカーのアドレス」, 「受信トピック」);

＜トピック受信処理＞
void get(char* topic, byte* payload, unsigned int length) {
  Mq.unstring(payload, length);
  // 受信されたメッセージは分解されて、Command, Op1, Op2, Op3のプロパティに編集される
  Serial.println(Mq.Command);
}

void setup() {
  Serial.begin(115200);
  Flag=true;
  Mq.begin(「トピック受信ルーチン（ここではget）」);
}

void loop() {

  Mq.loop();

  if (Flag) {
    ++Value;
    char msg[100];
    snprintf (msg, 75, "hello world #%ld", Value);
    Mq.publish(「送信メッセージ」);
    Flag=false;
  }
}
~~~

## Install
  git clone https://github.com/m0kimura/kmMqtt.git

## Licence

[MIT](https://github.com/tcnksm/tool/blob/master/LICENCE)

## Author

[m0kimura](https://github.com/m0kimura)

