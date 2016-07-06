// 雙閃燈
void setup()  {           // 只執行一次
  pinMode(11, OUTPUT);  // 設定D11為輸出Pin
  pinMode(12, OUTPUT);  // 設定D12為輸出Pin
}
void loop()  {          // 不斷的重複執行
  digitalWrite(11, LOW);   // 熄滅LED
  digitalWrite(12, HIGH);  // 點亮LED
  delay(500);           // 等 0.5 秒鐘
  digitalWrite(12, LOW);  // 熄滅LED
  digitalWrite(11, HIGH); // 點亮LED
  delay(500);          // 等 0.5 秒鐘
}

