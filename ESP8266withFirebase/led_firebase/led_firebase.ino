#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define D2 4
#define FIREBASE_HOST "網站"
#define WIFI_SSID "熱點名"
#define WIFI_PASSWORD "熱點密碼"

void setup() {
  Serial.begin(115200);
  //連線到Wifi
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.print("開始連線");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("連線成功:");
  Serial.print(WiFi.localIP());
  pinMode(D2,OUTPUT);
  Firebase.begin(FIREBASE_HOST);
}

void loop() {
  bool d2Value = Firebase.getBool("led/D2");
  if (Firebase.success() == false){
    Serial.print("取得led/D2失敗，重新執行");
    return;
  }
  digitalWrite(D2,d2Value);
  delay(200); 

}
