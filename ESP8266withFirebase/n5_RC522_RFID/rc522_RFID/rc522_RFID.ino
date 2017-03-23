/**
  Read a card using a mfrc522 reader on your SPI interface
  Pin layout should be as follows (on Arduino Uno):
  MOSI: Pin 11 / ICSP-4
  MISO: Pin 12 / ICSP-1
  SCK: Pin 13 / ISCP-3
  SS: Pin 10
  RST: Pin 9

  Script is based on the script of Miguel Balboa.
  New cardnumber is printed when card has changed. Only a dot is printed
  if card is the same.

  @version 0.1
  @author Henri de Jong
  @since 06-01-2013
*/

#include <SPI.h>
#include <RFID.h>
#include "Firebase.h"

#define SS_PIN 15
#define RST_PIN 16

Firebase firebase("arduinofirebase-6d104.firebaseio.com");
RFID rfid(SS_PIN, RST_PIN);
unsigned long lastTime = millis();

// Setup variables:
int serNum0;
int serNum1;
int serNum2;
int serNum3;
int serNum4;

void setup()
{
  Serial.begin(9600);
  SPI.begin();
  rfid.init();

  firebase.connectedToWifi("robert_hsu_home", "0926656000");

}

void loop()
{
  if (millis() - lastTime > 1000) {
    lastTime = millis();
    if (rfid.isCard()) {
      if (rfid.readCardSerial()) {
        if (rfid.serNum[0] != serNum0
            || rfid.serNum[1] != serNum1
            || rfid.serNum[2] != serNum2
            || rfid.serNum[3] != serNum3
            || rfid.serNum[4] != serNum4
           ) {
          /* With a new cardnumber, show it. */
          Serial.println(" ");
          Serial.println("Card found");
          serNum0 = rfid.serNum[0];
          serNum1 = rfid.serNum[1];
          serNum2 = rfid.serNum[2];
          serNum3 = rfid.serNum[3];
          serNum4 = rfid.serNum[4];

          //Serial.println(" ");
          Serial.println("Cardnumber:");
          Serial.print("Dec: ");
          Serial.print(rfid.serNum[0], DEC);
          Serial.print(", ");
          Serial.print(rfid.serNum[1], DEC);
          Serial.print(", ");
          Serial.print(rfid.serNum[2], DEC);
          Serial.print(", ");
          Serial.print(rfid.serNum[3], DEC);
          Serial.print(", ");
          Serial.print(rfid.serNum[4], DEC);
          Serial.println(" ");

          Serial.print("Hex: ");
          Serial.print(rfid.serNum[0], HEX);
          Serial.print(", ");
          Serial.print(rfid.serNum[1], HEX);
          Serial.print(", ");
          Serial.print(rfid.serNum[2], HEX);
          Serial.print(", ");
          Serial.print(rfid.serNum[3], HEX);
          Serial.print(", ");
          Serial.print(rfid.serNum[4], HEX);
          Serial.println(" ");
          //run firebase
          firebase.connectedToFirebase();
          String id = "";
          for(int i=0;i<4;i++){
            char charVal[2];
            sprintf(charVal,"%2X",rfid.serNum[i]);
            id += (String(charVal));
            if(i!=3){
              id += "-";
            }
          }
          firebase.postJSONData(id);
        } else {
          /* If we have the same ID, just write a dot. */
          Serial.print(".");
        }


      }

    } else {
      serNum0 = 0;
      serNum1 = 0;
      serNum2 = 0;
      serNum3 = 0;
      serNum4 = 0;
      Serial.println("no card or times error");
      
    }
    rfid.halt();

    
  }
}

