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

#define D2 4

void setup() {
  Serial.begin(115200);
  //led pin
  pinMode(D2,OUTPUT);
  
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
  bool D2bool = Firebase.getBool("led/D2");
  if(Firebase.failed()){
    Serial.println("取得資料失敗");
    return;
  }
  int D2Value = D2bool?HIGH:LOW;
  Serial.println(D2Value);
  digitalWrite(D2,D2Value);
  delay(200);
}
