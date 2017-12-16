#include "Potentiometer.h"

Potentiometer::Potentiometer(int pinNumber){
  _pin = pinNumber;
}

int Potentiometer::pin(){
  return _pin;
}


int Potentiometer::getValue(State state){
  int rawValue = analogRead(_pin);
  switch (state){
    case RAW:
      return rawValue;
      break;
    case TEN:
      return map(rawValue,0,1023,0,10);
      break;
    case HUNDRED:
      return map(rawValue,0,1023,0,100);
      break;
    case TWOFIVEFIVE:
      return map(rawValue,0,1023,0,255);
      break;
    default:
      
      return 9999;
   
  }
  
   
}

