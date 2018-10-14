#include <SPI.h>
#include <MFRC522.h>     // 引用程式庫
#include <FirebaseArduino.h>
#include<ESP8266WiFi.h>


#define RST_PIN      D0        // 讀卡機的重置腳位
#define SS_PIN       D8        // 晶片選擇腳位
#define FIREBASE_HOST "arduinofirebase-6d104.firebaseio.com"
#define FIREBASE_PWD "z5lPWwjZLZuNNcUEelbJdiNaIvnR2Zfq49BuQBAa"
#define WIFI_SSID "robert_hsu"
#define WIFI_PASSWORD "1234567890"

MFRC522 mfrc522(SS_PIN, RST_PIN);  // 建立MFRC522物件
StaticJsonBuffer<200> jsonBuffer;

void setup() {
  Serial.begin(115200);
  Serial.println("RFID reader is ready!");

  SPI.begin();
  mfrc522.PCD_Init();   // 初始化MFRC522讀卡機模組

  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.print("connected:");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST,FIREBASE_PWD);
}

void loop() {
    // 確認是否有新卡片
    if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
      byte *id = mfrc522.uid.uidByte;   // 取得卡片的UID
      byte idSize = mfrc522.uid.size;   // 取得UID的長度

      Serial.print("PICC type: ");      // 顯示卡片類型
      // 根據卡片回應的SAK值（mfrc522.uid.sak）判斷卡片類型
      MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
      Serial.println(mfrc522.PICC_GetTypeName(piccType));

      Serial.print("UID Size: ");       // 顯示卡片的UID長度值
      Serial.println(idSize);
      String cardID = "";
      for (byte i = 0; i < idSize; i++) {  // 逐一顯示UID碼
        Serial.print("id[");
        Serial.print(i);
        Serial.print("]: ");
        Serial.println(id[i], HEX);       // 以16進位顯示UID值
        cardID.concat(String(id[i],HEX));
        if (i != (idSize-1)){
          cardID.concat("-");
        }
      }
      Serial.println();
      Serial.println(cardID);

      mfrc522.PICC_HaltA();  // 讓卡片進入停止模式

      //create json
      JsonObject& cardIdObject = jsonBuffer.createObject();
      cardIdObject["cardID"] = cardID;
      

      String key = Firebase.push("rfid/records/",cardIdObject);
      JsonObject& timeStampObject = jsonBuffer.createObject();
      timeStampObject[".sv"] = "timestamp";
      Firebase.push("rfid/records/" + key ,timeStampObject);
      Serial.println(key);
    } 
}
