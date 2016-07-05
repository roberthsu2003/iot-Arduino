/* ----- BT module configutation program created by Tony Su 01/24/2013 ----
 1. Plug in BT module into 6 Pins BT socket then Power ON
 2. Setting BT ID to your specified Name 
 3. While Green LED turn on means configuration is sucessful  
 4. Turn Off Power then take BT module out
 5. Repeat to step 1 if more BT module will be configured
*/

int LedGreen = 13 ;

void setup()
{
   pinMode(LedGreen,OUTPUT) ;
   digitalWrite(LedGreen,LOW) ; // turn off LED
   Serial.begin(57600);         // Baud rate of HC-0x bluetooth module(設定已知之速率)
   delay(1000);
   Serial.println("AT+NAME=RobertDino"); // Change the "Appsduino" name to your ID name,改成你欲設定之名稱
   while(!Serial.available()) ; // waiting for 'ok' message
   Serial.read(); // flush feedback message
   digitalWrite(LedGreen,HIGH) ; // turn on LED    
}

void loop()
{
}

