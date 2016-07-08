
#define   Relay_IN1    4
#define   Relay_IN2    3

void setup() { 
  Serial.begin(9600);               
  pinMode(Relay_IN1, OUTPUT);  
  pinMode(Relay_IN2, OUTPUT);  
}

void loop() {
  digitalWrite(Relay_IN1, HIGH);  
  digitalWrite(Relay_IN2, HIGH);
    
  delay(5000);              
  digitalWrite(Relay_IN1, LOW);    
  digitalWrite(Relay_IN2, LOW); 
    
  delay(5000);              
}

