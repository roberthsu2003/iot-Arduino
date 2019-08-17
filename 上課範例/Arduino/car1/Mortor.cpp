#include "Mortor.h"

 Mortor::Mortor(int modePin1, int modePin2, int speedPin){
  _modePin1 = modePin1;
  _modePin2 = modePin2;
  _speedPin = speedPin;
  pinMode(_modePin1,OUTPUT);
  pinMode(_modePin2,OUTPUT);
  pinMode(_speedPin,OUTPUT);
 }


void Mortor::setSpeed(int speed){
  _speed = speed;
  int nowSpeed = 255 * ((float)_speed/10);
  analogWrite(_speedPin, nowSpeed);
}

void Mortor::setMode(MortorMode mode){
  _mode = mode;
  switch(_mode){
    case STOP:
      digitalWrite(_modePin1,LOW);
      digitalWrite(_modePin2,LOW);
      break;
      
    case FOREWARD:
      digitalWrite(_modePin1,HIGH);
      digitalWrite(_modePin2,LOW);
      break;
      
    case BACKWARD:
      digitalWrite(_modePin1,LOW);
      digitalWrite(_modePin2,HIGH);
      break;
  }
}
