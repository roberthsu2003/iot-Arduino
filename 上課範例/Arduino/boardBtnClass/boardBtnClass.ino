

#include "Button.h"
#include <Timer.h>


Button btn(A1);
Timer timer;

void setup() {
  // put your setup code here, to run once:
  timer.every(100,lookup);
  pinMode(13,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 timer.update();
}

void lookup(){
    boolean currentBtnState = btn.getCurrentState();
    digitalWrite(13,currentBtnState);
}
