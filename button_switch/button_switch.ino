#include "Led.h"
#include "SwitchButton.h"
#define BtnPin 2

LED redLed(13);
SwitchButton btn(2);

void setup() {
  Serial.begin(115200); 
  redLed.off();
}

void loop() {
 unsigned int stateChangeCount = btn.getStateChangeCount();
    switch (stateChangeCount % 4) {
        case 0:
          redLed.off();
          break;
        case 2:
          redLed.on();
          break;
      }
    


  Serial.print("you click:");
  Serial.println(stateChangeCount/2);

}
