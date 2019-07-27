#include "GreenRedBlue.h"

GreenRedBlue threeOfLed(13, 12, 11);


void setup() {

}

void loop() {
  threeOfLed.blink1(200);
  delay(100);
  threeOfLed.blink2(200);
  delay(100);
}
