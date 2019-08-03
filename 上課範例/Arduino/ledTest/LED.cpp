#include "LED.h"
LED::LED(byte pinNum){
  _pin = pinNum;
  _startTime = millis();
  pinMode(_pin,OUTPUT);
}

void LED::on(){
  _state = true;
  digitalWrite(_pin,HIGH);
}
void LED::off(){
  _state = false;
  digitalWrite(_pin,LOW);
}

void LED::blink(long interval){
  unsigned long currentTime = millis();
  if(currentTime - _startTime >= interval){
    if(_state == true){
      off();
    }else{
      on();
    }

    _startTime = currentTime;
  }
}
