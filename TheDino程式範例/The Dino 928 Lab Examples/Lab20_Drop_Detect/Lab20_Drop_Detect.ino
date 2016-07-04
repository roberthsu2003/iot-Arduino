#include <Streaming.h>
#include "L298Lib.h"
//　不會掉下去的車子
void setup()
{
  L298_setup();  //初始化L298馬達控制板
  DriveSingleMotor(MOTOR_M1, PWR_STOP, DIR_FORWARD);  //右馬達停止轉動
  DriveSingleMotor(MOTOR_M2, PWR_STOP, DIR_FORWARD);  //左馬達停止轉動
}
void loop()
{
  int raw_data = analogRead(3);  // 取得A3的輸入數位值(介於0~1023)
  // 若raw_data數位值偏低，代表紅外線照射到白色桌面，實際試驗值可能是250左右
  // 若raw_data數位值偏高，代表紅外線照射到邊緣懸崖，實際試驗值可能是750左右
  // 因此大概取中間值做為分界
  if(raw_data>500) {  // 遇到懸崖
    DriveSingleMotor(MOTOR_M1, PWR_STOP, DIR_FORWARD);  //左右馬達都停止
    DriveSingleMotor(MOTOR_M2, PWR_STOP, DIR_FORWARD);
    digitalWrite(13, HIGH);


    DriveSingleMotor(MOTOR_M1, 3, DIR_BACKWARD);  //先讓左右馬達倒轉=>倒車0.5秒
    DriveSingleMotor(MOTOR_M2, 3, DIR_BACKWARD);
    delay(500);
    DriveSingleMotor(MOTOR_M1, 5, DIR_BACKWARD);  // 車子原地右偏轉1秒鐘
    DriveSingleMotor(MOTOR_M2, PWR_STOP, DIR_FORWARD);
    delay(1000);
    DriveSingleMotor(MOTOR_M1, PWR_STOP, DIR_FORWARD);  //左右馬達都停止
    DriveSingleMotor(MOTOR_M2, PWR_STOP, DIR_FORWARD);
  } else {
    DriveSingleMotor(MOTOR_M1, 4, DIR_FORWARD);  // 左右馬達恢復正轉，車子前進
    DriveSingleMotor(MOTOR_M2, 4, DIR_FORWARD);
    digitalWrite(13, LOW);
  }
}


