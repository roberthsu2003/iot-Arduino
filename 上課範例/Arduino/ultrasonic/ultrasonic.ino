#include "Ultrasonic.h"

Ultrasonic front(3,4);
Ultrasonic left(A1,A2);
ULtrasonic right(A3,A4);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
 long millsecon = front.timing();
 float frontDistance = front.convert(millsecon, Ultrasonic::CM);
 Serial.println(frontDistance);
 delay(1000);
 
}
