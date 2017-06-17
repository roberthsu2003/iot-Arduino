const byte LED1 = 8;
const byte LED2 = 9;
const byte LED3 = 10;
const byte LED4 = 11;
const byte LED5 = 12;

byte leds[] = {LED1, LED2, LED3, LED4, LED5};

void setup() {
  // put your setup code here, to run once:
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
    digitalWrite(LED1,HIGH);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,LOW);
    digitalWrite(LED4,LOW);
    digitalWrite(LED5,LOW);
    delay(200);

    digitalWrite(LED1,LOW);
    digitalWrite(LED2,HIGH);
    digitalWrite(LED3,LOW);
    digitalWrite(LED4,LOW);
    digitalWrite(LED5,LOW);
    delay(200);

    digitalWrite(LED1,LOW);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,HIGH);
    digitalWrite(LED4,LOW);
    digitalWrite(LED5,LOW);
    delay(200);

    digitalWrite(LED1,LOW);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,LOW);
    digitalWrite(LED4,HIGH);
    digitalWrite(LED5,LOW);
    delay(200);

    digitalWrite(LED1,LOW);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,LOW);
    digitalWrite(LED4,LOW);
    digitalWrite(LED5,HIGH);
    delay(200);
}
