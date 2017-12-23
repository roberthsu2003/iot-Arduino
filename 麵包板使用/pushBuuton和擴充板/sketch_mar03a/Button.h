//Button.h
#ifndef _BUTTON_H_
#define _BUTTON_H_
#include <arduino.h>

using CallBackType = void(*)(long int);

class Button {
  private:
    int _buttonPin;
    CallBackType _callBack;
    bool _buttonState;
    long int pressTime = 0;
    
  public:
    Button(int buttonPin, CallBackType c);
    int getButtonPin();
    void running();
    void buttonSensor();
};

#endif


