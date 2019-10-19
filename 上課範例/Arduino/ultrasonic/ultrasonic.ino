#include "Ultrasonic.h"

Ultrasonic front(3,4);

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
