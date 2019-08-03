#ifndef __BUTTON__
#define __BUTTON__

#include <arduino.h>

class Button{
  private:
    byte _pin;

  public:
    //建構式
    Button(byte pinNum);

    boolean getCurrentState(); 
};
#endif
