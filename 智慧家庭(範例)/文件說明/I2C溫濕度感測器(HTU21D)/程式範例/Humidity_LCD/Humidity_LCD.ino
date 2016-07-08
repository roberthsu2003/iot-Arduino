/* 
 HTU21D Humidity Sensor Example Code
 By: Nathan Seidle
 SparkFun Electronics
 Date: September 15th, 2013
 License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).
 
 Uses the HTU21D library to display the current humidity and temperature
 
 Open serial monitor at 9600 baud to see readings. Errors 998 if not sensor is detected. Error 999 if CRC is bad.
  
 Hardware Connections (Breakoutboard to Arduino):
 -VCC = 3.3V
 -GND = GND
 -SDA = A4 (use inline 330 ohm resistor if your board is 5V)
 -SCL = A5 (use inline 330 ohm resistor if your board is 5V)

 */

#include <Wire.h>
#include "HTU21D.h"
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
//LCD setup
#define LCD_I2C_ADDR    0x27
#define BACKLIGHT_PIN  3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7 

//Create an instance of the object
HTU21D myHumidity; //建立溫濕度物件
LiquidCrystal_I2C  lcd(LCD_I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin); //建立LCD物件
void setup()
{
  
  Serial.println("HTU21D Example!");
  lcd.begin (16,2);  // LCD初始化設定 
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("HTU21D Example!");
  
  myHumidity.begin(); //溫濕度初始化
}

void loop()
{
  float humd = myHumidity.readHumidity();
  float temp = myHumidity.readTemperature();

 lcd.setCursor(0,1);
  lcd.print("T:");
  lcd.print(temp, 1);
  lcd.write(0xdf); // print degree symbol
  lcd.print("C");
  lcd.print(" H:");
  lcd.print(humd, 1);
  lcd.print("%");

  
  delay(1000);
}
