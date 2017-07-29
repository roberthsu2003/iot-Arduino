#include <HTU21D.h>
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "arduinofirebase-6d104.firebaseio.com"
#define WIFI_SSID "robert_hsu"
#define WIFI_PASSWORD "1234567890"
#define D3 0
#define soundSensor A0

boolean windowValue = false;
float humidityValue = 0.0;
float temperatureValue = 0.0;
float soundValue = 0.0;

HTU21D myHumidity;

void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST);

  pinMode(D3,INPUT_PULLUP);
  myHumidity.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  windowValue = digitalRead(D3);
  humidityValue = myHumidity.readHumidity();
  temperatureValue = myHumidity.readTemperature();
  soundValue = analogRead(soundSensor);
  Firebase.setBool("home/window",windowValue);
  Firebase.setFloat("home/humidity",humidityValue);
  Firebase.setFloat("home/temp",temperatureValue);
  Firebase.setFloat("home/sound",soundValue);
  
  delay(200);
  
}
