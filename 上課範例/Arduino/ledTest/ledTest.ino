#include "LED.h"
#include "Timer.h"

LED led13(13);
Timer timer;

void setup() {
  // put your setup code here, to run once:
  timer.every(1000,everyRun);
}

void loop() {
  // put your main code here, to run repeatedly:
  timer.update();
  
  
}

void everyRun(){
    led13.autoBlink();
}
