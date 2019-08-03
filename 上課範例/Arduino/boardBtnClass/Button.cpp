#include "Button.h"

Button::Button(byte pinNum){
  _pin = pinNum;
  pinMode(_pin,INPUT_PULLUP);
}
