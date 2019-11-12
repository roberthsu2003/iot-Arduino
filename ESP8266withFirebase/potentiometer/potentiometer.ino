#define RedPin 6
#define potPin A0
unsigned long noteTime = millis();
unsigned long note1Time = millis();
int valueOf8bit;
boolean ledState = false;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(RedPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  doSomeThing();
  blinkLed();
}

void doSomeThing() {
  
  unsigned long currentTime = millis();
  if((currentTime - noteTime) >= 100){
    noteTime = currentTime;
    
    int potValue = analogRead(potPin);
    valueOf8bit = (float)potValue / 1023 * 255; 
    Serial.println(valueOf8bit);
    analogWrite(RedPin, valueOf8bit);
  }
 
}

void blinkLed(){
  unsigned long currentTime = millis();
  if((currentTime-note1Time) >= 500){   
    note1Time = currentTime;
      Serial.println(digitalRead(RedPin));
      if(ledState == false){
        analogWrite(RedPin,valueOf8bit);
        ledState = true;
      }else{
        digitalWrite(RedPin,LOW);
        ledState = false;
      }
  }
}
