#include "Timer.h"


#define tempPin A0
#define pin0 D1
#define pin1 D2
#define pin2 D3
#define pin3 D4

#define dataPin D5
#define latchPin D6
#define clockPin D7

//delay物件
Timer t;
float tempC;

//共陽
const byte LEDs[10] = {
  B10000001, //0
  B11001111, //1
  B10010010, //2
  B10000110, //3
  B11001100, //4
  B10100100, //5
  B10100000, //6
  B10001111,//7
  B10000000,//8
  B10001100  //9
};


void setup()
{
  Serial.begin(115200); //opens serial port, sets data rate to 9600 bps
  pinMode(pin0, OUTPUT);
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);

  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  t.every(1000, oneSecondRun);
 
}

void loop()
{
  t.update();
  displayLED(tempC);
}

void oneSecondRun() {
  tempC = getTemperature();
  Serial.println(tempC);
}


  


float getTemperature() {
  float temp;
  temp = analogRead(tempPin);           //read the value from the sensor
  temp = (temp / 1024 * 3.3 / 0.01) - 2;
  return temp;
}

void displayLED(float numbers) {
  
  int n1 = numbers * 100;
  byte right1 = n1 % 10;
  byte right2 = (n1 / 10) % 10;
  byte right3 = (n1 / 100) % 10;
  byte right4 = (n1 / 1000) % 10;
  
  
  for (int i = 0; i <= 3; i++) {
    byte dotNumber;
    //處理位數
    switch (i) {
      case 0:
        digitalWrite(pin0, HIGH);
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, LEDs[right1]);
        digitalWrite(latchPin, HIGH);

        break;
      case 1:
        digitalWrite(pin0, LOW);
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
        digitalWrite(latchPin, LOW);

        shiftOut(dataPin, clockPin, LSBFIRST, LEDs[right2]);
        digitalWrite(latchPin, HIGH);
        break;
      case 2:
        digitalWrite(pin0, LOW);
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, HIGH);
        digitalWrite(pin3, LOW);
        digitalWrite(latchPin, LOW);
        dotNumber = LEDs[right3] & B01111111;
        shiftOut(dataPin, clockPin, LSBFIRST, dotNumber);
        digitalWrite(latchPin, HIGH);
        break;
      case 3:
        digitalWrite(pin0, LOW);
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, HIGH);
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, LEDs[right4]);
        digitalWrite(latchPin, HIGH);
        break;
    }
    delay(5);
  }
}
