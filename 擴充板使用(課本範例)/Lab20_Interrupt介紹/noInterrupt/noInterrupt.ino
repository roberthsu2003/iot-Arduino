/*
 * Button.pde: 使用按鍵 (PushButton)控制 LED 燈號的開關
 */

const int buttonPin = 2;                 // 按鈕(pushbutton)
const int ledPin = 13;                   // LED

volatile int buttonState;                // 用來儲存按鈕狀態

void setup() {
  pinMode(ledPin, OUTPUT);               // 把 ledPin 設置成 OUTPUT
  pinMode(buttonPin, INPUT);             // 把 buttonPin 設置成 INPUT
}

void loop(){
  // 讀取按鈕的狀態
  buttonState = digitalRead(buttonPin);

  // 檢查按鈕是否被按下
  // 是的話，buttonState 會是 HIGH
  if (buttonState == HIGH) {     
    digitalWrite(ledPin, HIGH);          // 打開 LED
  } 
  else {
    digitalWrite(ledPin, LOW);           // 關閉 LED
  }
}
