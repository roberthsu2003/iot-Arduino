#include <SPI.h>
#include <RFID.h>
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>

#define SS_PIN 15
#define RST_PIN 16
#define FIREBASE_HOST "arduinofirebase-6d104.firebaseio.com"
#define WIFI_SSID "robert_hsu"
#define WIFI_PASSWORD "1234567890"

RFID rfid(SS_PIN, RST_PIN);


int serNum0;
int serNum1;
int serNum2;
int serNum3;
int serNum4;

unsigned long lastTime = millis();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  SPI.begin();
  rfid.init();
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
  // put your main code here, to run repeatedly:
  if (millis() - lastTime > 1000) {
    lastTime = millis();
    if (rfid.isCard()) {
      if (rfid.readCardSerial()) {
        if (rfid.serNum[0] != serNum0 || rfid.serNum[1] != serNum1 || rfid.serNum[2] != serNum2 || rfid.serNum[3] != serNum3 || rfid.serNum[4] != serNum4) {
          Serial.println(" ");
          Serial.println("Card found");
          serNum0 = rfid.serNum[0];
          serNum1 = rfid.serNum[1];
          serNum2 = rfid.serNum[2];
          serNum3 = rfid.serNum[3];
          serNum4 = rfid.serNum[4];
          /*
          Serial.println("Cardnumber:");
          Serial.print(rfid.serNum[0], HEX);
          Serial.print(", ");

          Serial.print(rfid.serNum[1], HEX);
          Serial.print(", ");

          Serial.print(rfid.serNum[2], HEX);
          Serial.print(", ");

          Serial.print(rfid.serNum[3], HEX);
          Serial.print(", ");

          Serial.print(rfid.serNum[4], HEX);
        */
        StaticJsonBuffer<200> jsonBuffer; 
          JsonObject& dataObject = jsonBuffer.createObject();       
          
         // dataObject["card"] =((String)serNum0 + "-" + (String)serNum1).c_str();
         String id = "";
         for(int i=0;i<=4;i++){
          char charVal[2];
          sprintf(charVal,"%2x",rfid.serNum[i]);
          id += String(charVal);
          if(i != 4){
            id += "-";
          }
         }
          char data[id.length()+1];
          id.toCharArray(data,id.length()+1);
          
          
          dataObject["card"] =  data;
          
        String key = Firebase.push("rfid/records/",dataObject);
        JsonObject& timeStampObject = jsonBuffer.createObject();
        timeStampObject[".sv"] = "timestamp";
        Serial.println("rfid/records/" + key);
        Firebase.push("rfid/records/" + key,timeStampObject);
        //Serial.println(key);
        }
      }
    }

  }
}
