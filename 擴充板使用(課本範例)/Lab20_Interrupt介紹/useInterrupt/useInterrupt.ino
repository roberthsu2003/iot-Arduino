/*
 * attachInterrupt.pde: attachInterrupt() 與外部中斷
 */

const int interruptNumber = 0;           // Interrupt 0 在 pin 2 上
const int buttonPin = 2;                 // 按鈕(pushbutton)
const int ledPin = 13;                   // LED
volatile int buttonState;                // 用來儲存按鈕狀態

void setup() {
  pinMode(ledPin, OUTPUT);               // 把 ledPin 設置成 OUTPUT
  pinMode(buttonPin, INPUT);             // 把 buttonPin 設置成 INPUT
  
  // 把外部中斷(interrupt 0)連接到 buttonStateChanged() 函式
  // CHANGE 是指當 pin 狀態改變時就觸發中斷，不管是從 HIGH 到 LOW 或從 LOW 到 HIGH
  attachInterrupt(interruptNumber, buttonStateChanged, CHANGE);
}

void loop() {
  delay(1000);
}

// Interrupt 0 的中斷處理函式
// 讀取 buttonPin 的狀態，並反應到 ledPin 上
void buttonStateChanged() {
  buttonState = digitalRead(buttonPin);
  digitalWrite(ledPin, buttonState);
}
