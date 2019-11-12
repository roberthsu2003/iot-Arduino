#define BtnPin 2
void setup() {
 
  Serial.begin(115200);
  pinMode(BtnPin,INPUT_PULLUP);
}

void loop() {
  Serial.println(digitalRead(BtnPin));
  delay(10);
}
