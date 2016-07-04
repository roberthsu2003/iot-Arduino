#define  TRIGPIN   10
#define  ECHOPIN  11
#define LED1        12
#define LED2        13
 
long ping() {
  
digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
  return pulseIn(ECHOPIN, HIGH)/58;
}

void setup() {
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  long cm = ping();
  
  if (cm <= 100) {
    digitalWrite(LED1, HIGH);
    delay(cm*1.5 + 10);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    delay(cm*1.5 + 10);
    digitalWrite(LED2, LOW);
  }
    delay(100);
}

