const int SW_pin = A1;  // 指定 A1 接腳連接按鈕
void setup() {
  Serial.begin(9600);           // 初始化序列埠監控視窗的傳輸速度　 
  pinMode(SW_pin, INPUT_PULLUP);// 規劃SW_PIN為數位輸入接腳並啟動其內建上拉電阻
  pinMode(13, OUTPUT);         // 規劃 13接腳 為數位輸出接腳
}
void loop() {
  int val = analogRead(SW_pin);  // 取得輸入按鈕的狀態  
  if (val<500) {  // 依照電路設計  按下按鈕=0  放開按鈕=1
    digitalWrite(13, HIGH);  //　按下按鈕=>燈亮
  } else {
    digitalWrite(13, LOW);   //　放開按鈕=>燈滅
  }
  Serial.println(val);       // 將變數val的值顯示到序列埠監控視窗
  delay(100);         // 程式暫停100毫秒 (相當於0.1秒鐘)
}

