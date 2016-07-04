#define BlueLed   11

void setup() {
  digitalWrite(A4, HIGH);  // 開啟 A4 內建上拉電阻
  pinMode(BlueLed,OUTPUT) ;
  Serial.begin(9600);  // 初始化序列埠監控視窗的傳輸速度 9600bps
}

void loop() {    // 讀取類比輸入接腳 A4 的電壓，回傳介於 0~1023 數值
                                       
int val = analogRead(A4);  
Serial.println(val);  // 將變數val的值顯示到序列埠監控視窗

if(val > 500) 
   digitalWrite(BlueLed,HIGH) ; //Turn on Led
else
   digitalWrite(BlueLed,LOW) ; // Turn off Led

delay(500);          // 程式暫停500毫秒 (相當於0.5秒鐘)
}


