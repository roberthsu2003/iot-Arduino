const byte LEDs[] = {8,9,10,11,12};
const byte total = sizeof(LEDs)/sizeof(LEDs[0]);
byte indexValue = 0;

void setup() {
  // put your setup code here, to run once:
  for (byte i=0;i<total;i++){
    pinMode(LEDs[i],OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for(byte i=0;i<total;i++){
    digitalWrite(LEDs[i],LOW);
  }
  
  digitalWrite(LEDs[indexValue],HIGH);

  if(indexValue < total){
    indexValue ++;
  }else{
    indexValue = 0;
  }

  delay(500);
}
