#ifndef _PUSHBUTTON_H_
#define _PUSHBUTTON_H_

#include <arduino.h>

class PushButton{
  
  private:
  int _buttonPin;
  int _pushCounts = 0;
  unsigned long _previousTimes = 0;
  unsigned long _currentsTimes = 0;
  bool _previousState;
  bool _currentState;
  int _mode=INPUT;
  
  public:
  //constructor
  PushButton(int pinNumber);
  PushButton(int pinNumber,int mode);
  //method
  int getPushCounts();
  int getRepeatValue();
  
  
};
#endif

