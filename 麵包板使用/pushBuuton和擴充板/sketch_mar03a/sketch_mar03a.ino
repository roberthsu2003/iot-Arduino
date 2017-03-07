#include "Button.h"

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

Button btnS3(9, INPUT_PULLUP);
unsigned int lastTimes = 10000;

void DoJob1();
void DoJob2();
void DoJob3();
void runButton();




void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);  
  callBackType a[] = {DoJob1,DoJob2,DoJob3};
  btnS3.setup(a,3);
  
  lcd.begin(16, 2);
  lcd.backlight();

  pinMode(A2,INPUT_PULLUP);
 

  
}

void loop() {
  // put your main code here, to run repeatedly:
   btnS3.buttonRunning();
   
}





void DoJob1() {
  Serial.println("one");  
  
  
  
  lcd.clear();
  lcd.setCursor(0, 0); // 設定游標位置在第一行行首
  lcd.print("light");  
  lcd.setCursor(0, 1); // 設定游標位置在第二行行首
  int val = analogRead(A2);
  Serial.println(val);
  lcd.print(val); 
  
}

void DoJob2() {
 Serial.println("two");
 lcd.clear();
 lcd.setCursor(0, 0); // 設定游標位置在第一行行首
 lcd.print("Welcome!");

  lcd.setCursor(0, 1); // 設定游標位置在第二行行首
  lcd.print("Two");
}

void DoJob3() {
  Serial.println("three");
  lcd.clear();
  lcd.setCursor(0, 0); // 設定游標位置在第一行行首
  lcd.print("Welcome!");

  lcd.setCursor(0, 1); // 設定游標位置在第二行行首
  lcd.print("Three");
}










