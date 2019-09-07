#define IN1 D4
#define BTN D1

void setup() {
  // put your setup code here, to run once:
  pinMode(IN1,OUTPUT);
  pinMode(BTN,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  bool btnState = digitalRead(BTN);
  if(btnState == true){
    digitalWrite(IN1,HIGH);
  }else{
    digitalWrite(IN1,LOW);
  }
}
