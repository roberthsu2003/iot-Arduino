#include <Streaming.h>
void setup() {
  Serial.begin(9600);
}
void loop() {
  int raw_data = analogRead(3);  //偵測A3傳回的電壓值
  //若紅外線反射越強，接受器隨之導通(電阻也會下降)
  //A3的電壓也會下降，A/D轉換得到的數位值也會偏低
  Serial << "raw data : " << raw_data << endl;  //顯示結果
  delay(1000);
}

