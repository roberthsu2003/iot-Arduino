const int SW_pin = A1;

void setup() {
  Serial.begin(115200);
  pinMode(SW_pin,INPUT_PULLUP);
  pinMode(13,OUTPUT);
}

void loop() {
  int val = analogRead(SW_pin);
  
  if(val < 500){
    digitalWrite(13,HIGH);
  }else{
    digitalWrite(13,LOW);
  }

  Serial.println(val);
  delay(1000);

}
