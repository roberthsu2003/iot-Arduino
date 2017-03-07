#include "arduino.h"
using callBackType = void(*)(void);

class Button{
public:
    //declare Field
    
    byte pinNumber;
    bool lastBtnState;
    bool isReadyGet = false;
    unsigned long lastTime;
    unsigned int clickNum = 0;
    unsigned int clickTimes = 0;
    byte recycleCount = 2;
    callBackType *callBackArray;
    
    //declare constructure
    //建構式
    
    Button(byte pinNum,int mode);
    //declare method
    void buttonRunning();
    byte getButtonTime();
    void setup(callBackType *a,int num);
};


