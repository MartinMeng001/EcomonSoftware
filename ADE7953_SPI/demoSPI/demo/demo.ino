// Basic Test Demonstration for ADE7953 to read and report values (ADE7953_TEST)
//California Plug Load Research Center - 2017


#include "Arduino.h"
#include "ADE7953.h"
#include "EEPROMData4SensorBoard.h"
#include <SPI.h>


#define PB0_POWERMETER1 8
#define PB1_POWERMETER2 9
#define PB2_POWERMETER3 10
//Define ADE7953 object with hardware parameters specified
#define local_SPI_freq 1000000  //Set SPI_Freq at 1MHz (#define, (no = or ;) helps to save memory)
#define local_SS PB2_POWERMETER3  //Set the SS pin for SPI communication as pin 10  (#define, (no = or ;) helps to save memory)
ADE7953 myADE7953(local_SS, local_SPI_freq); // Call the ADE7953 Object with hardware parameters specified, the "local" lets us use the same parameters for examples in this program as what is assigned to the ADE7953 object

// led TEST
void ledInit(){
  pinMode(5, OUTPUT);
}
void ledOn(){
  digitalWrite(5, LOW);
}
// hw addr
void hwAddrInit(){
  pinMode(14, INPUT);
  pinMode(15, INPUT);
  pinMode(16, INPUT);
}
int getHwAddr(){
  int ret=0;
  if(digitalRead(14)==HIGH)ret|=0x01;
  if(digitalRead(15)==HIGH)ret|=0x02;
  if(digitalRead(16)==HIGH)ret|=0x04;
  return ret;
}
// pulse input
void inputInit(){
  pinMode(2, INPUT);
  pinMode(3, INPUT);
}
int getInput(){
  int ret = 0;
  if(digitalRead(2)==HIGH) ret|=0x01;
  if(digitalRead(3)==HIGH) ret|=0x02;
  return ret;
}

void setup() {
  uint8_t testdata[7] = {"Hello"};
  hwAddrInit();
  inputInit();
  ledInit();
  ledOn();
  eepromdata.begin();
  eepromdata.write(0, testdata, 6);
  Serial.begin(115200);
  delay(200);
  SPI.begin();
  delay(200);
  myADE7953.initialize();   //The ADE7953 must be initialized once in setup.
  Serial.println("Demo Init (hex): ");
}

//int count;

void loop() {
  char str[10];
  long apnoload, activeEnergyA;
  int hwaddr=getHwAddr();
  int instatus = getInput();
  float vRMS, iRMSA, powerFactorA, apparentPowerA, reactivePowerA, activePowerA;

  eepromdata.read(0, str, 10);
  apnoload = myADE7953.getAPNOLOAD();
  Serial.print(str);
  Serial.print("HwAddr(Hex): ");
  Serial.println(hwaddr, HEX);
  Serial.print("Input(Hex): ");
  Serial.println(instatus, HEX);
  Serial.print("APNOLOAD (hex): ");
  Serial.println(apnoload, HEX);
  delay(200); 

  vRMS = myADE7953.getVrms();  
  Serial.print("Vrms (V): ");
  Serial.println(vRMS);
  delay(200);

  iRMSA = myADE7953.getIrmsA();  
  Serial.print("IrmsA (mA): ");
  Serial.println(iRMSA);
  delay(200);

  apparentPowerA = myADE7953.getInstApparentPowerA();  
  Serial.print("Apparent Power A (mW): ");
  Serial.println(apparentPowerA);
  delay(200);

  activePowerA = myADE7953.getInstActivePowerA();  
  Serial.print("Active Power A (mW): ");
  Serial.println(activePowerA);
  delay(200);

  reactivePowerA = myADE7953.getInstReactivePowerA();  
  Serial.print("Rective Power A (mW): ");
  Serial.println(reactivePowerA);
  delay(200);

  powerFactorA = myADE7953.getPowerFactorA();  
  Serial.print("Power Factor A (x100): ");
  Serial.println(powerFactorA);
  delay(200);

  activeEnergyA = myADE7953.getActiveEnergyA();  
  Serial.print("Active Energy A (hex): ");
  Serial.println(activeEnergyA);
  delay(200);

  Serial.println();

  iRMSA = myADE7953.getIrmsB();  
  Serial.print("IrmsB (mA): ");
  Serial.println(iRMSA);
  delay(200);

  apparentPowerA = myADE7953.getInstApparentPowerB();  
  Serial.print("Apparent Power B (mW): ");
  Serial.println(apparentPowerA);
  delay(200);

  activePowerA = myADE7953.getInstActivePowerB();  
  Serial.print("Active Power B (mW): ");
  Serial.println(activePowerA);
  delay(200);

  reactivePowerA = myADE7953.getInstReactivePowerB();  
  Serial.print("Rective Power B (mW): ");
  Serial.println(reactivePowerA);
  delay(200);

  powerFactorA = myADE7953.getPowerFactorB();  
  Serial.print("Power Factor B (x100): ");
  Serial.println(powerFactorA);
  delay(200);

  activeEnergyA = myADE7953.getActiveEnergyB();  
  Serial.print("Active Energy B (hex): ");
  Serial.println(activeEnergyA);
  delay(200);

  Serial.println();

//  if(count>5){
//    while(1);
//  }
//  count++;
}
