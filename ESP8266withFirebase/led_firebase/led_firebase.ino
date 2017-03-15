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
#include <ArduinoJson.h>

#define D4 4
const char* ssid = "robert_hsu_home";
const char* password = "0926656000";
String section;



const char* host = "arduinofirebase-6d104.firebaseio.com";
const int httpsPort = 443;

// Use web browser to view and copy
// SHA1 fingerprint of the certificate
const char* fingerprint = "CF 05 98 89 CA FF 8E D8 5E 5C E0 C2 E4 F7 E6 C3 C7 50 DD 5C";

void setup() {
  pinMode(D4,OUTPUT);
  
  Serial.begin(115200);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); 
}

void loop() {
  while (WiFi.status() == WL_CONNECTED){
     // Use WiFiClientSecure class to create TLS connection
      WiFiClientSecure client;
      Serial.print("connecting to ");
      Serial.println(host);
      if (!client.connect(host, httpsPort)) {
        Serial.println("connection failed");
        return;
      }
     
    
    
    
      String url = "/led.json";      
      Serial.print("requesting URL: ");
      Serial.println(url);
    
      client.print("GET " + url + " HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n" +                    
                   "Connection: close\r\n\r\n");
                   
    
      Serial.println("request sent");
      unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  // Read all the lines of the reply from server and print them to Serial
  Serial.println("--------------data--------------------");
  section="header";
  while(client.available()){
    String line = client.readStringUntil('\r');
    parseJSON(line);
    //Serial.print(line);
  }
  
  
  Serial.println();
  Serial.println("----------------------------------------");
  Serial.println("closing connection");
  }
  delay(3000);
  
}

void parseJSON(String line){
  
      if(section=="header"){
        Serial.println(".");
        if (line=="\n"){
          section = "json";
        }
        return;
      }
      
      String result = line.substring(1);      // Parse JSON  
      Serial.println(result);    
      int size = result.length() + 1;
      Serial.println(size);
      char json[size];
      result.toCharArray(json, size);
      StaticJsonBuffer<200> jsonBuffer;
      JsonObject& json_parsed = jsonBuffer.parseObject(json);
      if (!json_parsed.success())
      {
        Serial.println();
        Serial.println("parseObject() failed");
        return;
      }
      // Make the decision to turn off or on the LED
      if (strcmp(json_parsed["D2"], "true") == 0) {
         digitalWrite(D4,HIGH);
         Serial.println("LED ON");
      }
      else {
        digitalWrite(D4,LOW);
        Serial.println("led off");
      }
    
}

