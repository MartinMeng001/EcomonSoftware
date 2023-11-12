#include "Arduino.h"
#include "RS485SensorBoard.h"

RS485SensorBoard::RS485SensorBoard(int pin, uint32_t baudrate){
  //Serial.begin(baudrate);
  pinMode(pin, OUTPUT);
  _pin=pin;
  _baudrate=baudrate;
  //enableRead();
  //enableWrite();
}
void RS485SensorBoard::begin(){
  Serial.begin(_baudrate);
  //enableWrite();
  enableRead();
}
int RS485SensorBoard::read(char* buff, int maxsize, int timeout){
  return digitalRead(_pin);
}
int RS485SensorBoard::write(char* buff, int maxsize){
  enableWrite();
  enableRead();
}
void RS485SensorBoard::enableWrite(){
  digitalWrite(_pin, HIGH);
}
void RS485SensorBoard::enableRead(){
  digitalWrite(_pin, LOW);
}
