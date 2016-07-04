//輸入參數 : half_Term代表半週期的長度(單位us)，
//          duration_ms代表要發音多久 (單位ms)
#define   Buzzer    8

void playTone(int half_Term, int duration_ms) {
  long elapse_ms = duration_ms * 1000L;
  while (elapse_ms >= 0) {
    digitalWrite(Buzzer, HIGH);			// 控制第5腳位  輸出5V
    delayMicroseconds(half_Term); 	// 延時 us 半週期
    digitalWrite(Buzzer, LOW);			// 改變第5腳位  輸出0V
    delayMicroseconds(half_Term); 	// 延時 us 半週期
    elapse_ms -= half_Term * 2; }
}
void setup() {
  int tempo = 500;
  
  pinMode(Buzzer, OUTPUT);
  for(int i=0;i < 5 ; i++) {
    playTone(956, tempo);  // 956 代表中音 Do , 持續500ms
    playTone(478, tempo);  // 478 代表高音 Do , 持續500ms
  }  
}
void loop() 
{
}

