#ifndef __MORTOR__
#define __MORTOR__

#include <arduino.h>

typedef enum {
  STOP,FOREWARD, BACKWARD
} MortorMode;

class Mortor{
  private:
    int _modePin1;
    int _modePin2;
    int _speedPin;
    int _speed = 0;
    MortorMode _mode = STOP;//stop, foreward, backward
    
  public:
    Mortor(int modePin1, int modePin2, int speedPin);
};

#endif
