/*
   Appsduino IoT Project : IoTSN Sensor Network w/RFID & BT communication project : Tony Su 2015/04/30  
   update history : 6/01
   1. Add Tx sensor data(JSON format with '{','}') to Mysql while connect to RPi
   2. Press Key while reset period will disable Tx sensor data to BT
*/

#include <Streaming.h>
/*-----( Import needed libraries )-----*/ 
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>  // F Malpartida's NewLiquidCrystal library

/*-----( Declare Constants )-----*/
#define I2C_ADDR    0x27  // Define I2C Address for the PCF8574T 
//---(Following are the PCF8574 pin assignments to LCD connections )----
#define BACKLIGHT_PIN  3
#define  LED_OFF  1
#define  LED_ON  0
/*-----( Declare objects )-----*/  
LiquidCrystal_I2C  lcd(I2C_ADDR,2,1,0,4,5,6,7); // declare I2C LCD object
/* -----  RC522 RFID Test program created by Tony Su 07/22/2013 ----
*
* Read a card using a mfrc522 reader on your SPI interface
* Pin layout should be as follows (on Arduino Uno):
* MOSI: Pin 11 / ICSP-4
* MISO: Pin 12 / ICSP-1
* SCK: Pin 13 / ISCP-3
* SS: Pin 10
* RST: Pin 9
*
*/

#include <SPI.h>
#include <RFID.h>

#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN, RST_PIN); 
//----------------------------------------------------------------------
#define   Buzzer      8      // Buzzer Pin
#define   WindowSW    7
#define   RedLed      6
#define   BlueLed     5
#define   RelayIN1    4     // Define Relay Pin
#define   RelayIN2    3
#define   NULL        '\0'   // string null terminator
#define   Keypress    A1
#define   LightSensor A2
#define   SoundSensor A3
//-----------------------------------------------------------------------
#include <MeetAndroid.h>  // include Android Bluetooth Library header
#include <Timer.h>
Timer tick ;// setup one sec timer event
//------------ For HTU21D Temperature/Humddity measure ---------
#include <HTU21D.h>
//Create an instance of the object
HTU21D myHumidity;
//----------------------------------------------------------------
volatile int CdsThreshold = 300 ; // default cds threshold,turn on blue led if > CdsThreshold
volatile boolean CdsTriggerFlag = false ;
volatile int soundPeakValue = 0 ;// Check Sound Sensor and keep the peak value during one sec interval 
//--------------------------- Melody ------------------------------
 #include "pitches.h"
// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4 };
//--------------- Android Bluetooth Test ------------
MeetAndroid AppsduinoBot;
//---------------------------------------------------
String sensorMsg = "" ; // initial sensor Message string(include Temp,HR,Rly1/2,..)
//------------------- RFID information definition ------------------
String rfid_receive_msg = " Wait" ; // initialize rfid received message
String rfid_prereceive_msg = "x    " ; // 
//--------- Define Serial Number(4 bytes) and Name(7 chars maximum)
unsigned char RFIDserNum[][4] ={{0x33,0xCC,0xC3,0xD3},
                                {0xED,0x5A,0x63,0x7C},
                                {0xA5,0x6B,0x60,0xB6},
                                {0x35,0x22,0x10,0x02},
                                {0xE2,0x07,0xD3,0xCC},
                                {0x4C,0xC3,0x14,0x46},
                                {0x7C,0x93,0x14,0x46},
                                {0x8C,0xC3,0x14,0x46},
                                {0xAC,0x7D,0x14,0x46},
                                {0xD3,0x73,0xDD,0x80},
                                {0x19,0xD9,0x41,0x03},
                                {0xB5,0x07,0x33,0xB3}
                               } ;
//-------- Maximun Name Length <= 7 chars to avoid too long App button Text ----------    
String  Name[] = { "Jenny"," Eddy"," John"," Mary",
                   "Nixon","James","Jasmi","Tracy",
                   "Stone","Wison","Steve"," Tony" } ;                   
//----------------------------------------------------------------------------------
boolean Piflag = false ; //
String  sensorMsgsql ="" ;// sensor data to mysql database 

void setup() 
{
  //---  I/O definition -----------------------------
  pinMode(RedLed, OUTPUT);
  pinMode(BlueLed, OUTPUT);
  pinMode(RelayIN1, OUTPUT);  // define Relay as Output Pin
  pinMode(RelayIN2, OUTPUT);  //   
  pinMode(Keypress,INPUT_PULLUP);  // enable pull up resister
  pinMode(LightSensor,INPUT_PULLUP);  // enable pull up resister
  pinMode(WindowSW,INPUT_PULLUP);  // enable pull up resister
  digitalWrite(RelayIN1,LOW ) ;  // HIGH Active
  digitalWrite(RelayIN2,LOW ) ;
  pinMode(Buzzer, OUTPUT);
  if(!digitalRead(Keypress)) { // check if Key is pressed then start to send the sensor data to Mysql
    digitalWrite(RedLed,HIGH) ; //turn on Red Led to indicate to connect with Raspberry Pi
    Piflag = true ; // 
  }   
  //------------ RFID Initialize ---------
  SPI.begin(); 
  rfid.init();
   //--------------------------------------
  lcd.begin (16,2);  // initialize the lcd 
  // Switch on the backlight
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(LED_ON);
  lcd.backlight();  //Backlight ON if under program control
  lcd.setCursor(0,0); //Start at character 0 on line 0
  // Configure your bluetooth module to this baud rate : 57600 bps
  Serial.begin(57600); 
//  while(!Serial) ; // wait for serial port is ready
  // register callback functions, which will be called when an associated event occurs.
  // - the first parameter is the name of your function (see below)
  // - match the second parameter ('A', 'B', 'a', etc...) with the flag on your Android application
  AppsduinoBot.registerFunction(AppsduinoiFamilyIO, 's');  
  AppsduinoBot.registerFunction(SetCdsThreshold, 'p');
  AppsduinoBot.registerFunction(sensordata2Mysql, 'r');// keep sensor data in databse 
  //------- initial HTD21D HR sensor  -------------
  myHumidity.begin();// Initialize HTU21D Humidity Sensor
  delay(2000) ; // waiting for 2 sec at least after power on for stable HR reading
  tick.every(1000, updateSensorHandler);// read sensor data from I2C slave node  
  tick.every(10, HundredmsSoundHandler);// read temperature/humidity once per second 
  lcd.setCursor(0,0); //Start at character 0 on line 0
  lcd.print("Service Now     ") ;
}

//--------------- Main Program ------------------------
void loop()
{
  int  NameIndex ;

  //-----------------------------------
  tick.update(); // check timer event
  AppsduinoBot.receive(); // you need to keep this in your loop() to receive events    
  //---------- Check RFID Name Card and show who is touching -----
  if (rfid.isCard()) {
     NameIndex = RFIDserNumLookup() ; // just show who is touching  
     if(NameIndex != -1) 
       rfid_receive_msg = Name[NameIndex] ;
     else 
        rfid_receive_msg = "Other" ;
     TxName2CO(rfid_receive_msg) ;// Tx received msg to CO 
  }
  rfid.halt();  // Enter Sleep Mode
  delay(50) ;
}

//-------------------------------------------------------------------------------------
//--- 's' flag to control RGB Led and Melody Play ----
void AppsduinoiFamilyIO(byte flag, byte numOfValues)
{
  int randomvalue = AppsduinoBot.getInt();
      
      iFamilyIO(randomvalue) ; // execute the related function

}
//--------------------- Toogle AC Light on/Off -------------------
//  Light # : 
//        1 : Toogle Light #1 on/off
//        2 : Toogle Light #2 on/off
//----------------------------------------------------------------

void iFamilyIO(int value)
{
  switch(value) {
    case 1 : // Toogle AC Light on/off 
       digitalWrite(RelayIN1,!digitalRead(RelayIN1)) ;
       break ;  
    case 2 : // Tuon off AC Light 
       digitalWrite(RelayIN2,!digitalRead(RelayIN2)) ;
       break ;      
    case 3 : // toggle Red led on /off
       digitalWrite(RedLed,!digitalRead(RedLed)) ;
       break ;  
    case 4 :  // toggle Blue led on /off
        digitalWrite(BlueLed,!digitalRead(BlueLed)) ;
       break ;
    case 5 : // melody play 
       PlayMelody(); // play melody
       break ;  
    case 6 : // Toogle AC Light on
       digitalWrite(RelayIN1,HIGH) ;
       break ;  
    case 7 : // Toogle AC Light off
       digitalWrite(RelayIN1,LOW) ;
       break ;  
  }   
}
//--------- Adjust CdsThreshold Level -----------------------
//--- 'p' flag to setup CdsThreshold Level (value : 100,200,..,800) ----
void SetCdsThreshold(byte flag, byte numOfValues)
{
    CdsThreshold = AppsduinoBot.getInt();
}
//------------------ RFID Serial Number look up and matching -----------
// Look up the RFIDserNum data base 
// return  : Name if matching
//           "None" if not found
//-----------------------------------------------------------------------

int RFIDserNumLookup()
{
  int tagCount = sizeof( RFIDserNum)/4 ; // calculate the UID count

  if (rfid.readCardSerial()) {
     for(int i=0;i < tagCount;i++) {
        if (rfid.serNum[0] == RFIDserNum[i][0] 
            && rfid.serNum[1] == RFIDserNum[i][1]
            && rfid.serNum[2] == RFIDserNum[i][2]
            && rfid.serNum[3] == RFIDserNum[i][3]
            ) 
           return i ;
      }
  }
  return -1 ;  
}
/* Created 04/6/2014
   Transmit received NFC/RFID name to smart devices
*/
void TxName2CO(String datastr) //-- 
{
    
    lcd.setCursor(0, 1);     // Display from 2nd Row
    lcd << "RFID : " << datastr << "   " ;

    if(rfid_prereceive_msg != datastr) {
       tone(Buzzer,262,20) ; // Enable Battery Low warning tone(Freq : 262 Hz,Do tone) for 20ms          
       rfid_prereceive_msg = datastr ;
       Serial <<  datastr << 'z' ; // Tx RFID message to smart devices
    }
 }
//--------------- Monitor Sound Sensor with 100ms interval & keep the peak value -----
//                Reset in the OneSecTimerHandler() 
//------------------------------------------------------------------------------------
void HundredmsSoundHandler()
{
  int Soundvalue ;

    Soundvalue = analogRead(SoundSensor) ; // read sound sensor value
    if(Soundvalue > soundPeakValue)
      soundPeakValue = Soundvalue ;
}

//-------- Read sensor data once 1 sec and Tx sensor data to Smart devices -------
// Data Format : Temp(xxx.x),Humidity(xx),Light1(x),Light2(x),LightSensor(xxx),Sound(xxx),DoorOpen(x),PIR Sensor(x) = 28 Bytes total include comma ","
// Timer Interval : 1 sec 
//------------------------------------------------------------------------------------
void updateSensorHandler() //-- update per sec -- 
{

    int cdsvalue ;
    String sensorMsg = ""  ; // Initial the Sensor message to transmit it to Master with BT
   
    sensorMsg += (int) (myHumidity.readTemperature() * 10) ;// temperature for test
    char lastDigit = sensorMsg.charAt(sensorMsg.length()-1) ;
    sensorMsg.setCharAt(sensorMsg.length()-1,'.') ; // divide 10.0 to get real temperature
    sensorMsg += lastDigit; // Add ',' separater 
    sensorMsg += ','; // Add ',' separater 
    sensorMsg +=  (int) myHumidity.readHumidity() ;
    sensorMsg += ','; // insert comma "," to be serarate delimiter
//------------ Check CDS Level if need to turn on Led -----------------
    cdsvalue = analogRead(LightSensor) ; // read CDS current value
    if(cdsvalue > CdsThreshold) {
       digitalWrite(BlueLed,HIGH) ; // turn on blue Led
      CdsTriggerFlag = true ; } // set CdsTriggerFlag = true
    else if(CdsTriggerFlag) {
       digitalWrite(BlueLed,LOW) ; // turn off blue Led
      CdsTriggerFlag = false ; }
    sensorMsg += cdsvalue ; // read CDS current value
//-----------------------------------------------------------------------
    sensorMsg += ','; // insert comma "," to be serarate delimiter
    sensorMsg += soundPeakValue ; // Insert Sound peak Value
    soundPeakValue = 0 ; // reset the sound peak value
    sensorMsg += ','; // insert comma "," to be serarate delimiter
    sensorMsg += digitalRead(WindowSW) ; // read co current value
    sensorMsg += ','; // insert comma "," to be serarate delimiter
    sensorMsg += digitalRead(RelayIN1) ; // convert to ASCII(x : 0/1)
    sensorMsg += ','; // insert comma "," to be serarate delimiter
    sensorMsg += digitalRead(RelayIN2) ; // convert to ASCII(x : 0/1)
    //--------------------------------------------------------------
//    sensorMsgsql = "{" ;
    sensorMsgsql = sensorMsg ; // record updated sensors msg
//    sensorMsgsql += "}" ;  // terminator flag  
    //--------------------------------------------------------------
    sensorMsg += ','; // insert comma "," to be serarate delimiter
    sensorMsg += CdsThreshold ; // Tx CdsThreshold Level
  //---------- Display current sensor data in the 1602 LCD display -----
  lcd.setCursor(0,0);     // Display from 1st Row
  int comaPos = sensorMsg.indexOf(',');
  comaPos = sensorMsg.indexOf(',',comaPos+1);
  comaPos = sensorMsg.indexOf(',',comaPos+1);// Total look for third ','
  comaPos = sensorMsg.indexOf(',',comaPos+1);// Total look for forth ','
  lcd << sensorMsg.substring(0, comaPos+1) << "  "; 
  lcd.setCursor(0,1);     // Display from 2nd Row
  lcd << sensorMsg.substring(comaPos+1, sensorMsg.length()) << "   " ; 
  if(!Piflag)
    Serial <<  sensorMsg << 'z' ;  
}
//--------- send the sensor data to Mysql database -----------------------
//--- 'r' flag to send the sensor data to Mysql  ----
//----------------------------------------------------
void sensordata2Mysql(byte flag, byte numOfValues) {
  
    Serial.flush() ;
    Serial <<  '{' << sensorMsgsql << '}' << '\n' ;   
}

//--------- Play melody from Arduino examples toneMelody ----
void PlayMelody() {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurations[thisNote];
    tone(8, melody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

