#ifndef __BUTTON__
#define __BUTTON__

#include <arduino.h>

class Button{
  private:
    byte _pin;

  public:
    Button(byte pinNum);  
};
#endif
