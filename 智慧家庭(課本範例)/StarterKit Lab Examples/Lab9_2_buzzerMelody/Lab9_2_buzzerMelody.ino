//--------- AmeiAmei Melody 2013/4/21 ---------
#include "pitches.h"
#define NO_SOUND 0 // make the rests in music
#define LedIndicator 10 // Green Led as Indicator

//array of notes
int melody[] = {
  NO_SOUND,NOTE_E4,NOTE_E4,NOTE_E4,NOTE_D4,NOTE_C4,NOTE_B3,NOTE_A3,NOTE_D4,NOTE_D4,NOTE_D4,
  NO_SOUND,NOTE_A3,NOTE_A3,NOTE_A3,NOTE_A3,NOTE_C4,NOTE_D4,NOTE_E4,
  NO_SOUND,NOTE_E4,NOTE_E4,NOTE_E4,NOTE_D4,NOTE_C4,NOTE_B3,NOTE_A3,NOTE_D4,NOTE_D4,NOTE_D4,//今天今天你要老實講　
  NO_SOUND,NOTE_B3,NOTE_B3,NOTE_B3,NOTE_B3,NOTE_C4,NOTE_D4,NOTE_C4,//　　我是否有希望
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

#define Buzzer                  8   // enable Pin 8 buzzer function
//---------------------------------------------------
void setup() 
{
  pinMode(Buzzer, OUTPUT);
  pinMode(LedIndicator,OUTPUT) ;
  MelodyPlay() ; // wait for melody play finished

 }

//--------------- Main Program ------------------------
void loop()
{
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

