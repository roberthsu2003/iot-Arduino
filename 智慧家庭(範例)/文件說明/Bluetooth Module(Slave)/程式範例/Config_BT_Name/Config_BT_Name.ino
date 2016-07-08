/* ----- BT module configutation program created by Tony Su 01/24/2013 ----
 1. Plug in BT module into 6 Pins BT socket then Power ON
 2. Setting BT ID to "Appsduino" and Baud rate from 9600 to 57,600 bps
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
   pinMode(LedRed,OUTPUT) ;
   pinMode(LedBlue,OUTPUT) ;   
   digitalWrite(LedRed,LOW) ; // turn off LED   
   digitalWrite(LedGreen,LOW) ; // turn off LED
   digitalWrite(LedBlue,LOW) ; // turn off LED
   Serial.begin(57600);         // Baud rate of HC-0x bluetooth module
   delay(1000);
   Serial.write("AT+NAMEAppsduino"); // setup BT ID name to Appsduino
   while(!Serial.available()) ; 
   Serial.read(); // flush feedback message
   digitalWrite(LedGreen,HIGH) ; // turn on LED    
}

void loop()
{
//  if (Serial.available()) 
//    Serial.write(Serial.read());  
}

