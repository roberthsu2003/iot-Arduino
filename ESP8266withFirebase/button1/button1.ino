#define BtnPin 2
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(BtnPin,INPUT);
}

void loop() {
  Serial.println(digitalRead(BtnPin));
  delay(10);
}
