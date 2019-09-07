#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define IN1 D4

FirebaseData firebaseData;
void setup() {
  Serial.begin(115200);
  Serial.println();
  WiFi.begin("RobertIphone", "0926656000");
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());


  Firebase.begin("arduinofirebase-6d104.firebaseio.com", "z5lPWwjZLZuNNcUEelbJdiNaIvnR2Zfq49BuQBAa");
  Firebase.reconnectWiFi(true);
  Firebase.setMaxErrorQueue(firebaseData, 30);
  Firebase.setMaxRetry(firebaseData, 3);
  pinMode(IN1,OUTPUT);
}

void loop() {
  if (Firebase.getBool(firebaseData,"/lcd/relay1")){
    if(firebaseData.boolData()){
      digitalWrite(IN1,HIGH);
    }else{
      digitalWrite(IN1,LOW);
    }
  }
  delay(300);
}
