#ifndef _LED_
#define _LED_

 #include <arduino.h>
class LED{
  private:
  byte pin = 0;

  public:
  LED(byte pinNum);
  void on();
  void off();
  
};
#endif
