#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define D1 5
#define D2 4
#define D0 16
#define FIREBASE_HOST "arduinofirebase-6d104.firebaseio.com"
#define WIFI_SSID "robert_hsu"
#define WIFI_PASSWORD "1234567890"

LiquidCrystal_I2C lcd(0x27, D1, D2);

void setup() {
  //LCD
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(5, 0);
  lcd.print("HELLO");
  lcd.setCursor(5, 1);
  lcd.print("WORLD");

  //relay
  pinMode(D0,OUTPUT);

  //Wifi
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected:");
  Serial.println(WiFi.localIP());

  //Firebase
  Firebase.begin(FIREBASE_HOST);
}

String message1 = "";
String message2 = "";
int relay1 = 3;

void loop() {
  //lcd setup start............................
  
  String line1 = Firebase.getString("lcd/line1");
  String line2 = Firebase.getString("lcd/line2");
  if (!line1.equals(message1) || !line2.equals(message2)) {
    message1 = line1;
    message2 = line2;

    lcd.clear();
    int count = message1.length();
    lcd.setCursor((16 / 2) - (count / 2), 0);
    lcd.print(message1);
    if (Firebase.failed()) {
      return;
    }


    count = message2.length();
    lcd.setCursor((16 / 2) - (count / 2), 1);
    lcd.print(message2);
    if (Firebase.failed()) {
      return;
    }
  }

  //lcd setup end............

  boolean firebaseRelay1 = Firebase.getBool("lcd/relay1");
  int intRelay1 = firebaseRelay1 ? 1 : 0;
  if (intRelay1 != relay1){
    relay1 = intRelay1;
    digitalWrite(D0,relay1);
  }
  



  delay(200);
}
