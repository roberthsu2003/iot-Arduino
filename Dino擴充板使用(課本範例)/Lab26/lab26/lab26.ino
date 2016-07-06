#include <Ultrasonic.h>
#define TRIGGER_PIN A2
#define ECHO_PIN A3

Ultrasonic ultrasonic(TRIGGER_PIN,ECHO_PIN);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec,Ultrasonic::CM);
  inMsec = ultrasonic.convert(microsec,Ultrasonic::IN);
  Serial.print("MS:");
  Serial.print(microsec);
  Serial.print(", CM:");
  Serial.print(cmMsec);
  Serial.print(", IN:");
  Serial.println(inMsec);
  delay(1000);
}
