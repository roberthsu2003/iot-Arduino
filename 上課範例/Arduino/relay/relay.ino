#define IN1 D4
#define BTN D1

bool btnState;
unsigned long count = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(IN1,OUTPUT);
  pinMode(BTN,INPUT);
  btnState = digitalRead(BTN);
}

void loop() {
  // put your main code here, to run repeatedly:
  bool currentState = digitalRead(BTN);
  if(currentState != btnState){
    count += 1;
    btnState = currentState;
  }

  switch (count % 4){
    case 0:
      digitalWrite(IN1,HIGH);
      break;
    case 2:
      digitalWrite(IN1,LOW);
      break;
  }
  
}
