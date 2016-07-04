
// 首先匯入程式庫標頭檔Timer.h
#include <Timer.h>
Timer t;	// declare one timer event

//-------- DS18B20 Temperature sensor -------------
#define   DS18B20_Pin   7  //Define DS18S20 onewire signal pin on D7
#include <OneWire.h>
#include <DS18B20.h>
DS18B20 dd(DS18B20_Pin);  // Declare one DS18B20 object : "dd" on digital pin 7
//--------------------------------------------------

void setup()
{
  Serial.begin(9600);
  t.every(1000,OneSecTimerHandler); // setup callback function
}

void loop()
{
  t.update();// 在loop裡，呼叫每個計時器的update，它才能運作更新狀態 
}

//-------- update Temperature per sec and Tx to Serial port
void OneSecTimerHandler()
{
  Serial.println(dd.getTemperature(),2);   // Read BS18B20 temperature data and print it out
}

