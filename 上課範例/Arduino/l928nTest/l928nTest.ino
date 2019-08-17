void setup() {
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode( 9, OUTPUT);
  digitalWrite(12, HIGH); //控制右輪全速前進 
  digitalWrite(11, LOW);
  digitalWrite(10, HIGH); //控制左輪全速前進
  digitalWrite( 9, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

}
