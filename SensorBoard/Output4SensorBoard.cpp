#include "Arduino.h"
#include "Output4SensorBoard.h"

Output4SensorBoard::Output4SensorBoard(int pin){
  pinMode(pin, OUTPUT);
  _pin=pin;
}
void Output4SensorBoard::on(){
  digitalWrite(_pin, HIGH);
}
void Output4SensorBoard::off(){
  digitalWrite(_pin, LOW);
}
void Output4SensorBoard::flash(int msecs_on, int msecs_off){
  on();
  delay(msecs_on);
  off();
  delay(msecs_off);
}
