#include "CalcMethod.h"

CalcMehtod::CalcMehtod(int gain, float burdenresistor, long ratio){
  Gain = gain;
  BurdenResistor = burdenresistor;
  Ratio = ratio;
}

float CalcMehtod::getResult(long value){
  return formula(value);
}

float CalcMehtod::formula(long value){
  float volmax = getMaxReferenceVoltageByGain(Gain);
  long maxADValue = getMaxADValue();
  float burden = getBurdenResistor();
  long ratio = getRatio();
  if(maxADValue==0) return 0;
  if(burden==0) return 0;
  return volmax * value * ratio / (maxADValue * burden);
}

float CalcMehtod::getMaxReferenceVoltageByGain(int gain){
  float ret = 0;
  switch(gain){
    case 2: ret =125.0; break;
    case 4: ret =62.5; break;
    case 8: ret = 31.25; break;
    case 16: ret = 15.625; break;
    case 22: ret = 11.35; break;
    default: ret = 250.0; break;
  }
  return ret*0.707;
}

long CalcMehtod::getMaxADValue(){
  return 9032007;
}

float CalcMehtod::getBurdenResistor(){
  return BurdenResistor;
}

long CalcMehtod::getRatio(){
  return Ratio;
}
