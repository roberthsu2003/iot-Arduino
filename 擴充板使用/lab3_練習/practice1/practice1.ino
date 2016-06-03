byte b0 = B000;
byte b1 = B001;
byte b2 = B010;
byte b3 = B100;
byte blinkings[] = {b0,b1,b2,b3};
int length;

void setup() {
  pinMode(13,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);
  length = sizeof(blinkings) / sizeof(byte);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < length; i++){
    byte current = blinkings[i];
    digitalWrite(13,bitRead(current,0));
    digitalWrite(10,bitRead(current,1));
    digitalWrite(9,bitRead(current,2));
    delay(500);
  }
}
