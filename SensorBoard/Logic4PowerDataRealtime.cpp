#include "RTC4SensorBoard.h"
#include "Logic4PowerDataRealtime.h"

PowerDataRealtime::PowerDataRealtime(){
  resetData();
  resetEEPROMdata();
}

int PowerDataRealtime::setData(PowerDataItem4Realtime &item, int chan){
  if(checkChannel(chan)==0) return 0;
  realtimedata[chan].datatime=RTC.getEpoch();
  realtimedata[chan].voltage=item.voltage;
  realtimedata[chan].current=item.current;
  realtimedata[chan].power=item.power;
  realtimedata[chan].reactivepower=item.reactivepower;
  realtimedata[chan].powerfactory=item.powerfactory;
  realtimedata[chan].temperature=item.temperature;
  setpowerdataitem4EEPROM(item.power, chan, realtimedata[chan].datatime);
  return data2EEPROMLogicCheck(starttime4eeprom, realtimedata[chan].datatime);
}

int PowerDataRealtime::getRealtimeData(PowerDataItem4Realtime& item, int chan){
  if(checkChannel(chan)==0) return 0;
  if(realtimedata[chan].datatime==0) return 0;
  item.datatime=realtimedata[chan].datatime;
  item.voltage=realtimedata[chan].voltage;
  item.current=realtimedata[chan].current;
  item.power=realtimedata[chan].power;
  item.reactivepower=realtimedata[chan].reactivepower;
  item.powerfactory=realtimedata[chan].powerfactory;
  item.temperature=realtimedata[chan].temperature;
  return 1;
}
int PowerDataRealtime::getEEPROMData(PowerDataItem4EEPROM &powerdataitem)
{
  setStartTime4EEPROM(RTC.getEpoch());
    powerdataitem.datatime=RTC.getEpoch();
    for(int i=0;i<TOTAL_CHANNELNUMS;i++){
        powerdataitem.power[i]=_eepromdata.power[i];
    }
    resetEEPROMdata();
    return 1;
}
void PowerDataRealtime::setStartTime4EEPROM(time_t starttime){
  starttime4eeprom=starttime;
}

int PowerDataRealtime::setpowerdataitem4EEPROM(uint32_t data, int channel, time_t datatime)
{
    //int diff = (int)difftime(datatime, powerdataEEPROM.datatime);
    _eepromdata.datatime=datatime;
    _eepromdata.power[channel]+=data;
    return 1;
}
void PowerDataRealtime::resetData(){
  //eepromdata.datatime=0;
  for(int i=0;i<TOTAL_CHANNELNUMS;i++){
    realtimedata[i].datatime=0;
    realtimedata[i].voltage=0;
    realtimedata[i].current=0;
    realtimedata[i].power=0;
    realtimedata[i].reactivepower=0;
    realtimedata[i].powerfactory=0;
    realtimedata[i].temperature=0;
    //eepromdata.power[i]=0;
  }
}
void PowerDataRealtime::resetEEPROMdata(){
  _eepromdata.datatime=0;
  for(int i=0;i<TOTAL_CHANNELNUMS;i++){
    _eepromdata.power[i]=0;
  }
}
int PowerDataRealtime::checkChannel(int chan){
  if(chan>=0 && chan<TOTAL_CHANNELNUMS) return 1;
  return 0;
}

int PowerDataRealtime::data2EEPROMLogicCheck(time_t starttime, time_t datatime)
{
    //struct tm* start, *current;
    uint32_t start_min, current_min;
    start_min=localtime(&starttime)->tm_min;
    current_min=localtime(&datatime)->tm_min;
    //Serial.print("start time min=");Serial.print(start_min);
    //Serial.print("current time min=");Serial.println(current_min);
    if(starttime>datatime) return 0;
    if(start_min!=current_min){
        if((current_min%5) == 0) {
    Serial.print("start time min=");Serial.print(start_min);
    Serial.print("start time=");Serial.println(starttime);
    Serial.print("current time min=");Serial.print(current_min);
    Serial.print("current time=");Serial.println(datatime);
          return 1;
        }
    }
    return 0;
}
