#include "LED.h"

LED led13(13);

void setup() {
  // put your setup code here, to run once:
  
}

void loop() {
  // put your main code here, to run repeatedly:
  led13.on();
  delay(500);
  led13.off();
  delay(500);
}
