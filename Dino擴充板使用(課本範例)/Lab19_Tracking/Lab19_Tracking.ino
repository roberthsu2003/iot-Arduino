#include <Streaming.h>
#include "L298Lib.h"
//　沿著黑線走
void setup()
{
  Serial.begin(9600);
  L298_setup();  //初始化L298馬達控制板
  DriveSingleMotor(MOTOR_M1, PWR_STOP, DIR_FORWARD);  //右馬達停止轉動
  DriveSingleMotor(MOTOR_M2, PWR_STOP, DIR_FORWARD);  //左馬達停止轉動
}

void loop()
{
  
  int raw_data = analogRead(3);  // 取得A3的輸入數位值(介於0~1023)
  // 若raw_data數位值偏低，代表紅外線照射到白色部分，實際試驗值可能是250左右
  // 若raw_data數位值偏高，代表紅外線照射到黑色部分，實際試驗值可能是750左右
  // 因此大概取中間值做為分界
  Serial.println(raw_data);
  if(raw_data<500) {    // 若紅外線照射到白色
    DriveSingleMotor(MOTOR_M1, 5, DIR_FORWARD);  //右馬達出力
    DriveSingleMotor(MOTOR_M2, PWR_STOP, DIR_FORWARD);  //左馬達停止
    digitalWrite(13, HIGH);  // 指示燈點亮
  } else { // 若紅外線照射到黑色

    DriveSingleMotor(MOTOR_M1, PWR_STOP, DIR_FORWARD);  //右馬達停止
    DriveSingleMotor(MOTOR_M2, 5, DIR_FORWARD);  //左馬達出力
    digitalWrite(13, LOW);  // 指示燈熄滅
  }
  
}

