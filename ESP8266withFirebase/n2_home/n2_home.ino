#include <HTU21D.h>
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>

#define FIREBASE_HOST ""
#define WIFI_SSID ""
#define FIREBASE_AUTH ""
#define WIFI_PASSWORD ""
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
  
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);

  pinMode(D3,INPUT_PULLUP);
  myHumidity.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  windowValue = digitalRead(D3);
  humidityValue = myHumidity.readHumidity();
  Serial.print("humidityValue:");
  Serial.println(humidityValue);
  
  temperatureValue = myHumidity.readTemperature();

  Serial.print("temperatureValue:");
  Serial.println(temperatureValue);
  
  soundValue = analogRead(soundSensor);
  Serial.print("soundValue:");
  Serial.println(soundValue);
  Serial.print("windowValue");
  Serial.println(windowValue);
  
  Firebase.setBool("home/window",windowValue);
  Firebase.setFloat("home/humidity",humidityValue);
  Firebase.setFloat("home/temp",temperatureValue);
  Firebase.setFloat("home/sound",soundValue);
  
  delay(200);
  
}
