#ifndef _LED_H_
#define _LED_H_

#include <arduino.h>
class Led{
  private:
    byte _pinNum;
    unsigned long _previousTime;
    boolean _state; 
    
  public:
    Led();
    Led(byte);
    void setPinNum(byte);
    void flashWithMillisecond(int);
    void setState(boolean);
};

#endif
