#include "GreenRedBlue.h"

GreenRedBlue threeOfLed;

void setup() {
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
 Serial.print("Green:");
 Serial.println(threeOfLed.greenLed);
 Serial.print("Red:");
 Serial.println(threeOfLed.redLed);
 Serial.print("Blue:");
 Serial.println(threeOfLed.blueLed);
 delay(1000);
}
