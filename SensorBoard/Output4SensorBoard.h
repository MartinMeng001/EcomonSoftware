#ifndef OUTPUT4SENSORBOARD_H
#define OUTPUT4SENSORBOARD_H
#include "Arduino.h"

class Output4SensorBoard{
  public:
    Output4SensorBoard(int pin);
    void on();
    void off();
    void flash(int msecs_on, int msecs_off);
  private:
    int _pin;
};

static Output4SensorBoard Output4SensorBoard(3);
#endif
