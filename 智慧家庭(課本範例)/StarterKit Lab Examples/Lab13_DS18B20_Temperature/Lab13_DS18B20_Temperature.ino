#include <OneWire.h>  
#include <DallasTemperature.h>
#define DS18B20_pin 7  // 定義常數
OneWire ds(DS18B20_pin);  // 　初始化 ds 物件
DallasTemperature DS18B20(&ds) ;// 初始化 DS18B20 物件

void setup(void) {
  Serial.begin(9600);
  DS18B20.begin(); // 啟動 DS18B20 
}
void loop() {
  DS18B20.requestTemperatures(); //由 DS18B20 物件，偵測環境溫度
  float val = DS18B20.getTempCByIndex(0); // 取得溫度值
  Serial.println(val,2);
  delay(1000);
}

