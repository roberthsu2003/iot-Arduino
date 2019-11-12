#include "Ultrasonic.h"
#include "Timer.h"
#define MOTORRIGHT1 12
#define MOTORRIGHT2 11
#define MOTORLEFT1 10
#define MOTORLEFT2 9
#define RIGHTPOWER 5
#define LEFTPOWER 6

typedef enum Direction {
  FRONT,
  LEFT,
  RIGHT,
  BACK
} Direction;

Ultrasonic front(3, 4);
Ultrasonic right(A1, A2);
Ultrasonic left(A3, A4);
Timer customTime;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  customTime.every(100,loopAgain);
}

void loop() {
  customTime.update();
}

void loopAgain(){
  Direction direction = ultrasonicSensor();
  switch (direction){
    case FRONT:
      Serial.println("Front");
      goHead();
      break;
    case LEFT:
      Serial.println("left");
      goLeft();
      break;
    case RIGHT:
      goRight();
      Serial.println("right");
      break;
    case BACK:
      goBack();
      Serial.println("back");
      break;
      
  }
}

Direction ultrasonicSensor() {
  // put your main code here, to run repeatedly:
  long frontMillsecon = front.timing();
  float frontDistance = front.convert(frontMillsecon, Ultrasonic::CM);
  //Serial.print("Front-->");
  //Serial.println(frontDistance);
  //left
  long leftMillsecon = left.timing();
  float leftDistance = front.convert(leftMillsecon, Ultrasonic::CM);
  //Serial.print("Left-->");
  //Serial.println(leftDistance);

  //right
  long rightMillsecon = right.timing();
  float rightDistance = right.convert(rightMillsecon, Ultrasonic::CM);
  //Serial.print("Right-->");
  //Serial.println(rightDistance);

  
  if (frontDistance > 50){
    return FRONT;
  }else if (leftDistance > 50){
    return LEFT;
  }else if(rightDistance > 50){
    return RIGHT;
  }else{
    return BACK;
  }
  
}

void goHead(){
  digitalWrite(MOTORRIGHT1,HIGH);
  digitalWrite(MOTORRIGHT2,LOW);
  digitalWrite(MOTORLEFT1,HIGH);
  digitalWrite(MOTORLEFT2,LOW);
  analogWrite(RIGHTPOWER,100);
  analogWrite(LEFTPOWER,100);
}

void goLeft(){
  digitalWrite(MOTORRIGHT1,HIGH);
  digitalWrite(MOTORRIGHT2,LOW);
  digitalWrite(MOTORLEFT1,HIGH);
  digitalWrite(MOTORLEFT2,LOW);
  analogWrite(RIGHTPOWER,130);
  analogWrite(LEFTPOWER,100);
}

void goRight(){
  digitalWrite(MOTORRIGHT1,HIGH);
  digitalWrite(MOTORRIGHT2,LOW);
  digitalWrite(MOTORLEFT1,HIGH);
  digitalWrite(MOTORLEFT2,LOW);
  analogWrite(RIGHTPOWER,100);
  analogWrite(LEFTPOWER,130);
}
void goBack(){
  digitalWrite(MOTORRIGHT1,LOW);
  digitalWrite(MOTORRIGHT2,HIGH);
  digitalWrite(MOTORLEFT1,LOW);
  digitalWrite(MOTORLEFT2,HIGH);
  analogWrite(RIGHTPOWER,100);
  analogWrite(LEFTPOWER,100);
}
