void setup()  {   // 只執行一次

  // put your setup code here, to run once;
  pinMode(13, OUTPUT);  // 設定D13為輸出 output 
}

void loop()  {          // 不斷的重複執行
  // put your main code here, to ryn repeatedly;
  digitalWrite(13, HIGH);  // 點亮LED
  delay(500);           // 等 0.5 秒鐘
  digitalWrite(13, LOW);  // 熄滅LED
  delay(500);          // 等 0.5 秒鐘
}
