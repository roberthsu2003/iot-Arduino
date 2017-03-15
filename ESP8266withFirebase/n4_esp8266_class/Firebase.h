#ifndef __FIREBASE__
#define __FIREBASE__
#include "arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

class Firebase{
  public:
  const char* ssid;
  const char*  password;
  const char* firebaseHost;
  const int httpsPort = 443;
  WiFiClientSecure client;

  Firebase(const char* host);
  void connectedToWifi(const char* ssid,const char* password);
  void connectedToFirebase();
  JsonObject* getJSONData(String url);  
};
#endif
