#include "Arduino.h"
#include "Input4SensorBoard.h"

Input4SensorBoard::Input4SensorBoard(int pin){
  pinMode(pin, INPUT);
  _pin=pin;
}
int Input4SensorBoard::status(){
  int status=0;
  if(digitalRead(_pin)==HIGH) status|=0x01;
  return status;
}
