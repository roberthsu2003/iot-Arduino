#ifndef _LED_
#define _LED_

 #include <arduino.h>
class LED{
  private:
  byte pin = 0;

  public:
  LED(byte pinNum);
  //基本功能
  void on();
  void off();

  //一閃一閃的功能
  void blink(long interval);
  
};
#endif
