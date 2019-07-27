#include "Led.h"
Led::Led(){
  _state = false; 
  
}

Led::Led(byte pinNum){
  _pinNum = pinNum;
  _previousTime = millis();
  _state = false;
  pinMode(pinNum,OUTPUT);
}

void Led::setPinNum(byte pinNum){
  _pinNum = pinNum;
  pinMode(_pinNum,OUTPUT);
}

void Led::setState(boolean state){
    _state = state;
    digitalWrite(_pinNum,_state);
}

void Led::flashWithMillisecond(int millisecond){
  if((millis()-_previousTime) >= millisecond){
    setState(!_state);
    _previousTime = millis();
  }
  
} 
 
 
  
