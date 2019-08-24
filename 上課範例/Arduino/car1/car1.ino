#include "Mortor.h"
#include <Ultrasonic.h>
#include <Timer.h>

Mortor leftMortor(10, 9 , 6);
Mortor rightMortor(12, 11, 5);

Ultrasonic frontUltra(3,4);
Timer timer;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  timer.every(100,runUltra);
}

void loop() {
  // put your main code here, to run repeatedly:
  timer.update();
  rightMortor.setMode(STOP);
  rightMortor.setSpeed(0);
  
 
}

void runUltra(){
  long microsec = frontUltra.timing();
  int frontCM = frontUltra.convert(microsec,Ultrasonic::CM);
  Serial.println(frontCM);
}
