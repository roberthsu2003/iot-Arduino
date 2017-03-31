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
Timer timer;

void setup() {
  Serial.begin(9600);
  
  // lcd setup;
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(5,0);
  lcd.print("Hello");
  lcd.setCursor(5,1);
  lcd.print("World");

  //relay
  pinMode(D0,OUTPUT);

  //Firebase wifi connection
  Serial.println("begin Wifi connection");
  firebase.connectedToWifi(ssid,password);
  timer.every(2000,runFirebase);
}

void loop() {
  // put your main code here, to run repeatedly:
  timer.update();
  
  
}

void runFirebase(){
  firebase.connectedToFirebase();  
  JsonObject* parseJson = firebase.getJSONData("/lcd.json");
  JsonObject& json = *parseJson;
  Serial.print("line1:");
  const char* line1 = json["line1"];
  Serial.println(line1);
  
}

