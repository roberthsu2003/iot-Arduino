#include "LED.h"
LED::LED(byte pinNum){
  pin = pinNum;
  pinMode(pin,OUTPUT);
}

void LED::on(){
  digitalWrite(pin,HIGH);
}
void LED::off(){
  digitalWrite(pin,LOW);
}
