\
/*
   The Dino 928 RC Car : Tony Su 2012/11/7
*/

/* Revised History : V1.0 
4/12/2013
1. Revised Battery Ratio calculation formula(3.65 ~ 4.16V) and use map() funtion 

4/13/2013 :
1. revised ultrosound detect touch the back 7cm to backward for 1.5 sec to avoid infinite moving due to meet object
2. Battery low then enable Buzzer beep(once 1sec)
3. Add infraRed drop detect in A2 pin,If AD Value > InfraredThreshold then Backward and turn left/right by predefine time period

4/21/2013 :
1. Add Play AmeiAmei song melody and add "#define MelodySongPlay 7" then put in DCMotor routine. If play melody then need to wait to end. 
1/18/2014 :
1. Add PID mode option(default : no PID control,enable by App)
2. Shorten the melody time 

6/16/2014 :
1.create DS18B20 library and use that to simplify the program

03/2015 : V1.01
 - add add  "(DistanceDetect() > 0)"to check if ultrasound is exist or not ? 
   if yes then enable 50ms monitor distance,otherwise it will slow the response with BT 
*/

#include <MeetAndroid.h>  // include Android Bluetooth Library header
#include <Timer.h>

//-------- DS18B20 Temperature sensor -------------
#define   DS18B20_Pin   7  //Define DS18S20 onewire signal pin on D7
#include <OneWire.h>
#include <DS18B20.h>
DS18B20 dd(DS18B20_Pin);  // Declare one DS18B20 object : "dd" on digital pin 7

//--------- AmeiAmei Melody 2013/4/21 ---------
#include "pitches.h"
#define NO_SOUND 0 // make the rests in music
#define LedIndicator 13 // Green Led as Indicator

//array of notes
int melody[] = {
  NO_SOUND,NOTE_E4,NOTE_E4,NOTE_E4,NOTE_D4,NOTE_C4,NOTE_B3,NOTE_A3,NOTE_D4,NOTE_D4,NOTE_D4,
  NO_SOUND,NOTE_A3,NOTE_A3,NOTE_A3,NOTE_A3,NOTE_C4,NOTE_D4,NOTE_E4,
  NO_SOUND,NOTE_E4,NOTE_E4,NOTE_E4,NOTE_D4,NOTE_C4,NOTE_B3,NOTE_A3,NOTE_D4,NOTE_D4,NOTE_D4,//今天今天你要老實講　
  NO_SOUND,NOTE_B3,NOTE_B3,NOTE_B3,NOTE_B3,NOTE_C4,NOTE_D4,NOTE_C4,//　　我是否有希望
  // --- comment to shorten the play time --------------------- 
/*  NO_SOUND,NO_SOUND,NO_SOUND,NOTE_F4,NOTE_G4,NOTE_A4,NOTE_A4,NOTE_A4,NOTE_A4,NOTE_G4,//--
  NOTE_F4,NOTE_G4,NOTE_A4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_F4,
  NOTE_E4,NOTE_G4,NOTE_G4,NOTE_C4,NOTE_D4,NOTE_E4,NOTE_G4,NOTE_F4,NOTE_E4,NOTE_F4,
  NOTE_F4,NOTE_F4,NOTE_F4,NOTE_E4,NOTE_E4,NOTE_D4,NOTE_D4,NOTE_D4,// 　看看自己的長
  NOTE_C4  // 相
*/
};

// note duration: 1 = whole note, 2 = half note, 4 = quarter note, 8 = eighth note, etc.
int noteDurations[] = {
  2,1,2,2,2,2,2,1,2,2,-2, //-2 代表延長兩個全音(兩拍)
  2,2,2,2,2,2,1,-4,  //-4 代表延長4個全音(4拍)
  2,1,2,2,2,2,2,1,2,2,-2,
  2,2,2,2,2,2,1,-4, //
/*  1,1,1,2,2,2,1,2,1,1, 
  -3,2,2,2,1,2,1,1,
  2,2,-2,2,2,1,1,1,2,2, //　樣    　但是你要想一想
  -3,2,2,1,1,2,2,1, // 　　看看自己的長
  -4
*/
};


//-------- EEPROM Library for recording motor parameters 
#include <EEPROM.h>
// Address : Motors speed and power level parameters record
//  0 : AA(1010 1010) -- Setting Flag/ "AA" means to be changed already,"FF" means no change never
//  1 : current power level -- 10,20,...100 but start from 3V(based on TT motor spec,normal 3V ~ 9V)
// --------------------------  under 3V no operation for motor,Sanyo 18650 : 3.625V ~ 4.2V/pcs  ------
// --------- Parameter Setting by App from smartphone/Tablet PC ---
int Configured_flag = 0;
byte eeprom_value;
//----------- End of EEPROM for Motor setting --------

// Car Direction Const Definition
#define TurnOff   0
#define FORWARD   1
#define BACKWARD  2
#define TurnLeft  3
#define TurnRight 4
#define LeftRotate 5
#define RightRotate 6
#define MelodySongPlay  7
#define PIDSwitchON     8     // PID function switch
#define PIDSwitchOFF    9     // PID function switch
#define Left_Right_PowerDrop 32 // drop power 64 while turn left/right
//-----------------------------------------------------------
Timer tick ;// setup one sec timer event
int PID_Event ;  // Setup PID Event to Stop/Start
//--- 超音波模組控制腳位定義 ---
#define   PIN_ECHO        A3 // The Dino 911P need more I/O port.
                            // Just use A2/A3 as Digital I/O
#define   PIN_TRIG        A2

//--- BOT Car Speed detect ----
#define RightMotor_Speed_Pin    2  // Pin 2 as Interrupt 0/INT0
#define LeftMotor_Speed_Pin     3  // Pin 3 as Interrupt 1/INT1
#define Buzzer                  8   // enable Pin 8 buzzer function
volatile byte EventFlag = B00000000 ;    // clear 8 bits boolean event flag 
//--- 馬達模組控制腳位定義 ---
#define   dir1PinA         12 // IN1
#define   dir2PinA         11 // IN2 Motor A
#define   dir1PinB         10 // IN3
#define   dir2PinB         9 // IN4 Motor B
#define   speedPinA        6 // PWM Control
#define   speedPinB        5 // PWM Control

//-- Judgement for Auto mode Car direction with UltraSound sensor
volatile int MotorMode = TurnOff ; //define current Motor operation mode
volatile int LeftMotorSpeed = 168 ;// Initially set up 50% speed
volatile int RightMotorSpeed = 168 ;
volatile int MotorPowerLevel = 50; // send to mobile device to show(10,20, ~ 100)
static int MotorDelay = 1 ; // test RTurn/LTurn time period
volatile boolean JSControl = false ; // default control by smart mobile devices
volatile boolean DistanceControlFlag = false ; // distance control by smart mobile devices
//-----
volatile boolean PIDEnableFlag = false ; // default disable PID control 
#define PID_LeftMotorLimit     230   // for PID control,drop the maximum motor power limit
#define PID_RightMotorLimit    230 
#define Normal_LeftMotorLimit  255   // for normal operation,maximum the motor power limit
#define Normal_RightMotorLimit 255 
volatile int LeftMotorLimit =  Normal_LeftMotorLimit ;     
volatile int RightMotorLimit = Normal_RightMotorLimit ;

#define MotorPowerLevel_eeprom_Addr   1    // EEPROM[1] = MotorPowerLevel record the current MotorPowerLevel
//---------- Battery status monitor --------------------------
#define BatteryDetect    A0   // Battery detect input Pin 
#define FullBatteryLevel 852  // 4.16V / 5V * 1024
#define MinBatteryLevel  748  // setup 3.65V as Min Battery Voltage to protect Lion Battery(Avoid over discharge)
#define battWarningLevel 15  // Battery warning notice threshold level
volatile int BatteryRatio = 0 ; // Battery current Level (0 ~ 100%)
//--------------- Android Bluetooth Test ------------
MeetAndroid AppsduinoBot;
//--------------------------------------------------
const int InterruptNumber0 = 0;           // Interrupt 0 在 pin 2 上,Interrupt 1 : pin 3
const int InterruptNumber1 = 1;            // INT1 for Left motor Speed Detect 
//---------------------------------------------------
void setup() 
{
  pinMode(PIN_ECHO, INPUT);
  digitalWrite(PIN_ECHO, HIGH);  // enable pull up resister 
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(RightMotor_Speed_Pin,INPUT);
  digitalWrite(RightMotor_Speed_Pin, HIGH);  // enable pull up resister 
  pinMode(LeftMotor_Speed_Pin,INPUT);
  digitalWrite(LeftMotor_Speed_Pin, HIGH);  // enable pull up resister 
  //--------------------------------------
  pinMode(dir1PinA, OUTPUT);
  pinMode(dir2PinA, OUTPUT);
  pinMode(speedPinA, OUTPUT);
  pinMode(dir1PinB, OUTPUT);
  pinMode(dir2PinB, OUTPUT);
  pinMode(speedPinB, OUTPUT);
  pinMode(LedIndicator, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  //---- Clear Event Flag ----
  
  EventFlag = 0 ; // Clear all Event Flag
  
  // Read Motor seeting from the EEPROM,If addr(0) = "AA" then read the presetting value,otherwise just skip
  if(EEPROM.read(0) == 0xAA) { // Speed setting = Upper_Limit(0.4 + 0.6 * PowerLevel)/100 ; Motor operation is around 40% * Voltage ~ 3.0V
    MotorPowerLevel = EEPROM.read(MotorPowerLevel_eeprom_Addr) ;// restore motor power level
    LeftMotorSpeed = LeftMotorLimit * (35 + 65 * MotorPowerLevel/100)/100 ; // Restore Motor Speed setting
    RightMotorSpeed = RightMotorLimit * (35 + 65 * MotorPowerLevel/100)/100 ; // Restore Motor Speed setting
  }  

  // Configure your bluetooth module to this baud rate : 57600 bps
  // not all baud rates are working well, i.e. ATMEGA168 works best with 57600
  Serial.begin(57600); 
  while(!Serial) ; // wait for serial port is ready
  // Read Battery current level
  tick.every(200, BatteryDetectHandler);// check battery status once 200ms 
  tick.every(1000, OneSecTimerHandler);// read temperature/humidity once per second 
  if(DistanceDetect() > 0)  // 03/2015 add to check if ultrasound is exist or not ? if yes then start distance monitor
    tick.every(50, Timer50msHandler);//setup 50ms timer to check out the event flag to service

  PID_Event=tick.every(20, PD_Control);// setup PID control Timer
  tick.stop(PID_Event) ; // Stop PID control first 
  // register callback functions, which will be called when an associated event occurs.
  // - the first parameter is the name of your function (see below)
  // - match the second parameter ('A', 'B', 'a', etc...) with the flag on your Android application
  // AppsduinoBot.registerFunction(testEvent, 'A');  
  AppsduinoBot.registerFunction(BTCommandHandler, 'c');     // Setup the BT Command Control function from Smart devices
  AppsduinoBot.registerFunction(SetMotorPower, 'p');   // Setup the Motor Power Control function from Smart devices
  AppsduinoBot.registerFunction(JoyStickControl, 'j'); // setup the Joystick Control function 
  AppsduinoBot.registerFunction(DistanceControl, 'd'); // setup the Joystick Control function 
//---------------------------------------
// 把外部中斷(interrupt 1)連接到 RightMotorSpeed_ISR() 函式
// CHANGE 是指當 pin 狀態改變時就觸發中斷，不管是從 HIGH 到 LOW 或從 LOW 到 HIGH
// FALLING : interrupt while the signal from HIGH to LOW
attachInterrupt(InterruptNumber0, RightMotorSpeed_ISR, CHANGE); // Count the speed of Right Motor
attachInterrupt(InterruptNumber1, LeftMotorSpeed_ISR, CHANGE); // Count the speed of Left Motor
// if analog input pin 0 is unconnected, random analog
// noise will cause the call to randomSeed() to generate
// different seed numbers each time the sketch runs.
// randomSeed() will then shuffle the random function.
randomSeed(analogRead(4));// generate a random seed due to Pin 2 is unconnected,use for BOT to change moving direction due to object in frent of 5cm
//----------------------------------
}

//--------------- Main Program ------------------------
void loop()
{
  tick.update(); // check timer event
  
  AppsduinoBot.receive(); // you need to keep this in your loop() to receive events    
 }
 
//----------------------------------------------------
// input : Left Motor Speed(0~255)/Right Motor Speed(0~255)/Direction(STOP,FOWARD,...)
//----------------------------------------------------
void DCMotor(int LMspeed,int RMspeed,int dir)
{
   tick.stop(PID_Event) ; // Stop PID control first 
   switch(dir) {
     case TurnOff : // turn off motors
     analogWrite(speedPinA, 0);
     analogWrite(speedPinB, 0);
     MotorMode = TurnOff ;
     break ;

    // both motors forward 
     case FORWARD : // Forward
     digitalWrite(dir1PinA, HIGH);
     digitalWrite(dir2PinA, LOW); 
     digitalWrite(dir1PinB, HIGH);
     digitalWrite(dir2PinB, LOW); 
     analogWrite(speedPinA, RMspeed);
     analogWrite(speedPinB, LMspeed);  
     MotorMode = FORWARD ;
     if(!JSControl)     // if Smart devices control then enable PID
       StartPDControl();// Start PID control Timer
     break;
     // both motors Reverse
     case BACKWARD : // reverse
     digitalWrite(dir1PinA, LOW);
     digitalWrite(dir2PinA, HIGH); 
     digitalWrite(dir1PinB, LOW);
     digitalWrite(dir2PinB, HIGH); 
     analogWrite(speedPinA, RMspeed);
     analogWrite(speedPinB, LMspeed);  
     MotorMode = BACKWARD ;
     if(!JSControl)     // if Smart devices control then enable PID
       StartPDControl();// Start PID control Timer
     break;   
     case LeftRotate : // LeftRotate
     digitalWrite(dir1PinA, HIGH);
     digitalWrite(dir2PinA, LOW); 
     digitalWrite(dir1PinB, LOW);
     digitalWrite(dir2PinB, HIGH); 
     analogWrite(speedPinA, RMspeed);
     analogWrite(speedPinB, LMspeed);  
     MotorMode = LeftRotate ; 
     break;
     // both motors reverse
     case RightRotate : // RightRotate
     digitalWrite(dir1PinA, LOW);
     digitalWrite(dir2PinA, HIGH); 
     digitalWrite(dir1PinB, HIGH);
     digitalWrite(dir2PinB, LOW); 
     analogWrite(speedPinA, RMspeed);
     analogWrite(speedPinB, LMspeed);  
     MotorMode = RightRotate ; 
     break;       
     //---- Turn Right(Slow right wheel) -----------  
     case TurnRight : // turn right
     digitalWrite(dir1PinA, HIGH);
     digitalWrite(dir2PinA, LOW); 
     digitalWrite(dir1PinB, HIGH);
     digitalWrite(dir2PinB, LOW); 
     if((RMspeed-Left_Right_PowerDrop) > 0)
       analogWrite(speedPinA, RMspeed-Left_Right_PowerDrop);
     else 
       analogWrite(speedPinA, 0);
     analogWrite(speedPinB, LMspeed);  
     MotorMode = TurnRight ;
     break;       
     //---- Turn Left(Slow left wheel) -----------  
     case TurnLeft : // turn right
     digitalWrite(dir1PinA, HIGH);
     digitalWrite(dir2PinA, LOW); 
     digitalWrite(dir1PinB, HIGH);
     digitalWrite(dir2PinB, LOW); 
     analogWrite(speedPinA, RMspeed);
     if((LMspeed-Left_Right_PowerDrop) > 0)
       analogWrite(speedPinB, LMspeed-Left_Right_PowerDrop);
     else 
       analogWrite(speedPinB, 0);
     MotorMode = TurnLeft ; 
     break;       
     //------ Just Play Song Melody,only for Demo -------
     case MelodySongPlay : // RightRotate
     MelodyPlay() ; // wait for melody play finished
     break;            
     //---- Toggle PID Control -----------  
     case PIDSwitchON : // PID 
       PIDEnableFlag = true ; // toggle the PID function
       LeftMotorLimit = PID_LeftMotorLimit ;     
       RightMotorLimit = PID_RightMotorLimit ;
       LeftMotorSpeed = LeftMotorLimit * (35 + 65 * MotorPowerLevel/100)/100 ; // Restore Motor Speed setting
       RightMotorSpeed = RightMotorLimit * (35 + 65 * MotorPowerLevel/100)/100 ; // Restore Motor Speed setting
       break;            
     case PIDSwitchOFF : // PID 
       PIDEnableFlag = false ; // toggle the PID function
       LeftMotorLimit =  Normal_LeftMotorLimit ;     
       RightMotorLimit = Normal_RightMotorLimit ;
       LeftMotorSpeed = LeftMotorLimit * (35 + 65 * MotorPowerLevel/100)/100 ; // Restore Motor Speed setting
       RightMotorSpeed = RightMotorLimit * (35 + 65 * MotorPowerLevel/100)/100 ; // Restore Motor Speed setting
       break;            
   }
}

// distance detect
int DistanceDetect()
{
digitalWrite(PIN_TRIG, LOW); // 保持超音波控制介面低電位2us
delayMicroseconds(2);

digitalWrite(PIN_TRIG, HIGH); // 保持超音波控制介面高電位10us
delayMicroseconds(11);
digitalWrite(PIN_TRIG, LOW);    // 超音波控制介面轉低電位以觸發測距過程

// 距離測試公式為 : 脈衝長度 * 音速 / 2;
const float SONIC_SPEED = 0.0340; // 音速在大氣中傳播速度為340米/秒
float duration = pulseIn(PIN_ECHO, HIGH); // 讀出脈衝時間
return duration * SONIC_SPEED / 2;
}

//--------------------- BT Command Handler ---------------------------------
// Flag : 'c' - means direction Ctrl cmd transmit from smart devices
// Format : start_Flag('c') Cmd(0/1/2/3/..) endofcmd(0x13)
//--------------------------------------------------------------------------
void BTCommandHandler(byte flag, byte numOfValues)
{
      
      JSControl = false ; // disable Joy Stick control
      DistanceControlFlag = false ; //disable distance control
  int randomvalue = AppsduinoBot.getInt();
      noInterrupts();// Critical Section,so disable Interrupt
      EventFlag = EventFlag & B11110000 ; // Clear all actions/service in Timer100msHandler() to avoid error actions
      interrupts();// Enable Interrupt
      DCMotor(LeftMotorSpeed,RightMotorSpeed,randomvalue);
}

//--------------------- Motor Power Control Command Handler ----------------
// Flag : 'p' - means Motor Power Control cmd transmit from smart devices
// Format : start_Flag('p') Motor Power value(10/20/30/..) endofcmd(0x13)
// Convert the Power Level to 0 ~ 255      
//--------------------------------------------------------------------------
void SetMotorPower(byte flag, byte numOfValues)
{

    JSControl = false ; // disable Joy Stick control
    MotorPowerLevel = AppsduinoBot.getInt();
    if(MotorPowerLevel > 0 && MotorPowerLevel <= 100) {
       LeftMotorSpeed  = LeftMotorLimit * (35 + 65 * MotorPowerLevel/100)/100 ; // Restore Motor Speed setting
       RightMotorSpeed = RightMotorLimit * (35 + 65 * MotorPowerLevel/100)/100 ; // Restore Motor Speed setting
       //------------ Store the update setting value to EEPROM ---------
       EEPROM.write(MotorPowerLevel_eeprom_Addr, MotorPowerLevel);// Keep the MotorPowerLevel to EEPROM
       // Read Motor seeting from the EEPROM,If addr(0) = "AA" then read the presetting value,otherwise just skip
      if(EEPROM.read(0) != 0xAA) 
         EEPROM.write(0,0xAA) ; // If the 1st Time then set up flag
    }
}
//--------------------- Joystick Control Command Handler ----------------
// Flag : 'j' - means direction Ctrl cmd transmit from Remote BT Joystick handler
// Format : 'j' Signed_integer,0x13 : Dir(+/-)-LeftSpeed(High Byte :0 ~~ 127)-RightSpeed(Low Byte : 0 ~ 127)
//--------------------------------------------------------------------------
void JoyStickControl(byte flag, byte numOfValues)
{
    int JoySpeed,Direction,JS_LeftMotorSpeed,JS_RightMotorSpeed ;
    JSControl = true ; // enable Joy Stick control
    JoySpeed = AppsduinoBot.getInt();
    if(JoySpeed > 0)
       Direction = FORWARD ; // Move Forward
    else if(JoySpeed < 0) {  
       Direction = BACKWARD ; // Move Backward
       JoySpeed = - JoySpeed ; // make it to positive integer
    }   
    else
       Direction = TurnOff ; // Stop Motor

    JS_LeftMotorSpeed = JoySpeed / 256 ;// get the high byte left motor speed
    JS_LeftMotorSpeed = map(JS_LeftMotorSpeed,0,127,50,255) ; // convert 0 ~ 127 to 60 ~ 255 motor speed
    JS_RightMotorSpeed = JoySpeed & 0x00ff ; // get the low byte data
    JS_RightMotorSpeed = map(JS_RightMotorSpeed,0,127,50,255) ; // convert 0 ~ 127 to 60 ~ 255 motor speed
    DCMotor(JS_LeftMotorSpeed,JS_RightMotorSpeed,Direction);
}  
//--------------------- Distance Control Command Handler ----------------
// Flag : 'd' - means distance Ctrl cmd transmit from Remote BT with moving distance(cm basis)
// Format : 1/2/3/4;distance(cm)
//--------------------------------------------------------------------------
volatile float DistanceLimit = 0; //use for moving distance target for this run(cm)
volatile float DistanceofTrip = 0; //measure total range for this run(cm)
#define HalfPowerMotor  128        // use half power to move
void DistanceControl(byte flag, byte numOfValues)
{
    int values[2] ;
    AppsduinoBot.getIntValues(values) ;
    DistanceControlFlag = true; // enable Distance Control
    DistanceLimit = DistanceofTrip + (float) values[1] ; //setting moving distance target(cm) 
    DCMotor(140,140,values[0]);
}  
// ------------------------------------------------------------------------------
//  Check the Battery Status interval ,Beep warning if battery Low is detected
//------------------------------------------------------------------------------
#define NUM_SAMPLES      10          // define the taken samples count 
volatile int sum = 0;                // sum of samples taken
unsigned char sample_count = 0;      // current sample number

void BatteryDetectHandler() //-- update per sec -- 
{
//------------- Read Battery voltage level from  ------
          sum += analogRead(BatteryDetect) ; // Full battery is around 4.2V for one 18650 Battery
          sample_count++ ; // check how many samples is measured ?
          if(sample_count >= NUM_SAMPLES) {
            int Battery_AvgLevel = sum / NUM_SAMPLES ; //average battery voltage level
            sum = 0 ; // reset sum
            sample_count = 0 ; // reset the taken sample counter
            if(Battery_AvgLevel < 500) // if voltage < 2.5V,it could be power from USB,so just skip
              return ;
            BatteryRatio = map(Battery_AvgLevel,MinBatteryLevel,FullBatteryLevel,0,100) ; // map to 0 ~ 100 %  revised 4/12/2013
            if( BatteryRatio >100 )  // If Battery is more than 100% keep to 100%
               BatteryRatio = 100 ; //         //------------ measure car speed and distance for this run --------
            if( BatteryRatio < battWarningLevel)  // If Battery is less than 15% then warning a tone
               tone(Buzzer,262,20) ; // Enable Battery Low warning tone(Freq : 262 Hz,Do tone) for 20ms          
          }  
} 
/*------- Timer event : 1 sec interval event ------------------------------------------------
          send current Temperature to Android device every second ------
          Created 13 December 2012 by Tony
          Data Format : Temp space Humidity "z" : "z" is char delimiter
*/
volatile int Right_PulseCount = 0; // 20 pulses per cycle for wheel
volatile int Left_PulseCount = 0; // 20 pulses per cycle for wheel
volatile int WheelCount = 0; // update CyclePerMin per 5 sec
volatile float CyclePerMin ; // 
volatile unsigned long CycleCountOfWheel = 0; // 131.946891mm/cycle for 42mm(2r) wheel,the length is : 2 x R x pi
                                              // 204.2035225mm/cycle for 65mm(2r) wheel,the length is : 2 x R x pi
// volatile float DistanceofTrip = 0; //measure total range for this run(cm)
volatile unsigned long CycleCountPerSec = 0; // record previous cycle
volatile int Pulse1SecCount = 0; // record previous position
volatile float DistancePrevious = 0;
//------- for big car use ----
const float DistancePerPulse = 1.02101761242/2 ;// unit : cm  1.02101761242cm/cycle with 2 CHANGE states
#define PulsePerCycle 40            // 20 pulses per cycle for Big Car but with 40 CHANGE states
const int BatteryVoltageRange = FullBatteryLevel - MinBatteryLevel ; //full range : 3.75V ~ 4.16V,so 854 - 768 = 84
volatile int USRange = 0 ; // UltraSound Range recore 

void OneSecTimerHandler() //-- update per sec -- 
{
        int CycleCount,P_Count ;
        float SpeedCMMin;

        P_Count = Right_PulseCount - Pulse1SecCount ;
        if(P_Count < 0)
           P_Count += PulsePerCycle ; // increase pulse counter
        WheelCount++; // increase Cycle count,update per 5 sec
        if(WheelCount == 2) {
           WheelCount = 0;
           CycleCount = CycleCountOfWheel - CycleCountPerSec;
           CyclePerMin =  (CycleCount + P_Count/PulsePerCycle) * 30 ;
           CycleCountPerSec = CycleCountOfWheel ;
        }   
        SpeedCMMin =   (DistanceofTrip - DistancePrevious) * 60 ;
        DistancePrevious = DistanceofTrip ;
        Pulse1SecCount = Right_PulseCount ;
//-------- Add DS18B20 Temp reading and transmi to Smart devices to show it -----
        Serial.println(dd.getTemperature(),1);   // Read BS18B20 temperature data and Transmit it to smart deivces
        Serial.println(BatteryRatio); // Transmit Battery Level to smart deivces
        Serial.println(CyclePerMin,0);// 
        Serial.println(SpeedCMMin,1);// 
        Serial.println(DistanceofTrip,1);
        Serial.println(MotorPowerLevel) ;
        if(USRange == 0)
           Serial.println("X") ; // No connect then send "X" char
        else
           Serial.println(USRange) ; // Display current range from ultrasound detector
        Serial.println("z");// sent out delimiter               
}
//------------------------------------------------------------
//--------- PID Control ---------------
volatile int EncoderRight_Count=0,EncoderLeft_Count=0;
const int P = 5; 
const int D = 4;
const int power = 25;
int center=0;
int last_proportional=0;
//----------- PID Control Start and Reset the encoder counter value ----------
void StartPDControl()
{
    if(PIDEnableFlag) {
      noInterrupts();// Critical Section,so disable Interrupt
      EncoderRight_Count = 0 ; // Reset the encoder counter value
      EncoderLeft_Count = 0 ; 
      PID_Event=tick.every(5, PD_Control);// Start PID control Timer  
      interrupts(); // enable Interrupt
    }  
}

//----------- PID Compute ---------------
void PD_Control()
{
  center=EncoderRight_Count-EncoderLeft_Count;

  int proportional = center;
  int derivative = proportional - last_proportional;
      last_proportional = proportional;
  int power_difference = proportional*P  +derivative*D;

  if(power_difference > power)
     power_difference = power;
  
  if(power_difference < -power)
     power_difference = -power;
  
  analogWrite(speedPinA, RightMotorSpeed-power_difference);
  analogWrite(speedPinB, RightMotorSpeed+power_difference);
}

//------------ Left/Right Motor Speed Measure ISR ------------
// INT 0 : Right Motor
// INT 1 : Left Motor
// Only calculate the Distance from Right Motor

void RightMotorSpeed_ISR()
{
    EncoderRight_Count++ ; // Increase Encoder Pulse count 
    Right_PulseCount++ ;
    DistanceofTrip += DistancePerPulse ; // increase one pulse range(1/12 or 1/20 wheel)
    if(DistanceControlFlag == true && DistanceofTrip >= DistanceLimit) {
      DistanceControlFlag = false ;
      DCMotor(HalfPowerMotor,HalfPowerMotor,TurnOff);
    }
    if(Right_PulseCount == PulsePerCycle) {
       Right_PulseCount = 0; // reset
       CycleCountOfWheel++ ;
    }     
 }  
 
void LeftMotorSpeed_ISR()
{
    EncoderLeft_Count++ ; // Increase Encoder Pulse count 
    Left_PulseCount++ ;
    if(Left_PulseCount == PulsePerCycle) {
       Left_PulseCount = 0; // reset
//       CycleCountOfWheel++ ;
    }     
 }  

/*-- Have object on right corner ---
  1. stop immediately
  2. store current moving mode
  3. backward about 5/10 cm or 100ms(moving distance based on power level)
  4. setup the moving flag(need to take care if user take action while this period will clear all flag/action) 
     then check by timer(50ms) ISR
  5. determine right/left turn 10/5cm
  6. back to original moving operation  
*/ 

volatile int BackupMotorMode ; //store current motor motion mode
volatile float BackupDistanceofTrip ; //store current total range for this run(cm)
volatile int BackwardTimer50ms     ; //While detect drop or distance less than some threshold then make car to Backward for some time period 
//volatile byte EventFlag = B00000000 ;    // clear 8 bits boolean event flag 
#define RightTouchEvent  B00000001   // Touch event flag
#define LeftTouchEvent   B00000010   // Touch event flag
#define UltraSoundEvent  B00000100   // UltraSound detect < 5cm then backward first,random leftrotate/rightrotate 
#define DropDangerEvent  B00001000   // Infrared detect drop dangerous event flag
#define MoveDistanceOnceTouch   7    // moving back 5cm then right/left turn 5cm once touch then keep original operation 
#define BackwardTimePeriod     10    // moving back for 0.5 sec then right/left turn 1 sec once touch then keep original operation
#define LeftRightTimePeriod    5    // moving back for 0.5 sec then right/left turn 1 sec once touch then keep original operation
//#define HalfPowerMotor  128        // use half power to move
#define UltraSoundThreshold 12  // define UltraSound Threshold < ? cm then action
#define InfraredThreshold   900  // define the threshold for Infrared,over this means no signal received then could drop danger 
 
//------------- system timer(50ms) to check events for service -------
/*
While event occurs,then Backward for BackwardTimePeriod(1.5Sec) then turn Left/Right about LeftRightTimePeriod(~1 sec)
*/

void Timer50msHandler()
{ 
  // Check BOT if touch the object on the right corner
  // sequence is very important,only process one event to finish then new one

  if(EventFlag & UltraSoundEvent ){  //---------- check the distance with UltraSound sensor ---- 
    if(!(--BackwardTimer50ms)) {
     BackwardTimer50ms = LeftRightTimePeriod ; //Start left or right turn timer
     if(MotorMode == RightRotate || MotorMode == LeftRotate) { // means finish one cycle process
        EventFlag ^= UltraSoundEvent ; //clear ultrasound Flag 
        DCMotor(LeftMotorSpeed,RightMotorSpeed,BackupMotorMode); // Restore original operation 
     } else // means Backward for specified distance then make it LeftRotate/RightRotate      
        DCMotor(HalfPowerMotor,HalfPowerMotor,random(LeftRotate,RightRotate+1)); // LeftRotate/RightRotate randomly 
   }   
 }
 else  {
    USRange = DistanceDetect() ; // Get the ultrasound distance
    if(USRange != 0 && USRange <= UltraSoundThreshold ){ // Check the distance of obstacle < 5cm then start some actions 
     BackupMotorMode = MotorMode ; // backup current motor mode
     BackwardTimer50ms = BackwardTimePeriod ; // start timer to count
     EventFlag |= UltraSoundEvent ; //set TouchFlag = True 
     DCMotor(HalfPowerMotor,HalfPowerMotor,BACKWARD); //Stop Motor     
     } 
 }  
}

//--------- AmeiAmei Melody Player ----------------------------
// Play the melody based on the Notes in melody and NotesDurations array

int pace = 350; // change pace of music("speedy")

void MelodyPlay() {
  int melodysize = sizeof(melody)/2 ;// sizeof(var) return the byte count for the var
  int duration ;
  
  for (int Note = 0; Note < melodysize; Note++) {//counter of Notes (54 limit the array)
    duration = pace/noteDurations[Note];//Adjust duration with the pace of music
    if(duration < 0)
       duration = pace * abs(noteDurations[Note]) ; // it means long note
 //   Serial.println(duration) ;   
    tone(Buzzer,melody[Note],duration); //Play note
    analogWrite(LedIndicator,melody[Note]/2) ;

// to distinguish the notes, set a minimum time between them.
    delay(duration*1.2);
  }
  noTone(Buzzer) ;
  analogWrite(LedIndicator,0) ; //turn off Led
}

