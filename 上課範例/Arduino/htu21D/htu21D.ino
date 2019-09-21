#include <Wire.h>
#include "SparkFunHTU21D.h"
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include "Timer.h"
#define window D3
#define sound A0


//Create an instance of the object
HTU21D myHumidity;
FirebaseData firebaseData;
Timer timer;
//sound
int averageSound = 0;
 

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

//sound
  timer.every(1000,doSomeThing);
}

void loop() {
  
  timer.update();
}

void doSomeThing(){
  timer.every(100,getSound);
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
  //window
  bool windowValue = digitalRead(window);
  if (Firebase.setBool(firebaseData,"/home/window",windowValue) == true){
    Serial.println("window success");
  }else{
    Serial.println("window false");
  }
  Serial.print("window:");
  Serial.println(windowValue);

  //sound
  int soundValue = averageSound;
  
  if (Firebase.setInt(firebaseData,"/home/sound",soundValue) == true){
    Serial.println("sound success");
  }else{
    Serial.println("sound false");
  }
  Serial.print("sound:");
  Serial.println(soundValue);
}

float round(float var) 
{ 
    
    float value = (int)(var * 100 + .5); 
    return (float)value / 100; 
} 


void getSound(){
  int soundValue = analogRead(sound);
 
    averageSound += soundValue;
    averageSound /= 2;
  
   
}
