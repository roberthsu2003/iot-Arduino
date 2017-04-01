#include "Firebase.h"
Firebase firebase("arduinofirebase-6d104.firebaseio.com");

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  firebase.connectedToWifi("robert_hsu_home","0926656000");
  //firebase.getJSONData("/led.json");
  JsonObject* parseJson= firebase.getJSONData("/lcd.json");
  JsonObject& json = *parseJson;
  
  Serial.print("line2:");
  Serial.println((const char*)json["line2"]);
  delay(1000);
}
