#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

//定義LCD pin
#define I2C_ADDR    0x27
#define BACKLIGHT_PIN  3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

//定義pin 
#define REED 7
#define RELAY 4

boolean reedState;
byte count = 0;
//建立LCD物件
LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

void setup() {
 Serial.begin(9600);
 pinMode(REED,INPUT_PULLUP);
 pinMode(RELAY,OUTPUT);
 
 //LCD初始化
 lcd.begin (16,2);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);  
  lcd.backlight();  //Backlight ON if under program control  
  displayLCD();

  //REED初始化
  reedState = digitalRead(REED);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  boolean isChanged = monitorREEDStateChanged();
  if(isChanged){
    controlRely();
    displayLCD();
  }
  
}

boolean monitorREEDStateChanged(){
  boolean currentReedState = digitalRead(REED);
  if(currentReedState != reedState){
    reedState = currentReedState;
    return true;
  }
  return false;
}


void controlRely(){
  boolean lightState = digitalRead(REED);//不導通，代表REED打開，不導通為１
  digitalWrite(RELAY,lightState);
}

void displayLCD(){
  lcd.clear();
  lcd.setCursor(0,0); //Start at character 0 on line 0
  lcd.print("Need State:");
  lcd.setCursor(0,1);
  
  if(digitalRead(REED)){ //不導通，代表REED打開，不導通為１   
    lcd.print("OPEN");
  }else{    
    lcd.print("CLOSE");
  }
}

