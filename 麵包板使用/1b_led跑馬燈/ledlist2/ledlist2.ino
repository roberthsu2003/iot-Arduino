const byte startPin = 8;
const byte endPin = 12;
byte lightPin = startPin;

void setup() {
  for(int i = startPin ; i <= endPin ; i++){
    pinMode(i,OUTPUT);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=startPin;i<=endPin;i++){
    digitalWrite(i,LOW);    
  }
  digitalWrite(lightPin,HIGH);
  if(lightPin > endPin){
    lightPin = startPin;
  }else{
   lightPin++;
  }
  delay(500);
}
