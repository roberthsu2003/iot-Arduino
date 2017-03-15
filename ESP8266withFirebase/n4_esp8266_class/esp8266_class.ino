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
  JsonObject* parseJson= firebase.getJSONData("/led.json");
  JsonObject& json = *parseJson;
  const char* d2State = json["D2"];
  Serial.print("d2:");
  Serial.println(d2State);
  delay(1000);
}
