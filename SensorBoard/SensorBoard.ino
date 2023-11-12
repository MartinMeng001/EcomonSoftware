#include "HardwareDef.h"
#include "Leds4SensorBoard.h"
#include "RTC4SensorBoard.h"
#include "EEPROMData4SensorBoard.h"
#include "CS5480SensorBoard.h"
#include "HwAddr4SensorBoard.h"
#include "RS485SensorBoard.h"
#include "Input4SensorBoard.h"
#include "Output4SensorBoard.h"
#include "ActionEntry.h"




CS5480 powerMeter[3];
//CS5480 powerMeter1(PB0_POWERMETER1,PD7_RESET_POWERMETERS);
//CS5480 powerMeter2(PB1_POWERMETER2,PD7_RESET_POWERMETERS);
//CS5480 powerMeter3(PB2_POWERMETER3,PD7_RESET_POWERMETERS);
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
unsigned int sel_cs5480=0;
void setup() {
  // put your setup code here, to run once: eepromdata
  // hardware init
  Serial.begin(115200);
  //RS485Sensorboard.begin(); // communication start
  //RTC.begin();      // time start
  //eepromdata.begin(); // CS5480 start
  Serial.print("Testing Init\n");
  /*
  for(int i=0;i<3;i++){
    powerMeter[i].begin(PB0_POWERMETER1+i,PD7_RESET_POWERMETERS);
    if(i==0)powerMeter[i].init();
    powerMeter[i].initcs5480();
  }*/
  // running param init
  led.flash(1000,500);
  //sensorBoardActionEntry.begin();
  // reserve 100 bytes for the inputString:
  //inputString.reserve(100);

}

void loop() {
  // put your main code here, to run repeatedly:
//  led.flash(1000,500);
//  sensorBoardActionEntry.begin();
  Serial.print("Testing\n");
  // input status check
  //sensorBoardActionEntry.setInput(InputSensorBoard.status());
  // 485 HwAddr
  //sensorBoardActionEntry.setHardAddr(HwAddr485.addr());
  // cs5480 data check per
  /*
  unsigned int index=sel_cs5480%3;
  //Serial.print("Data ready=");Serial.println(powerMeter[index].getStatus());
  //if((powerMeter[index].getStatus() & DATA_READY)!=0){powerMeter1
  uint32_t status=powerMeter[index].getStatus();
  //Serial.print("Data status ");Serial.print(status, HEX); Serial.print(" - "); Serial.println(index);
  if((status & DATA_READY)!=0 && (status!=0x00FFFFFF)){   
    
    uint32_t voltage = powerMeter[index].getRawVoltage();
    uint32_t current1= powerMeter[index].getRawCurrent(1);
    uint32_t current2= powerMeter[index].getRawCurrent(2);
    uint32_t power1= powerMeter[index].getRawPower(1);
    uint32_t power2= powerMeter[index].getRawPower(2);
    uint32_t rpower1= powerMeter[index].getRawRPower(1);
    uint32_t rpower2= powerMeter[index].getRawRPower(2);
    uint32_t pf1= powerMeter[index].getRawPowerFactor(1);
    uint32_t pf2= powerMeter[index].getRawPowerFactor(2);
    uint32_t temperature = powerMeter[index].getRawTemperature();
    powerMeter[index].clearStatus(0x00FFFFFF);
    Serial.print("Data Voltage ");Serial.print(voltage*0.0251/1000); Serial.print(" = "); Serial.println(index);
    Serial.println(RTC.getEpoch());
    
    sensorBoardActionEntry.setECOData(index*2, voltage, current1, power1, rpower1, pf1, temperature);
    sensorBoardActionEntry.setECOData(index*2+1, voltage, current2, power2, rpower2, pf2, temperature);
  }*//*
  // serial port data
  if (stringComplete) {
    // clear the string:
    sensorBoardActionEntry.set485Command(inputString);
    inputString = "";
    stringComplete = false;
  }*/
  //sel_cs5480++;
  delay(1);
}
/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the inputString is over the length, ignore the string
    if(inputString.length()>99)inputString = "";
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
