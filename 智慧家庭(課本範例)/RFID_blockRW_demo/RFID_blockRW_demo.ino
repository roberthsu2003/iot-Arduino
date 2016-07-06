/*
 * Documentation：RFID_blockRW_demo.ino
 * Created By：Evan    WWW.B2CQSHOP.COM
 * Creation Date：2011.09.19
 * Modified：
 * Translated By：Gareth Halfacree    gareth.halfacree.co.uk
 * Description：Mifare, Find Cards → Anti-Collision → Read and Write Cards
 * Translated By：Tony Su/2015/04/16    www.appsduino.com
 * Description：simplified with rfid library
 */
 // the sensor communicates using SPI, so include the library:
#include <SPI.h>
#include <RFID.h>

#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN, RST_PIN); 

// Maximum length of an array
#define MAX_LEN 16

unsigned char  writeData[16]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100};  // Initialise $100
unsigned char  moneyConsume = 18 ;  // Spend $18
unsigned char  moneyAdd = 10 ;  // Recharge $10
// Sector A Password, 16 sectors, each sector password is 6-bytes
 unsigned char sectorKeyA[16][16] = 
                             {{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
                             {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},//when you try it again, please change it into your new password
                             {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
                             {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
                            };
 unsigned char sectorNewKeyA[16][16] = 
                                {{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
                                {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xff,0x07,0x80,0x69, 0x19,0x84,0x07,0x15,0x76,0x14},
                                {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xff,0x07,0x80,0x69, 0x19,0x33,0x07,0x15,0x34,0x14},
                                {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xff,0x07,0x80,0x69, 0x19,0x33,0x07,0x15,0x34,0x14},
                               };

void setup() {                
   Serial.begin(9600);                        
 // start the SPI library:
   SPI.begin();
   rfid.init();
   delay(1000) ;
   Serial.println("RFID write/read block Example");
   Serial.println("Demo for Read/Write data in (Sector 2,Block 0) or block #8");

}

void loop()
{
  	unsigned char i,tmp;
	unsigned char status;
        unsigned char str[MAX_LEN];
        unsigned char RC_size;
        unsigned char blockAddr;	// Select the operating block address, 0-63


//-----------------------------------
        if (rfid.isCard()) {  //　檢查是否偵測到RFID Tag ? 並回傳true/false
            if (rfid.readCardSerial()) { //讀取RFID的ID/序號(4 bytes)與檢查碼(1 byte)
                /* With a new cardnumber, show it. */
                Serial.println(" ");
                Serial.println("Card found");                       
                Serial.print("Serial #(Hex) : ");
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
          }
      }
//-----------------------------------------
		// Election card, return capacity
		RC_size = rfid.SelectTag(rfid.serNum); //　選擇一張卡並回傳卡片的容量
                // Now a card is selected. The UID and SAK is in mfrc522.uid.
		if (RC_size != 0)  

		{
                        Serial.print("The size of the card is  :   ");
			Serial.print(RC_size,DEC);
                        Serial.println("K bits ");
		}
		// 　存入$100 in Registration card
		blockAddr = 11;		//驗證Data block 11中的密碼 A		
		status = rfid.auth(PICC_AUTHENT1A, blockAddr, sectorKeyA[blockAddr/4], rfid.serNum);// Authentication by verify Key A
                if (status == MI_OK)
		{
			// Write data
			status = rfid.write(blockAddr, sectorNewKeyA[blockAddr/4]);//寫入新的密碼
                        Serial.print("set the new card password, and can modify the data of the Sector ");
                        Serial.print(blockAddr/4,DEC);
                        Serial.println(" : ");
			for (i=0; i<6; i++)
		        {
              		    Serial.print(sectorNewKeyA[blockAddr/4][i],HEX);
                            Serial.print(" , ");
		        }
                        Serial.println(" ");
                        blockAddr = blockAddr - 3 ; 
                        status = rfid.write(blockAddr, writeData);//在block #8的byte #15存入$100
                        if(status == MI_OK)
                        {
                           Serial.println("You are CyberShop VIP Member, The card has  $100 !");
                        }
		}

		// Card reader
		blockAddr = 11;		//驗證Data block 11中的密碼 A		
		status = rfid.auth(PICC_AUTHENT1A, blockAddr, sectorNewKeyA[blockAddr/4], rfid.serNum);	// Authentication
		if (status == MI_OK)
		{
			// Read data
                        blockAddr = blockAddr - 3 ; 
                        status = rfid.read(blockAddr, str);//讀取Sector 2的控制區塊資料(block #11)	
			if (status == MI_OK)
			{
                                Serial.println("Read from the card ,the data is : ");
				for (i=0; i<16; i++)
				{
              			      Serial.print(str[i],DEC);
                                      Serial.print(" , ");
				}
                                Serial.println(" ");
			}
		}

                //　模擬消費/Consumer	
		blockAddr = 11;		//驗證Data block 11中的密碼 A		
		status = rfid.auth(PICC_AUTHENT1A, blockAddr, sectorNewKeyA[blockAddr/4], rfid.serNum);	// Authentication
		if (status == MI_OK)
		{
			// Read data
                        blockAddr = blockAddr - 3 ;
			status = rfid.read(blockAddr, str);
			if (status == MI_OK)
			{
                          if( str[15] < moneyConsume )
                          {
                              Serial.println(" The money is not enough !");
                          }
                          else
                          {
                              str[15] = str[15] - moneyConsume;
                              status = rfid.write(blockAddr, str);//在block #8的byte #15減去$18後再存入
                              if(status == MI_OK)
                              {
                                 Serial.print("You pay $18 for items in CyberShop Now, Your money balance is :   $");              			 Serial.print(str[15],DEC);
                                 Serial.println(" ");
                              }
                          }
			}
		}

                // Recharge	
		blockAddr = 11;		// Data block 11		
		status = rfid.auth(PICC_AUTHENT1A, blockAddr, sectorNewKeyA[blockAddr/4], rfid.serNum);	// Authentication
		if (status == MI_OK)
		{
			// Read data
                        blockAddr = blockAddr - 3 ;
			status = rfid.read(blockAddr, str);
			if (status == MI_OK)
			{
                          tmp = (int)(str[15] + moneyAdd) ;
                          //Serial.println(tmp,DEC);
                          if( tmp > 254 ) //一個Byte數值不能超過255
                          {
                              Serial.println(" The money of the card can not be more than 255 !");
                          }
                          else
                          {
                              str[15] = str[15] + moneyAdd ;
                              status = rfid.write(blockAddr, str);
                              if(status == MI_OK)
                              {
                                 Serial.print("You add $10 to your card in CyberShop,Your money balance is :  $");
              			 Serial.print(str[15],DEC);
                                 Serial.println(" ");
                              }
                          }
			}
		}
  rfid.halt();  // Enter Sleep Mode
  delay(500) ; // waiting for 0.5 sec      
}


