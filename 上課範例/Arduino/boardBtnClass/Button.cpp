#include "Button.h"



Button::Button(byte pinNum){
  _pin = pinNum;
  pinMode(_pin,INPUT_PULLUP);
  
}

boolean Button::getCurrentState(){
  int buttonState = digitalRead(_pin);
    if (buttonState == LOW) {
        return true;
    } else {
        return false;
    }
}
