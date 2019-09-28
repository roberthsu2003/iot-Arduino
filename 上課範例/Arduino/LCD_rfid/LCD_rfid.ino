//https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads/

#include <Wire.h>  // Arduino IDE 內建
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <RFID.h>


#define SS_PIN D8
#define RST_PIN D0
RFID rfid(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // 設定 LCD I2C 位址

int serNum0;
int serNum1;
int serNum2;
int serNum3;
int serNum4;
    
void setup() {
  Serial.begin(115200);  // 用於手動輸入文字
  lcd.begin(16, 2);      // 初始化 LCD，一行 16 的字元，共 2 行，預設開啟背光

  // 閃爍三次
  for(int i = 0; i < 3; i++) {
    lcd.backlight(); // 開啟背光
    delay(250);
    lcd.noBacklight(); // 關閉背光
    delay(250);
  }
  lcd.backlight();

  // 輸出初始化文字
  lcd.setCursor(0, 0); // 設定游標位置在第一行行首
  lcd.print("Hello, world!");
  delay(1000);
  lcd.setCursor(0, 1); // 設定游標位置在第二行行首
  lcd.print("Robert_HSU");


 //rfif
 SPI.begin();
 rfid.init();
}

void loop() {
  if(rfid.isCard()){
    if(rfid.readCardSerial()){
      if (rfid.serNum[0] != serNum0 
      && rfid.serNum[1] != serNum1 
      && rfid.serNum[2] != serNum2 
      && rfid.serNum[3] != serNum3 
      && rfid.serNum[4] != serNum4){
        Serial.println(" ");
        Serial.println("Card found");
        serNum0 = rfid.serNum[0];
        serNum1 = rfid.serNum[1];
        serNum2 = rfid.serNum[2];
        serNum3 = rfid.serNum[3];
        serNum4 = rfid.serNum[4];
        lcd.clear();
        String cardid = String(serNum0) + "-" + String(serNum1) + "-" + String(serNum2) + "-" + String(serNum3)+ "-" + String(serNum4) ;
        lcd.setCursor(0, 0); // 設定游標位置在第一行行首
        lcd.print("cardID:");
        delay(500);
        lcd.setCursor(0, 1); // 設定游標位置在第二行行首
        lcd.print(cardid);
        Serial.println("Cardnumber:");
        Serial.print("Dec: ");
        Serial.print(rfid.serNum[0],DEC);
        Serial.print(", ");
        Serial.print(rfid.serNum[1],DEC);
        Serial.print(", ");
        Serial.print(rfid.serNum[2],DEC);
        Serial.print(", ");
        Serial.print(rfid.serNum[3],DEC);
        Serial.print(", ");
        Serial.print(rfid.serNum[4],DEC);
        Serial.println(" ");

        Serial.print("Hex: ");
        Serial.print(rfid.serNum[0],HEX);
        Serial.print(", ");
        Serial.print(rfid.serNum[1],HEX);
        Serial.print(", ");
        Serial.print(rfid.serNum[2],HEX);
        Serial.print(", ");
        Serial.print(rfid.serNum[3],HEX);
        Serial.print(", ");
        Serial.print(rfid.serNum[4],HEX);
        Serial.println(" ");

      } else
      {
         Serial.print(".");
      }
    }
  }
  
}
