#include "LED.h"
#include "Timer.h"

LED led13(13);
Timer timer;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  timer.every(1000,every1000Run);
  timer.every(2000,every2000Run);
}

void loop() {
  // put your main code here, to run repeatedly:
  timer.update();
  
  
}

void every1000Run(){
    led13.autoBlink();
    Serial.println("1000");
}

void every2000Run(){
   Serial.println("2000");
}
