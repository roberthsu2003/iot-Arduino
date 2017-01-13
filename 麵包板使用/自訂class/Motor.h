#ifndef _MOTOR_H_
#define _MOTOR_H_
#include <arduino.h>
class Motor{
  protected:
    int _modePin1;
    int _modePin2;
    int _speedPin;
    int _speed;
    String _mode;
    void changeMotorState();
   public:
    Motor(int pin1,int pin2,int speedPin);
    void setSpeed(int speed);//speed 0~4,default=0
    void setMode(String mode);//"stop","foreward","backward".default="stop"
};
#endif


