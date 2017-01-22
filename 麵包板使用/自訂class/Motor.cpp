#include "Motor.h"
String Motor::STOP = "stop";
String Motor::FOREWARD = "foreward";
String Motor::BACKWARD = "backward";
 Motor::Motor(int pin1,int pin2,int speedPin){
      _modePin1 = pin1;
      _modePin2 = pin2;
      this -> _speedPin = speedPin;
      _speed = 0;
      _mode = "stop";
    }
 void Motor::setSpeed(int speed){
    if(this -> _speed != speed){
      this -> _speed = speed;
      changeMotorState();
    }
 }

 void Motor::setMode(String mode){
    if(this -> _mode != mode){
      this -> _mode = mode;
      changeMotorState();
    }
 }

 void Motor::changeMotorState(){
  int speedValue = map(_speed,0,4,50,255);
  analogWrite(_speedPin,speedValue);
  if(_mode == "stop"){
      digitalWrite(_modePin1,LOW);
      digitalWrite(_modePin2,LOW);
    }else if(_mode == "foreward"){
       digitalWrite(_modePin1,HIGH);
       digitalWrite(_modePin2,LOW);
    }else if(_mode == "backward"){
       digitalWrite(_modePin1,LOW);
       digitalWrite(_modePin2,HIGH);
    }
 }
