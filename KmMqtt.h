//*******1*********2*********3*********4*********5*********6*********7*********8
/* KmMqtt.h */

#ifndef KMMQTT_H
#define KMMQTT_H

#include <Arduino.h>
#include "ESP8266WiFi.h"
#include "PubSubClient.h"

class KmMqtt{
  public:
    KmMqtt(String ssid, String psw, String server, String topic);
    void begin(std::function<void(char*, uint8_t*, unsigned int)> callback);
    void reconnect();
    void loop();
    bool publish(String data);
    int unstring(byte* payload, unsigned int length);
    int Count;
    String Command;
    String Op1;
    String Op2;
    String Op3;
  private:
    char Server[16];
    char Ssid[16];
    char Sspsw[16];
    char Topic[16];
};

#endif
