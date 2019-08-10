#define RELAY 4
boolean lightState = false;

void setup() {
  pinMode(A4,INPUT_PULLUP);
  pinMode(RELAY,OUTPUT);
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  int cdsValue = analogRead(A4);
  Serial.println(cdsValue);
  if(cdsValue > 200){
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
  
  delay(100);
}
