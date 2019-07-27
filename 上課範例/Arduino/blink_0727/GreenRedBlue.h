#ifndef _GREENREDBLUE_
#define _GREENREDBLUE_

#include <arduino.h>

class GreenRedBlue{
  public:
  //實體變數(Field)
  int greenLed;
  int redLed;
  int blueLed;
  
  //建立建構式
  GreenRedBlue(int green, int red, int blue);
  
  //method方法
  void blink1(long interval);
};

#endif
