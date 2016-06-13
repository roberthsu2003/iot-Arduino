void setup() {
    Serial.begin(115200);               //initial the Serial
    pinMode(13,OUTPUT);
}

void loop()
{
    if(Serial.available())
    {
        //Serial.write(Serial.read());    //send what has been received
        char incomingByte = Serial.read();
        if(incomingByte == 1){
          digitalWrite(13,HIGH);
          
        }else if (incomingByte == 0){
          digitalWrite(13,LOW);
          
        }
        Serial.write(incomingByte);
        Serial.println(incomingByte);
    }
}


