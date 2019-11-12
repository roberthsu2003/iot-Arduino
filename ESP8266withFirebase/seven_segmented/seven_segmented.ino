//***********************************************************
//參考的網址
//http://programmermagazine.github.io/201307/htm/article1.html
//***********************************************************
// 七段顯示器製作倒數功能 (v1)

byte digits[10][7] = {
  { 1, 1, 1, 1, 1, 1, 0 }, // = 0
  { 0, 1, 1, 0, 0, 0, 0 }, // = 1
  { 1, 1, 0, 1, 1, 0, 1 }, // = 2
  { 1, 1, 1, 1, 0, 0, 1 }, // = 3
  { 0, 1, 1, 0, 0, 1, 1 }, // = 4
  { 1, 0, 1, 1, 0, 1, 1 }, // = 5
  { 1, 0, 1, 1, 1, 1, 1 }, // = 6
  { 1, 1, 1, 0, 0, 0, 0 }, // = 7
  { 1, 1, 1, 1, 1, 1, 1 }, // = 8
  { 1, 1, 1, 0, 0, 1, 1 } // = 9
};

byte mapArdiuinoPin[] = {2, 3, 4, 5, 6, 7, 8};

void setup() {
  Serial.begin(115200);
  for (byte i = 0; i < 7; i++) {
    pinMode(mapArdiuinoPin[i], OUTPUT);
  }
}

void loop() {
  if (Serial.available() > 0) {
    char getDigit = Serial.read();
    if (getDigit >= 48 && getDigit <= 57) {
      Serial.println(getDigit);
      displayDigit(getDigit);
    } else {
      Serial.println("error");
    }

  }
}


void displayDigit(char displayDigit){
  int displayIndex = (int)displayDigit - 48;
  for(int i=0; i<7 ; i++){
    bool onePinState = digits[displayIndex][i];
    byte pinNum = mapArdiuinoPin[i];
    digitalWrite(pinNum, onePinState);
  }
}
