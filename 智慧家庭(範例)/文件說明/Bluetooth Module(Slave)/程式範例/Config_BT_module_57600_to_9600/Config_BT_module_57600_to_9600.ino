/* ----- BT module configutation program created by Tony Su 01/24/2013 ----
 1. Plug in BT module into 6 Pins BT socket then Power ON or BT Tx --> Rx(D0),BT Rx --> Tx(D1)
 2. Setting Baud rate from 57600 to 9,600 bps
 3. While R,G,B LED or Led13 turn on means configuration is sucessful  
 4. Turn Off Power then take BT module out
 5. Repeat to step 1 if more BT module will be confirged
*/

int LedGreen = 13 ;
int LedRed = 12 ;
int LedBlue = 11 ;

void setup()
{
   pinMode(LedGreen,OUTPUT) ;
   pinMode(LedBlue,OUTPUT) ;   
   digitalWrite(LedGreen,LOW) ; // turn off LED
   digitalWrite(LedBlue,LOW) ; // turn off LED
   Serial.begin(57600);         // Baud rate of HC-0x bluetooth module
   delay(1000);
   Serial.write("AT+BAUD4");   // Set baud rate as 57600
   digitalWrite(LedBlue,HIGH) ; // turn on Blue LED 
   while(!Serial.available()) ; // wait for feedback "OK"
   Serial.read(); 
   digitalWrite(LedGreen,HIGH) ; // turn on LED    
}

void loop()
{

}

