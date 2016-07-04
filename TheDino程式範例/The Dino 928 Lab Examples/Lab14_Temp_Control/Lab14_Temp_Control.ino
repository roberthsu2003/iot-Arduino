#include <Streaming.h>
#include <OneWire.h>  
#include <DallasTemperature.h>

#define DS18B20_pin 7  // 定義常數
const unsigned long IntervalTime = 1000;
const unsigned int AlarmTemp = 40;  //警戒溫度
const unsigned int UpperTemp = 30;  //上限溫度

unsigned long CurrTime, PrevTime;

OneWire ds(DS18B20_pin);  // 　初始化 ds 物件
DallasTemperature DS18B20(&ds); // 初始化 DS18B20 物件

void setup(void)  {

  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
 Serial.begin(9600);
  DS18B20.begin(); // 啟動 DS18B20 
  PrevTime = millis();
}

void loop()
{
  CurrTime = millis();
  if (CurrTime -PrevTime > IntervalTime)
  {  //　每隔一秒偵測一次溫度
    DS18B20.requestTemperatures(); //由 DS18B20 物件，偵測環境溫度
    int val = DS18B20.getTempCByIndex(0); // 取得溫度值
    Serial << val << endl;  //顯示溫度
      
    if (val >= UpperTemp)  //若到達上限溫度 點亮pin13綠燈
      digitalWrite(13, HIGH);
    else
      digitalWrite(13, LOW);
    if (val >= AlarmTemp)  //若到達警戒溫度 發出警報聲
      digitalWrite(8, HIGH);
    else
      digitalWrite(8, LOW);
    PrevTime = CurrTime;
  }
}

