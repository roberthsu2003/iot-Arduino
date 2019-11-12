#include "SevenSegmented.h"
byte mapArdiuinoPin[] = {2, 3, 4, 5, 6, 7, 8};
SevenSegmented sl_01(mapArdiuinoPin);

void setup() {
  // put your setup code here, to run once:
 
}

void loop() {
 for(int i=9;i>=0;i--){
  sl_01.displaySingleNumber(i);
  delay(100);
 }

}
