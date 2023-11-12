#ifndef SWRESETSENSORBOARD_H
#define SWRESETSENSORBOARD_H
#include "Arduino.h"

class SWReset4SensorBoard{
  public:
    SWReset4SensorBoard(int pin);
    int state();
  private:
    int _pin;
};

#endif
