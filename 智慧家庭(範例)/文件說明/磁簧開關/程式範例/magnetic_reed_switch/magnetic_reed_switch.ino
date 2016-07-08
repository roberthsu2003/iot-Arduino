int sensorPin = 7;    // select the input pin for the sensor
int sensorValue ;

void setup() {
  pinMode(sensorPin,INPUT_PULLUP) ; // enable pull up resister
  Serial.begin(9600);
  Serial.println("Starting...");
}

void loop() {
  sensorValue = digitalRead(sensorPin); 
  if(sensorValue == LOW)
    Serial.println(".. Close detected ..") ;    
  else
    Serial.println(".. Open Detected ..");
    
  Serial.println(sensorValue);
  delay(1000);
}

