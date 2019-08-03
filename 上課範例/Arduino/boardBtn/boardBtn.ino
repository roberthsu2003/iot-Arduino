unsigned long n1StartPoint;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(A1, INPUT_PULLUP);
  pinMode(13, OUTPUT);

  n1StartPoint = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long n1CurrentPoint = millis();
  if (n1CurrentPoint - n1StartPoint >= 100) {
    int buttonState = digitalRead(A1);
    if (buttonState == LOW) {
      digitalWrite(13, HIGH);
    } else {
      digitalWrite(13, LOW);
    }
    Serial.println(buttonState);
    n1StartPoint = n1CurrentPoint;
  }


}
