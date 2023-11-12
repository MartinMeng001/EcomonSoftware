#ifndef HWADDRSENSORBOARD_H
#define HWADDRSENSORBOARD_H
#include "Arduino.h"

class HwAddr4SensorBoard{
  public:
    HwAddr4SensorBoard(int pinA, int pinB, int pinC, int pinD);
    int addr();
  private:
    int _pinA, _pinB, _pinC, _pinD;
};

static HwAddr4SensorBoard HwAddr485(14,15,16,17);
#endif
