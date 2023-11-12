#ifndef LEDSSENSORBOARD_H
#define LEDSSENSORBOARD_H
#include "Arduino.h"
#include "HardwareDef.h"
class LedSensorBoard{
  public:
    LedSensorBoard(int pin);
    void on();
    void off();
    void flash(int msecs_on, int msecs_off);
  private:
    int _pin;
};
static LedSensorBoard led(PD6_LED);
#endif
