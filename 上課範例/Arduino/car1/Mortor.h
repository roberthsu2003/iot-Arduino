#ifndef __MORTOR__
#define __MORTOR__

class Mortor{
  private:
    int _modePin1;
    int _modePin2;
    int _speedPin;
    int _speed = 0;
    
  public:
    Mortor(int modePin1, int modePin2, int speedPin);
};

#endif
