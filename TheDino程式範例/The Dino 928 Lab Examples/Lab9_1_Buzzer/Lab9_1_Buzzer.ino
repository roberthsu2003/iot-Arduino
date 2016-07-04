#define   Buzzer   8    // 定義Buzzer腳位
void setup() { 
  pinMode(Buzzer, OUTPUT); // 設定D8為數位輸出

  for(int i=0;i < 1 ; i++) {  
    digitalWrite(Buzzer, HIGH); //對Buzzer不斷輸出高、低電位，讓 Buzzer 快速發出振動聲
    delay(100); //delay()函數可以控制發聲的頻率
    digitalWrite(Buzzer, LOW);
    delay(100);
  }
}
void loop() 
{ 
}

