
//使用app 擴充板的s3

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
#define BTN A1
#define RELAY 4

boolean btnState = false;
byte count = 0;
//建立LCD物件
LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

void setup() {
 Serial.begin(9600);
 pinMode(BTN,INPUT_PULLUP);
 pinMode(RELAY,OUTPUT);
 //LCD初始化
 lcd.begin (16,2);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);  
  lcd.backlight();  //Backlight ON if under program control  
  displayLCD();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  boolean isOnce = monitorSwitch();
  if(isOnce){
    controlRely();
    displayLCD();
  }
  
}

boolean monitorSwitch(){
  if(digitalRead(BTN) == btnState){
      delay(30);      
      if(digitalRead(BTN) == btnState){        
        btnState = !btnState;
         count++;
         if(count == 2){      
          count = 0;
          return true;
         }
        
      }
  }
  return false;
}


void controlRely(){
  boolean lightState = !digitalRead(RELAY);
  digitalWrite(RELAY,lightState);
}

void displayLCD(){
  lcd.clear();
  lcd.setCursor(0,0); //Start at character 0 on line 0
  lcd.print("Relay State:");
  lcd.setCursor(0,1);
  
  if(digitalRead(RELAY)){    
    lcd.print("OPEN");
  }else{    
    lcd.print("CLOSE");
  }
}

