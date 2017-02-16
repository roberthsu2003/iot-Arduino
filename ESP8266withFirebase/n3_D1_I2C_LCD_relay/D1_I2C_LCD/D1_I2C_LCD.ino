#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include "Timer.h"

// Construct an LCD object and pass it the
// I2C address, width (in characters) and
// height (in characters). Depending on the
// Actual device, the IC2 address may change.
//0 is SCA,2 is SDL
//
LiquidCrystal_I2C lcd(0x27, 0, 2);
#define D8 0
const char* ssid = "robert_hsu_home";
const char* password = "0926656000";
const char* host = "arduinofirebase-6d104.firebaseio.com";
const int httpsPort = 443;
String section;
Timer timer;

void setup() {
  wifiConnection();
  //lcd Setup
  lcd.begin(16, 2);
  lcd.init();

  // Turn on the backlight.
  lcd.backlight();

  // Move the cursor characters to the right and
  // zero characters down (line 1).
  lcd.setCursor(5, 0);

  // Print HELLO to the screen, starting at 5,0.
  lcd.print("HELLO");

  // Move the cursor to the next line and print
  // WORLD.
  lcd.setCursor(5, 1);
  lcd.print("WORLD");

  //relay
  pinMode(D8, OUTPUT);

  //esp8662
  
  timer.every(2000,connectionFirebase);
  


}

void loop() {
  timer.update();
  

}

void wifiConnection() {
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
  if(WiFi.status() == WL_CONNECTED){
      WiFiClientSecure client;
      Serial.print("connecting to ");
      Serial.println(host);
      if (!client.connect(host, httpsPort)) {
        Serial.println("connection failed");
        return;
      }
       String url = "/lcd.json";
      Serial.print("requesting URL: ");
      Serial.println(url);
      client.print("GET " + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +                
               "Connection:close\r\n\r\n");

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
  Serial.println("closing connection");;
  }

 
  
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
      if (strcmp(json_parsed["relay1"], "true") == 0) {
         digitalWrite(D8,HIGH);
         Serial.println("relay1 ON");
      }
      else {
        digitalWrite(D8,LOW);
        Serial.println("relay1 off");
      }
      lcd.clear();
      lcd.setCursor(0, 0);
      const char* line1 = json_parsed["line1"];
      lcd.print(line1);
      lcd.setCursor(0, 1);
      const char* line2 = json_parsed["line2"];
      lcd.print(line2);
    
}


