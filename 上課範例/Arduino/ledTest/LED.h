#ifndef _LED_
#define _LED_

 #include <arduino.h>

 
class LED{
  private:
  byte _pin = 0;
  unsigned long _startTime;
  boolean _state = false;
  

  public:
  
  LED(byte pinNum); 
  //基本功能
  void on();
  void off();

  //一閃一閃的功能
  void blink(long interval);

  //一閃一閃，使用別人的功能
  void autoBlink();
  
};
#endif
