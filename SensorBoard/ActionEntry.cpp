#include "SensorBoardCommon.h"
#include "RS485SensorBoard.h"
#include "RTC4SensorBoard.h"
#include "ActionEntry.h"

ActionEntry::ActionEntry(){
  
}

void ActionEntry::begin(){
  _powerData4EEPRomV2.begin();
  time_t time_ineeprom = _powerData4EEPRomV2.getTime4Index();
  time_t time_now = RTC.getEpoch();
  if(time_now<time_ineeprom)time_ineeprom=time_now;
  _powerRealtimeLogic.setStartTime4EEPROM(time_ineeprom);
}

void ActionEntry::setInput(int status){
  int event=_inputLogic.setStatus(status);
  if(event==1)action4InputOnEvent();
  else if(event==2)action4InputOffEvent();
}

void ActionEntry::setHardAddr(int addr){
  _hwaddr=addr;
}

void ActionEntry::setECOData(int channel, uint32_t voltage, uint32_t current, uint32_t power, uint32_t rpower, uint32_t pf, uint32_t temperature){
  PowerDataItem4Realtime item;
  item.voltage=voltage;
  item.current=current;
  item.power=power;
  item.reactivepower=rpower;
  item.powerfactory=pf;
  item.temperature=temperature;
  //Serial.print("setEcoData ");Serial.print(channel);Serial.print(" ");Serial.print(voltage);Serial.print(" ");Serial.print(power);Serial.println(" ");
  if(_powerRealtimeLogic.setData(item, channel)==1){
    Serial.print("stored data to eeprom ");
    PowerDataItem4EEPROM powerdataitem;
    if(_powerRealtimeLogic.getEEPROMData(powerdataitem)==0) return;
    //_powerData4EEPRomV2.writeData2EEPRom(powerdataitem.power, powerdataitem.datatime);
  }
}

void ActionEntry::set485Command(String cmd){
  int action = _dataProtocol.setProtocolData(cmd, _hwaddr);
  if(action==0) return;
  int ret=0;
  switch (action) {
  case CMD_REQ_REALTIMEDATA:{
    PowerDataItem4Realtime item;
    RS485Sensorboard.enableWrite();
    for(int i=0;i<TOTAL_CHANNELNUMS;i++){
      if(_powerRealtimeLogic.getRealtimeData(item, i)==1){
        Serial.print(cmd.substring(0,6));
        Serial.print(i, DEC);Serial.print(";");
        Serial.print(item.datatime, DEC);Serial.print(";");
        Serial.print(item.voltage, DEC);Serial.print(";");
        Serial.print(item.current, DEC);Serial.print(";");
        Serial.print(item.power, DEC);Serial.print(";");
        Serial.print(item.reactivepower, DEC);Serial.print(";");
        Serial.print(item.powerfactory, DEC);Serial.print(";");
        Serial.print(item.temperature, DEC);Serial.print(";\n");
      }
    }
    delay(10);
    RS485Sensorboard.enableRead();
    ret=1;
  }
    break;
  case CMD_REQ_DATABYTIME:{
    uint32_t time4set=cmd.substring(7).toInt();
    if(time4set==0) break;
    uint32_t data[10]={0};
    if(_powerData4EEPRomV2.readData2EEPRom(data, time4set)!=1)break;
    RS485Sensorboard.enableWrite();
    Serial.print(cmd.substring(0,6));
    Serial.print(data[0], DEC);Serial.print(";");
    Serial.print(data[1], DEC);Serial.print(";");
    Serial.print(data[2], DEC);Serial.print(";");
    Serial.print(data[3], DEC);Serial.print(";");
    Serial.print(data[4], DEC);Serial.print(";");
    Serial.print(data[5], DEC);Serial.print(";\n");
    delay(10);
    RS485Sensorboard.enableRead();
    ret=1;
  }
    break;
  case CMD_REQ_DATABYINDEX:
      //ret=getDataByIndex(0);
      break;
  case CMD_SET_485ID:
      //ret=setSoftwareId();
      break;
  case CMD_REQ_485ID:
      //ret=getSoftwareId();
      break;
  case CMD_REQ_VERSIONINFO:
    RS485Sensorboard.enableWrite();
    Serial.print(cmd.substring(0,6));
    Serial.print(SENSORBOARD_SOFTWARE_VERSION);Serial.print(";OK\n");
    delay(10);
    RS485Sensorboard.enableRead();
    ret=1;
    break;
  case CMD_SET_RTCTIME:{
    uint32_t time4set1=cmd.substring(7).toInt();
    if(time4set1==0) break;
    RTC.setEpoch(time4set1);
    RS485Sensorboard.enableWrite();
    Serial.print(cmd.substring(0,6));
    Serial.print(RTC.getEpoch(), DEC);Serial.print(";OK\n");
    delay(10);
    RS485Sensorboard.enableRead();
    ret=1;
  }
    break;
  case CMD_REQ_RTCTIME:{
    RS485Sensorboard.enableWrite();
    Serial.print(cmd.substring(0,6));
    Serial.print(RTC.getEpoch(), DEC);Serial.print(";\n");
    delay(10);
    RS485Sensorboard.enableRead();
    ret=1;
  }
    break;
  default:
      //ret = setNoAck();
      break;
  }
  if(ret!=1){
    RS485Sensorboard.enableWrite();
    Serial.print(cmd.substring(0,6));
    Serial.println("NG");
    delay(10);
    RS485Sensorboard.enableRead();
  }  
}

void ActionEntry::action4InputOnEvent(){
  // pending, add the function later ..
}
void ActionEntry::action4InputOffEvent(){
  // pending, add the function later ..
}
