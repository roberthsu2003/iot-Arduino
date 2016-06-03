
void setup() {
  // put your setup code here, to run once:
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(13,OUTPUT);
}

void loop() {
  for (int i = 0; i<8 ; i++)
  {
    digitalWrite(9, bitRead(i,0));
    digitalWrite(10, bitRead(i, 1));
    digitalWrite(13, bitRead(i, 2));
    delay(500);
  }

}
