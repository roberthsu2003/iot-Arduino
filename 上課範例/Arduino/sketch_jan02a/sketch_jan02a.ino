#include "TrafficLight.h"

TrafficLight *trafficLight;

void setup() {
 Serial.begin(115200);
 trafficLight = new TrafficLight(5,6,7);
}

void loop() {
  // put your main code here, to run repeatedly:
 trafficLight->turnOn(3,2,5);
}
