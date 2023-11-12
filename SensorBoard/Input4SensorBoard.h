#ifndef INPUT4SENSORBOARD_H
#define INPUT4SENSORBOARD_H
#include "Arduino.h"

class Input4SensorBoard{
  public:
    Input4SensorBoard(int pin);
    int status();
  private:
    int _pin;
};

static Input4SensorBoard InputSensorBoard(2);
#endif
