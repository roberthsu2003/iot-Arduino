#ifndef _Potentiometer_H_
#define _Potentiometer_H_

#include <arduino.h>


class Potentiometer{
  public:
  typedef enum {
    RAW,
    TEN,
    HUNDRED,
    TWOFIVEFIVE
  } State;
  
  private:
  int _pin;

  public:
  Potentiometer(int pinNumber);
  int pin();
  int getValue(State state);
  
};
#endif
