#include <Wire.h>
#include "SparkFunHTU21D.h"
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#define window D3

//Create an instance of the object
HTU21D myHumidity;
FirebaseData firebaseData;


 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("HTU21D Example!");  
  myHumidity.begin();
  
  //wifi
  WiFi.begin("0gm4", "2773524311");
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  //firebase
  Firebase.begin("arduinofirebase-6d104.firebaseio.com", "z5lPWwjZLZuNNcUEelbJdiNaIvnR2Zfq49BuQBAa");
  Firebase.reconnectWiFi(true);
  Firebase.setMaxRetry(firebaseData, 3);
  Firebase.setMaxErrorQueue(firebaseData, 30);

  //window
  pinMode(window,INPUT_PULLUP);
}

void loop() {
  float humd = myHumidity.readHumidity();
  float temp = myHumidity.readTemperature();
  float humdValue = round(humd);
  float tempValue = round(temp);
  Serial.print("Time:");
  Serial.print(millis());
  Serial.print(" Temperature:");
  Serial.print(tempValue, 5);
  Serial.print("C");
  Serial.print(" Humidity:");
  Serial.print(humdValue, 5);
  Serial.print("%");

  Serial.println();
  if (Firebase.setDouble(firebaseData,"/home/humidity",humdValue) == true){
    Serial.println("humidity success");
  }else{
    Serial.println("humidity false");
  }

  if (Firebase.setDouble(firebaseData,"/home/temp",tempValue) == true){
    Serial.println("temperature success");
  }else{
    Serial.println("temperature false");
  }
  bool windowValue = digitalRead(window);
  if (Firebase.setBool(firebaseData,"/home/window",windowValue) == true){
    Serial.println("window success");
  }else{
    Serial.println("window false");
  }
  Serial.print("window:");
  Serial.println(windowValue);
  delay(1000);
}

float round(float var) 
{ 
    
    float value = (int)(var * 100 + .5); 
    return (float)value / 100; 
} 
