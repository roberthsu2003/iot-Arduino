#define GREEN 13
#define RED 12
#define BLUE 11
void blink1();

void setup() {
  // put your setup code here, to run once:
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  blink1();

}

void blink1() {
  digitalWrite(GREEN, HIGH);
  delay(300);
  digitalWrite(RED, HIGH);
  delay(300);
  digitalWrite(BLUE, HIGH);
  delay(300);
  digitalWrite(BLUE, LOW);
  delay(300);
  digitalWrite(RED, LOW);
  delay(300);
  digitalWrite(GREEN, LOW);
  delay(300);
}
