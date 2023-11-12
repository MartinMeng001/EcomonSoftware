#include "Arduino.h"
#include "HwAddr4SensorBoard.h"

HwAddr4SensorBoard::HwAddr4SensorBoard(int pinA, int pinB, int pinC, int pinD){
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);
  pinMode(pinC, INPUT);
  pinMode(pinD, INPUT);
  _pinA=pinA;_pinB=pinB;_pinC=pinC;_pinD=pinD;
}
int HwAddr4SensorBoard::addr(){
  int addr=0;
  if(digitalRead(_pinA)==HIGH) addr|=0x01;
  if(digitalRead(_pinB)==HIGH) addr|=0x02;
  if(digitalRead(_pinC)==HIGH) addr|=0x04;
  if(digitalRead(_pinD)==HIGH) addr|=0x08;
  return addr;
}
