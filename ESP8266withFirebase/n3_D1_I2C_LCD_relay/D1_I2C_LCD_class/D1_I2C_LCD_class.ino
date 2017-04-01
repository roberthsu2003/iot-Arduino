//SCL is D1,SDA is D2
//Use Esp8266 D1 mini board

#include <LiquidCrystal_I2C.h>
#include "Firebase.h"
#include "Timer.h"


#define D1 5
#define D2 4
#define D0 16
LiquidCrystal_I2C lcd(0x27, D1, D2);
const char* ssid = "Robert iphone";
const char* password = "0926656000";
const char* host = "arduinofirebase-6d104.firebaseio.com";
const int httpsPort = 443;
Firebase firebase(host);
unsigned long lastTime = millis();//勿使用timer會出問題

void setup() {
  Serial.begin(115200);
  
  // lcd setup;
  lcdInit();

  //relay
  pinMode(D0,OUTPUT);

  //Firebase wifi connection
  
  firebase.connectedToWifi(ssid,password);
 
}

void loop() {
  // put your main code here, to run repeatedly:
 unsigned long current = millis();
 if((current - lastTime) >= 1000){   
  JsonObject* parseJson = firebase.getJSONData("/lcd.json");
  JsonObject& json = *parseJson; 
  const char* line1 = json["line1"];
  const char* line2 = json["line2"];
  String relay1 = String((const char*)json["relay1"]);
  String relay2 = String((const char*)json["relay2"]);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(line1);
  lcd.setCursor(0,1);
  lcd.print(line2);
  if(relay1 == "true"){
    digitalWrite(D0,HIGH);
  }else{
    digitalWrite(D0,LOW);
  }
  //更新時間  
  lastTime = current;
 }
 
}

void lcdInit(){
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(5,0);
  lcd.print("Hello");
  lcd.setCursor(5,1);
  lcd.print("World");
}



