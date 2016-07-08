int sensorPin = A3;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  Serial.begin(9600);
  Serial.println("Starting...");
}

void loop() {
  sensorValue = analogRead(sensorPin); 
  Serial.print("Sound Level : ") ;    
  Serial.println(sensorValue);
  delay(10); // 每10 ms 取樣一次
}

