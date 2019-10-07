#define dataPin D6
#define latchPin D7
#define clockPin D8

byte index1 = 0;
const byte LEDs[10] = {
  B01111110, //0
  B00110000, //1
  B01101101, //2
  B01111001, //3
  B00110011, //4
  B01011011, //5
  B01011111, //6
  B01110000,//7
  B01111111,//8
  B01110011  //9
};

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin,LSBFIRST,LEDs[index1]);
  digitalWrite(latchPin, HIGH);
  delay(1000);
  index1 ++;
  if (index1 == 10){
    index1 = 0;
  }
}
