#include <Streaming.h>
#include "L298Lib.h"
// 自動閃避障礙物的車子
void setup()
{
  L298_setup();  //初始化L298馬達控制板
  DriveSingleMotor(MOTOR_M1, PWR_STOP, DIR_FORWARD);  //右馬達停止轉動
  DriveSingleMotor(MOTOR_M2, PWR_STOP, DIR_FORWARD);  //左馬達停止轉動
}
void loop()
{
  int raw_data = analogRead(3);  // 取得A3的輸入數位值(介於0~1023)
  // 若raw_data數位值偏低，代表沒有太多紅外線反射=>前方無障礙物
  // 若raw_data數位值偏高，代表有很多紅外線反射=>障礙物接近
  // 因此大概取中間值做為分界
  if(raw_data>500) {  // 遇到前有障礙物了
    DriveSingleMotor(MOTOR_M1, PWR_STOP, DIR_FORWARD);  //左右馬達都停止
    DriveSingleMotor(MOTOR_M2, PWR_STOP, DIR_FORWARD);
    digitalWrite(13, HIGH);



    DriveSingleMotor(MOTOR_M1, 3, DIR_BACKWARD);  //先讓左右馬達倒轉=>倒車0.5秒
    DriveSingleMotor(MOTOR_M2, 3, DIR_BACKWARD);
    delay(500);
    DriveSingleMotor(MOTOR_M1, 5, DIR_BACKWARD);  // 車子原地右偏轉0.7秒鐘
    DriveSingleMotor(MOTOR_M2, PWR_STOP, DIR_FORWARD);
    delay(700);
    DriveSingleMotor(MOTOR_M1, PWR_STOP, DIR_FORWARD);  //左右馬達都停止
    DriveSingleMotor(MOTOR_M2, PWR_STOP, DIR_FORWARD);
  } else {
    DriveSingleMotor(MOTOR_M1, 4, DIR_FORWARD);  // 左右馬達恢復正轉，車子前進
    DriveSingleMotor(MOTOR_M2, 4, DIR_FORWARD);
    digitalWrite(13, LOW);
  }
}


