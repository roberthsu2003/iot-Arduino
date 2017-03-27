/*
 *  HTTP over TLS (HTTPS) example sketch
 *
 *  This example demonstrates how to use
 *  WiFiClientSecure class to access HTTPS API.
 *  We fetch and display the status of
 *  esp8266/Arduino project continuous integration
 *  build.
 *
 *  Created by Ivan Grokhotkov, 2015.
 *  This example is in public domain.
 */

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "Timer.h"
#include <HTU21D.h>
#define D3 0
#define SoundSensor A0

boolean windowValue = false;
float humidityValue = 0.0;
float temperatureValue = 0.0;
float soundValue = 0.0;


const char* ssid = "robert_hsu";
const char* password = "1234567890";


const char* host = "arduinofirebase-6d104.firebaseio.com";
const int httpsPort = 443;

// Use web browser to view and copy
// SHA1 fingerprint of the certificate
const char* fingerprint = "CF 05 98 89 CA FF 8E D8 5E 5C E0 C2 E4 F7 E6 C3 C7 50 DD 5C";
Timer timer;
HTU21D myHumidity;
void setup() {
  
  wifiConnection();

  //window
  pinMode(D3,INPUT_PULLUP);
  if (WiFi.status() == WL_CONNECTED){
    timer.every(2000,connectionFirebase);
    }else{
     wifiConnection();
   }

   //humidity
   myHumidity.begin();
  
  
}

void loop() {
    timer.update();
    windowValue = configureWindow(D3);
    humidityValue = getHumidity();
    temperatureValue = getTemperatureValue();
    soundValue = analogRead(SoundSensor);
    delay(100);
    Serial.print("soundValue:");
    Serial.println(soundValue);
   
}

void wifiConnection(){
  Serial.begin(115200);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void connectionFirebase(){
  // Use WiFiClientSecure class to create TLS connection
  WiFiClientSecure client;
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }
 



  String url = "/home.json";
  String jsonString = "{\"window\":" + String(windowValue?"true":"false") + ",\"sound\":" + soundValue + ",\"temp\":" + temperatureValue + ",\"humidity\":" + humidityValue + "}";

  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print("PUT " + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Content-Type: application/json\r\n" + 
               "User-Agent: BuildFailureDetectorESP8266\r\n" + 
               "Content-Length:" + jsonString.length() +"\r\n\r\n" +               
               jsonString);

  Serial.println("request sent");
  while (client.connected()) {
    
    String line = client.readStringUntil('\n');
    Serial.println(line);
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
    Serial.println("esp8266/Arduino CI successfull!");
  } else {
    Serial.println("esp8266/Arduino CI has failed");
  }
  Serial.println("reply was:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  Serial.println("closing connection");
}

boolean configureWindow(int pin){
  return digitalRead(pin);
}

float getHumidity(){
  float humd = myHumidity.readHumidity();
  return humd;
}

float getTemperatureValue(){
  float temp = myHumidity.readTemperature();
  return temp;
}

