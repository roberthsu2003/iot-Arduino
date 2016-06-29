
void setup() {
  // put your setup code here, to run once:
  pinMode(A4,INPUT_PULLUP);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead(A4);
  Serial.println(val);
  delay(500);
}
