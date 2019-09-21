#include <Wire.h>
#include "SparkFunHTU21D.h"
#include <ESP8266WiFi.h>

//Create an instance of the object
HTU21D myHumidity;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("HTU21D Example!");  
  myHumidity.begin();

  WiFi.begin("network-name", "pass-to-network");
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  float humd = myHumidity.readHumidity();
  float temp = myHumidity.readTemperature();

  Serial.print("Time:");
  Serial.print(millis());
  Serial.print(" Temperature:");
  Serial.print(temp, 1);
  Serial.print("C");
  Serial.print(" Humidity:");
  Serial.print(humd, 1);
  Serial.print("%");

  Serial.println();
  delay(1000);
}
