#include "PushButton.h"
const int pushButtonPin = 2;
PushButton pushButton(pushButtonPin,INPUT_PULLUP);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(pushButton.getRepeatValue());
  
}
