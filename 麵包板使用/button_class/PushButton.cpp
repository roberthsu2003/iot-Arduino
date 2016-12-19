#include "PushButton.h"

PushButton::PushButton(int pinNumber){
  _buttonPin = pinNumber;
  pinMode(_buttonPin,INPUT);
  _previousState = LOW;
  _currentState = LOW;
}

PushButton::PushButton(int pinNumber,int mode){
  _buttonPin = pinNumber;
  _mode = mode;
  pinMode(_buttonPin,_mode);
  switch (mode){
    case INPUT:
      _previousState = LOW;
      _currentState = LOW;
      break;
    case INPUT_PULLUP:
     _previousState = HIGH;
     _currentState = HIGH;
     break;
    default:break;
  }
}

int PushButton::getPushCounts(){
  _currentState = digitalRead(_buttonPin);
  _currentsTimes = millis();
  if(_currentState != _previousState && (_currentsTimes-_previousTimes)>50){
    _previousState = _currentState;
    _previousTimes = _currentsTimes;
    
    if(_mode == INPUT && _currentState == HIGH){
      _pushCounts++;
    }

    if(_mode == INPUT_PULLUP && _currentState == LOW){
      _pushCounts++;
    }
  }
  return _pushCounts;
}

int PushButton::getRepeatValue(){
  int pushCounts = getPushCounts();
  return pushCounts%2;
}

