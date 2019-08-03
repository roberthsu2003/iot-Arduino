#include "LED.h"
LED::LED(byte pinNum){
  pin = pinNum;
  pinMode(pin,OUTPUT);
}
