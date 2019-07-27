#include "TrafficLight.h"

TrafficLight::TrafficLight(byte redPin,byte yellowPin,byte greenPin){
  _redLed.setPinNum(redPin);
  _yellowLed.setPinNum(yellowPin);
  _greenLed.setPinNum(greenPin);
  Serial.println("trafficLight constructor");
}

void TrafficLight::turnOn(byte redSecond,byte yellowSecond,byte greenSecond){
  oneLedOnInterval(_greenLed,greenSecond);
  oneLedOnInterval(_yellowLed,yellowSecond);
  oneLedOnInterval(_redLed,greenSecond);
}

void TrafficLight::oneLedOnInterval(Led led,byte secondInterval){
  led.setState(true);
  delay(secondInterval*1000);
  led.setState(false);
}
