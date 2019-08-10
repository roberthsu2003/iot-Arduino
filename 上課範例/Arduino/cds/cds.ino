void setup() {
  pinMode(A4,INPUT_PULLUP);
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  int cdsValue = analogRead(A4);
  Serial.println(cdsValue);
  delay(500);
}
