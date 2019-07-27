#include "GreenRedBlue.h"


GreenRedBlue::GreenRedBlue(int green, int red, int blue){
  greenLed = green;
  redLed = red;
  blueLed = blue;
  pinMode(greenLed,OUTPUT);
  pinMode(redLed,OUTPUT);
  pinMode(blueLed,OUTPUT);
}

void GreenRedBlue::blink1(long interval){
    digitalWrite(greenLed,HIGH);
    delay(interval);
    digitalWrite(redLed,HIGH);
    delay(interval);
    digitalWrite(blueLed,HIGH);
    delay(interval);
    digitalWrite(blueLed,LOW);
    delay(interval);
    digitalWrite(redLed,LOW);
    delay(interval);
    digitalWrite(greenLed,LOW);
    delay(interval);
}

void GreenRedBlue::blink2(long interval){
    digitalWrite(greenLed,HIGH);
    delay(interval);
    digitalWrite(redLed,HIGH);
    delay(interval);
    digitalWrite(blueLed,HIGH);
    delay(interval);

    delay(2000);
    
    digitalWrite(blueLed,LOW);
    delay(interval);
    digitalWrite(redLed,LOW);
    delay(interval);
    digitalWrite(greenLed,LOW);
    delay(interval);

    delay(2000);
}
