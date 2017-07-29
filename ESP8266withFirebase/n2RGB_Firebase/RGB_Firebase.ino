//
// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// FirebaseDemo_ESP8266 is a sample that demo the different functions
// of the FirebaseArduino API.

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "arduinofirebase-6d104.firebaseio.com"
#define WIFI_SSID "robert_hsu"
#define WIFI_PASSWORD "1234567890"

#define D5 14
#define D6 12
#define D7 13

void setup() {
  Serial.begin(115200);
  //led pin
  pinMode(D5,OUTPUT);
  pinMode(D6,OUTPUT);
  pinMode(D7,OUTPUT);
  
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST);
}



void loop() {
  // set value
  int rValue = Firebase.getBool("RGBSwitch/R");
   if(Firebase.failed()){
    Serial.println("取得R資料失敗");
    return;
  }
  
  int gValue = Firebase.getBool("RGBSwitch/G");
   if(Firebase.failed()){
    Serial.println("取得G資料失敗");
    return;
  }
  
  int bValue = Firebase.getBool("RGBSwitch/B");
   if(Firebase.failed()){
    Serial.println("取得B資料失敗");
    return;
  }

  if(rValue == true){
    red();
  }else if(gValue == true){
    green();
  }else if(bValue == true){
    blue();
  }
  
  
 
  
  delay(200);
}

void red(){
  digitalWrite(D5,LOW);
  digitalWrite(D6,HIGH);
  digitalWrite(D7,HIGH);
}

void blue(){
  digitalWrite(D5,HIGH);
  digitalWrite(D6,HIGH);
  digitalWrite(D7,LOW);
}

void green(){
  digitalWrite(D5,HIGH);
  digitalWrite(D6,LOW);
  digitalWrite(D7,HIGH);
}

