// 二進制方式閃爍
void setup()   {            // 只執行一次
  pinMode(９, OUTPUT);     // 設定11號腳為輸出 output
  pinMode(10, OUTPUT);     // 設定12號腳為輸出 output
  pinMode(13, OUTPUT);     // 設定13號腳為輸出 output
}
void loop()                // 不斷的重複執行
{
  for (int i=0; i<8; i++)  // 變數 i = 0~7
  {
    digitalWrite(9, bitRead(i, 0));   // 取出變數 i 的第 0 個位元值
                                          // 控制 pin11 連接的燈亮或滅 
    digitalWrite(10, bitRead(i, 1));   // 取出變數 i 的第 0 個位元值
                                          // 控制 pin12 連接的燈亮或滅 
    digitalWrite(13, bitRead(i, 2));   // 取出變數 i 的第 0 個位元值
                                          // 控制 pin13 連接的燈亮或滅 
    delay(500);              // 等 0.5 秒鐘
  }
}

