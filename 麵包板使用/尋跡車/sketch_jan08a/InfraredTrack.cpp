#include "InfraredTrack.h"
 InfraredTrack::InfraredTrack(int pinNum){
  _pin = pinNum;
 }

 
 int InfraredTrack::rawValue(){
    _rawValue = analogRead(_pin);
    return _rawValue;
 }

