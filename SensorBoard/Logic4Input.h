#ifndef __LOGIC4INPUTSENSORBOARD_H__
#define __LOGIC4INPUTSENSORBOARD_H__
#include <arduino.h>

class Logic4Input{
  public:
  Logic4Input();
  int setStatus(int status);
  protected:
  int checkEvent();
  private:
  int _status;
  uint32_t time4status;
};
#endif
