#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define dataPin D6
#define latchPin D7
#define clockPin D8

FirebaseData firebaseData;
byte index1 = 0;
const byte LEDs[10] = {
  B01111110, //0
  B00110000, //1
  B01101101, //2
  B01111001, //3
  B00110011, //4
  B01011011, //5
  B01011111, //6
  B01110000,//7
  B01111111,//8
  B01110011  //9
};

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  //連線WIFI
  Serial.begin(115200);
  Serial.println();
  WiFi.begin("robert_hsu", "1234567890");
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  //連線firebase
  Firebase.begin("arduinofirebase-6d104.firebaseio.com",
                 "z5lPWwjZLZuNNcUEelbJdiNaIvnR2Zfq49BuQBAa");

  Firebase.reconnectWiFi(true);
  Firebase.setMaxRetry(firebaseData, 3);
  Firebase.setMaxErrorQueue(firebaseData, 30);
}

void loop() {
  // put your main code here, to run repeatedly:
   if (Firebase.getInt(firebaseData, "/iot0624/digit")) {
    if (firebaseData.dataType() == "int") {
      int digitalNum = firebaseData.intData();
      Serial.println(digitalNum);
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin,LSBFIRST,LEDs[digitalNum]);
    digitalWrite(latchPin, HIGH);
    }

  } else {
    Serial.println(firebaseData.errorReason());
  }

  
  delay(500);
  
}
