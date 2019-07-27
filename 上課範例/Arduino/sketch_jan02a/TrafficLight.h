#ifndef _TRAFFICLIGHT_H_
#define _TRAFFICLIGHT_H_

#include "Led.h";
#include <arduino.h>


class TrafficLight{
  private:
  Led _redLed;
  Led _yellowLed;
  Led _greenLed;

  void oneLedOnInterval(Led,byte);

  public:
  TrafficLight(byte,byte,byte);
  void turnOn(byte,byte,byte);
};

#endif
