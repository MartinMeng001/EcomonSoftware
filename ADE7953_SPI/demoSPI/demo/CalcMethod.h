#ifndef CALCMETHOD_h
#define CALCMETHOD_h

class CalcMehtod{
public:  
  CalcMehtod(int gain, float burdenresistor, long ratio);
  float getResult(long value);
protected:
  float formula(long value);
  float getMaxReferenceVoltageByGain(int gain);
  long getMaxADValue();
  float getBurdenResistor();
  long getRatio();
private:
  int Gain;
  float BurdenResistor;
  long Ratio;
};

#endif
