
#define led 3
#define potentiometer A3

void setup() {
  pinMode(potentiometer,INPUT);
  pinMode(led,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int inputValue = analogRead(potentiometer);
  int outputValue = (float)inputValue / 1023 * 255;
  Serial.println(outputValue);
  analogWrite(led,outputValue);

}
