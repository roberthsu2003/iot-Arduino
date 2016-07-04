#include <Streaming.h>
const int R1 = 1000;  //R1 電阻值
const int R2 = 1000;  //R2 電阻值
const  float  f1= 1024.0  * R2 / (R1 + R2);  //計算轉換係數

void setup() {
  Serial.begin(9600);
}
void loop() {
  int raw_data = analogRead(0);  // 依據 A0 檢測電壓傳回介於 0~1023 的值
  float map_data = (raw_data / f1) * 5.0;  //計算轉換後的電壓值

  Serial << "raw data: " << raw_data << '\t';    //顯示原始資料
  Serial << "\t voltage: " << map_data << endl;  //顯示轉換後的電壓值
  delay(1000);
}
