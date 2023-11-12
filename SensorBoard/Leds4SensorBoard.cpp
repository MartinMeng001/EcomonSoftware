#include "Arduino.h"
#include "Leds4SensorBoard.h"

LedSensorBoard::LedSensorBoard(int pin){
  pinMode(pin, OUTPUT);
  _pin=pin;
}
void LedSensorBoard::on(){
  digitalWrite(_pin, LOW);
}
void LedSensorBoard::off(){
  digitalWrite(_pin, HIGH);
}
void LedSensorBoard::flash(int msecs_on, int msecs_off){
  on();
  delay(msecs_on);
  off();
  delay(msecs_off);
}
