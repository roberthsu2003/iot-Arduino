
// 首先匯入程式庫標頭檔Timer.h
#include <Timer.h>
#define    greenLed     13
#define    CDS          A2

Timer t;	// declare one timer event

void setup()
{
  pinMode(greenLed, OUTPUT);
  pinMode(CDS, INPUT_PULLUP);      // enable pull up resistor
  Serial.begin(9600);
  t.oscillate(greenLed,500,LOW); // toggle LED one Sec interval 
  t.every(1000,cdsReading); // setup callback function
}

void loop()
{
  t.update();// 在loop裡，呼叫每個計時器的update，它才能運作更新狀態 
}

//-------- Check Light Status and Tx to Serial port
void cdsReading()
{
  Serial.println(analogRead(CDS)); // 讀取Analog A2 Value(ex: CDS)
}

