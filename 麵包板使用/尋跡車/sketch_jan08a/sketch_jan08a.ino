#include "PushButton.h"
#include "Motor.h"
#include "InfraredTrack.h"
#include <LiquidCrystal_I2C.h>

const int pushButtonPin = A1;
PushButton pushButton(pushButtonPin,INPUT_PULLUP);
boolean run = false;
int pushCounts = 0;
Motor leftMotor(11,12,6);
Motor rightMotor(9,10,5);
InfraredTrack rightInfrared(A2);
InfraredTrack leftInfrared(A3);
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
lcd.begin(16, 2);

}

void loop() {
  // put your main code here, to run repeatedly:
  pushCounts= pushButton.getPushCounts();

 run = (pushCounts % 2)==0?false:true;
  if(run)  
   carRun();
  else   
   carStop();  
}


void carRun(){
  //Serial.println("run");
  //infraredValue
   Serial.println(rightInfrared.rawValue());
    delay(20);
  
   //左邊>600是黑
   //右邊>600是黑
   int rightValue = rightInfrared.rawValue();
   int leftValue = leftInfrared.rawValue();
   /*
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.println(rightValue);
   lcd.setCursor(0, 1);
   lcd.println(leftValue);
   delay(500);
   */
  
  if (leftValue<500){      
      carToRight();
      return;
   }else{     
      carToLeft();
      return;
   }

   

   if (rightValue<500){
      carToLeft();
      return;
   }else{
      carToRight();
      return;
   }

   carToStraight();
  
}

void carToLeft(){
  leftMotor.setMode("foreward");
  leftMotor.setSpeed(0);
  rightMotor.setMode("foreward");
  rightMotor.setSpeed(1);
}

void carToRight(){
  leftMotor.setMode("foreward");
  leftMotor.setSpeed(1);
  rightMotor.setMode("foreward");
  rightMotor.setSpeed(0);
}

void carToStraight(){
  leftMotor.setMode("foreward");
  leftMotor.setSpeed(4);
  rightMotor.setMode("foreward");
  rightMotor.setSpeed(4);
}

void carStop(){
  // Serial.println("stop");
  leftMotor.setMode("stop");
  leftMotor.setSpeed(0);
  rightMotor.setMode("stop");
  rightMotor.setSpeed(0);
}

