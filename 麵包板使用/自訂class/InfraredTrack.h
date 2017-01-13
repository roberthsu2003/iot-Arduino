#ifndef _INFRAREDTRACK_H
#define _INFRAREDTRACK_H

#include "arduino.h"
class InfraredTrack{
  protected:
  int _rawValue=0;
  int _pin;
  
  public:
  InfraredTrack(int pinNum);
  int rawValue();
};
#endif

