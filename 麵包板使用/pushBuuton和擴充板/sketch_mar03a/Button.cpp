#include "Button.h"

Button::Button(byte pinNum,int mode){
    pinNumber = pinNum;
    pinMode(pinNumber,mode);
    if(mode == INPUT_PULLUP){
        lastBtnState = true;
    }else if(mode == INPUT){
        lastBtnState = false;
    }
    
}




void Button::buttonRunning(){
    bool newBtnState = digitalRead(pinNumber);
    if(newBtnState != lastBtnState){
        lastTime = millis();
        lastBtnState = newBtnState;
        isReadyGet = true;
    }
    unsigned long newTime = millis();
    if((newTime-lastTime) >= 30 && isReadyGet == true){
        clickNum++;
        isReadyGet = false;
    }
    Serial.println(clickNum);
    clickTimes = clickNum/2;
    byte buttonTime = clickTimes % recycleCount;
    callBackArray[buttonTime]();
    delay(10);    
}


void Button::setup(callBackType *a,int num){
    callBackArray = a;
    recycleCount = num;
    
}

