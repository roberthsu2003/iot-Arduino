#include "SwitchButton.h"
#include "Led.h"

SwitchButton leftBtn(4);
SwitchButton rightBtn(2);
LED redLed(8);
LED yellowLed(9);
LED greenLed(10);

void setup() {
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long leftCounts = leftBtn.getStateChangeCount();  
  Serial.print("leftCount:");
  Serial.println(leftCounts);

  //製作left2段式
  switch (leftCounts % 4){
    case 2:
      //click一次時
      Serial.println("left1");
      redLed.on();
      yellowLed.on();
      greenLed.off();
      break;
    case 0:
      //click2次時
      Serial.println("left2");
      redLed.off();
      yellowLed.on();
      greenLed.on();
      break;     
  }

  unsigned long rightCounts = rightBtn.getStateChangeCount();
  
  
  //製作right3段式
  switch (rightCounts % 6){
    case 2:
      //click一次時
      Serial.println("right1");
     
      break;
    case 4:
      //click2次時
       Serial.println("right2");
      break;
    case 0:
      //click3次時
       Serial.println("right3");
      break;     
  }
  delay(100);
}
