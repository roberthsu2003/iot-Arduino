//Button.cpp
#include "Button.h"

Button::Button(int buttonPin, CallBackType c) {
  _buttonPin = buttonPin;
  pinMode(_buttonPin, INPUT_PULLUP);
  _buttonState = digitalRead(_buttonPin);
  _callBack = c;
}

int Button::getButtonPin() {
  return _buttonPin;
}

void Button::buttonSensor() {
  //取得按下放開的次數
  bool lastButtonState = digitalRead(_buttonPin);
  if (_buttonState != lastButtonState) {
    
    //使用delay才不會bounce
    delay(20);     
      if (lastButtonState == digitalRead(_buttonPin)) {
        pressTime++;
        _callBack(pressTime);
        
      }
      _buttonState = digitalRead(_buttonPin);
    

  }
}

void Button::running() {
  buttonSensor();
}


