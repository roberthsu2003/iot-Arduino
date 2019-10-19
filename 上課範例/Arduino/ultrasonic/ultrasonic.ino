#include "Ultrasonic.h"

Ultrasonic front(3, 4);
Ultrasonic right(A1, A2);
Ultrasonic left(A3, A4);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
ultrasonicSensor();

}

void ultrasonicSensor() {
  // put your main code here, to run repeatedly:
  long frontMillsecon = front.timing();
  float frontDistance = front.convert(frontMillsecon, Ultrasonic::CM);
  Serial.print("Front-->");
  Serial.println(frontDistance);
  //left
  long leftMillsecon = left.timing();
  float leftDistance = front.convert(leftMillsecon, Ultrasonic::CM);
  Serial.print("Left-->");
  Serial.println(leftDistance);

  //right
  long rightMillsecon = right.timing();
  float rightDistance = right.convert(rightMillsecon, Ultrasonic::CM);
  Serial.print("Right-->");
  Serial.println(rightDistance);

  delay(1000);
}
