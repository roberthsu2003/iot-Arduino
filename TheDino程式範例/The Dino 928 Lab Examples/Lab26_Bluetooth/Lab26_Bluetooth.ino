#include <MeetAndroid.h> // include Android Bluetooth Library header

MeetAndroid AppsduinoBT; //-- declare one MeetAndroid Bluetooth object  --

void setup() {
Serial.begin(57600); // setup baud rate
AppsduinoBT.registerFunction(BTCommHandler, 'c');  //register one call back function
}
void loop() {
AppsduinoBT.receive() ; // you need to keep this in your loop() to receive events   
}

void BTCommHandler (byte flag, byte numOfValues)  {//'c' flag to receive BT cmd
  int cmd = AppsduinoBT.getInt();
  If (cmd == ??) do_action ; 
  ……
}
 

