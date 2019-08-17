#include <Ultrasonic.h>
#define RELAY 9
#define TRIGER 3
#define ECHO 4
Ultrasonic ultrasonic(TRIGER, ECHO);
boolean lightState = false;
void setup() {
  pinMode(RELAY,OUTPUT);
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  long microsec = ultrasonic.timing();
  float cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  if(cmMsec <= 20){
    if (lightState == false){
      digitalWrite(RELAY,HIGH);
      lightState = true;
    }
  }else{
     if(lightState == true){
       digitalWrite(RELAY,LOW);
      lightState = false;
    }
  }
  Serial.println(cmMsec);
  delay(100);
}
