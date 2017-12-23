#include "Button.h"

#define ledPin 13




//使用lambda=暱名function
Button buttonS3(A1, [](long int pressNumber) {
  //Serial.println(pressNumber);
  switch (pressNumber % 6){
    case 2:
      Serial.println("S3 First");
      break;
    case 4:
      Serial.println("S3 Second");
      break;
    case 0:
      Serial.println("S3 Third");
      break;
  }
});

Button buttonS4(A0, [](long int pressNumber){
  switch (pressNumber % 4){
    case 2:
      Serial.println("S4 First");
      break;
    
    case 0:
      Serial.println("S4 Second");
      break;
  }
  });

void setup() {
  Serial.begin(115200);
  //Serial.print(buttonS1.getButtonPin());
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonS3.running();
  buttonS4.running();

}






