#include "Arduino.h"
#include "SWReset4SensorBoard.h"

SWReset4SensorBoard::SWReset4SensorBoard(int pin){
  pinMode(pin, INPUT);
  _pin=pin;
}
int SWReset4SensorBoard::state(){
  return digitalRead(_pin);
}
