#define redLed 10
#define blueLed 9


void setup() {
  // put your setup code here, to run once:
  pinMode(redLed,OUTPUT);
  pinMode(blueLed,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(redLed,LOW);
  digitalWrite(blueLed,HIGH);
  delay(500);
  digitalWrite(redLed,HIGH);
  digitalWrite(blueLed,LOW);
  delay(500);
}
