#include "Mortor.h"
#include <Ultrasonic.h>

Mortor leftMortor(10, 9 , 6);
Mortor rightMortor(12, 11, 5);

Ultrasonic frontUltra(3,4);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  rightMortor.setMode(STOP);
  rightMortor.setSpeed(0);
  long microsec = frontUltra.timing();
  int frontCM = frontUltra.convert(microsec,Ultrasonic::CM);
  Serial.println(frontCM);
  delay(100);
}
