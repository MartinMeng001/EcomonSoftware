#include "EEPROMData4SensorBoard.h"
#include "PowerData4EEPRomV2.h"
#include "Leds4SensorBoard.h"
//extern static AT24C512 eepromdata;
PowerData4EEPROMV2::PowerData4EEPROMV2()
{

}
void PowerData4EEPROMV2::begin(){
  if(checkMagicStr()==0){
    resetDataSpace();
  }
  initcurrentpos();
}
void PowerData4EEPROMV2::resetDataSpace()
{
  uint32_t data=0;
  for(uint32_t i=0;i<ATMAXADR/4;i++){
    //eepromdata.write(i*4, data, 4);
	eepromdata.writeLong(i*4, data);
  }
  writeMagicStr();
  checkMagicStr();
}
time_t PowerData4EEPROMV2::getTime4Index(){
  return currentpos.time4index;
}
void PowerData4EEPROMV2::initcurrentpos(){
  currentpos.index = eepromdata.readUnsignedLong(4);//(4,4);
  currentpos.time4index = eepromdata.readUnsignedLong(8);//(8,4);
  currentpos.totals = eepromdata.readUnsignedLong(12);//eepromdata.read(12,4);
}
void PowerData4EEPROMV2::updateCurrentPos(){
	eepromdata.writeLong(4, currentpos.index);
	eepromdata.writeLong(8, currentpos.time4index);
	eepromdata.writeLong(12, currentpos.totals);
}

int PowerData4EEPROMV2::checkMagicStr(){
  uint32_t datamagic=eepromdata.readUnsignedLong(0);//eepromdata.read(0,4);
  Serial.print("read magic=");Serial.println(datamagic);
  Serial.print("define magic=");Serial.println(VERSION_EEPROM_MAGICDATA);
  if(datamagic==VERSION_EEPROM_MAGICDATA) return 1;
  return 0;
}
void PowerData4EEPROMV2::writeMagicStr(){
  uint32_t datamagic=VERSION_EEPROM_MAGICDATA;
  eepromdata.writeLong(0, datamagic);
  //eepromdata.write(0, datamagic, 4);
}
uint32_t PowerData4EEPROMV2::getPos(time_t datatime, time_t lastdatatime){
  if(datatime<lastdatatime)return 0;
  uint32_t diff=(datatime-lastdatatime)/300;
  if(diff<2) return 1;
  return diff;
}
// num    page  index
// 1    1   0
// 2    1   1
// 3    1   2
// 4    2   0
uint32_t PowerData4EEPROMV2::getpageByNum(uint32_t num){
  return ((num-1)/3+1);
}
uint32_t PowerData4EEPROMV2::getindexByNum(uint32_t num){
  return (num-1)%3;
}
void PowerData4EEPROMV2::writeData2EEPRom(uint32_t* data, time_t datatime){
  uint32_t num=getPos(datatime, currentpos.time4index);
  if(num==0) return;
  uint32_t index=currentpos.index;
  do{
    index++; if(index>1440)index=1;
    uint32_t page=getpageByNum(index);
    uint32_t pageindex=getindexByNum(index);
      Serial.print("write page="); Serial.println(page);
      Serial.print("write pagepos="); Serial.println(pageindex);
    writeDataPerGroup(data, page, pageindex);  
    num--;
  }while(num>0);
  currentpos.index=index;
  currentpos.time4index=datatime;
  if(currentpos.totals<1440)currentpos.totals+=num;
  if(currentpos.totals>1440)currentpos.totals=1440;
}
//void PowerData4EEPROMV2::writeData2EEPRom(uint32_t* data, time_t datatime){
//  uint32_t num = getPositionByTime(datatime);
//  Serial.print("write pos="); Serial.println(num);
//  Serial.print("time="); Serial.println(datatime);
//  if(num==0) return;
//  if(num>SUPPORT_DATAITEMS){
//    resetDataSpace();
//    currentpos.index = 0;
//    currentpos.time4index = datatime;
//    currentpos.totals = 0;
//    num=1;
//  }
//  uint32_t lastindex=currentpos.index;
//  setDataTotals(num);
//  setDataIndex(num);
//  int currentindex=currentpos.index;
//  for(uint32_t i=0;i<num;i++){
//    if(i==num-1){
//      uint32_t page=getPageIndexByNum(currentindex)+1;  // the page begin from 1, page 0 was not for data
//      uint32_t pagepos=getDataNumInPageByNum(currentindex);
//      Serial.print("write page="); Serial.println(page);
//      Serial.print("write pagepos="); Serial.println(pagepos);
//      writeDataPerGroup(data, page, pagepos);      
//    }else if(i!=0){  // clear all data between last and current
//      uint32_t page=getPageIndexByNum(lastindex+i)+1;
//      uint32_t pagepos=getDataNumInPageByNum(lastindex+i);
//      uint32_t datatemp[10]={0};
//      writeDataPerGroup(datatemp, page, pagepos);   
//    }
//  }
//  updateCurrentPos();
//}
int PowerData4EEPROMV2::readData2EEPRom(uint32_t* data, time_t datatime){
  uint32_t num = getPositionByTime(datatime);
  if(num==0) return 0;
  if(num>SUPPORT_DATAITEMS)return 0;
  uint32_t lastindex=currentpos.index;
  setDataTotals(num);
  setDataIndex(num);
  uint32_t currentindex=currentpos.index;
  uint32_t page=getPageIndexByNum(currentindex)+1;  // the page begin from 1, page 0 was not for data
  uint32_t pagepos=getDataNumInPageByNum(currentindex);
  readDataPerGroup(data, page, pagepos);
  return 1;
  
}

void PowerData4EEPROMV2::setDataTotals(uint32_t num){
  if(currentpos.totals<SUPPORT_DATAITEMS){
    if(currentpos.index+num < SUPPORT_DATAITEMS)currentpos.totals=currentpos.index+num;
    else currentpos.totals=SUPPORT_DATAITEMS;
  }
}

void PowerData4EEPROMV2::setDataIndex(uint32_t num){
  if(currentpos.index+num < SUPPORT_DATAITEMS)currentpos.index=currentpos.index+num;
  else currentpos.index=currentpos.index+num-SUPPORT_DATAITEMS;
}

uint32_t PowerData4EEPROMV2::getPositionByTime(time_t datatime){
  //if(currentpos.time4index==0){
  if(datatime>currentpos.time4index){
    if(currentpos.time4index==0){
      currentpos.time4index=datatime;
      return 1;
    }else{
      uint32_t ret=(datatime-currentpos.time4index)/300 + 1;
      currentpos.time4index=datatime;
      return ret;
    }
  }else{
    currentpos.index = 0;
    currentpos.time4index = datatime;
    currentpos.totals = 0;
  }
  return 0;
}
// 10 int values per group
int PowerData4EEPROMV2::writeDataPerGroup(uint32_t *data, uint32_t page, uint32_t pagepos)
{
    uint32_t position=getPositionByPage(page, pagepos);
    if(position==-1) return -1;
    for(int i=0;i<6;i++){
      //eepromdata.write(position+i*4, data[i], 4);
      eepromdata.writeLong(position+i*4, data[i]);
    }
    return 1;
}

int PowerData4EEPROMV2::readDataPerGroup(uint32_t *data, uint32_t page, uint32_t pagepos)
{
    uint32_t position=getPositionByPage(page, pagepos);
    if(position==-1) return -1;
    for(int i=0;i<6;i++){
      data[i] = eepromdata.readUnsignedLong(position+i*4);//eepromdata.read(position+i*4, 4);
    }
    return 1;
}

int PowerData4EEPROMV2::writeData2Postion(uint32_t &data, uint32_t position)
{
    //eepromdata.write(position, data, 4);
	eepromdata.writeLong(position, data);
    return 1;
}

int PowerData4EEPROMV2::readDataFromPosition(uint32_t &data, uint32_t position)
{
    data=eepromdata.readUnsignedLong(position);//eepromdata.read(position);
    return 1;
}

uint32_t PowerData4EEPROMV2::getPositionByPage(uint32_t page, uint32_t pagepos)
{
    if(pagepos>=3)return -1;
    uint32_t position = page*BYTES_PERPAGE+pagepos*BYTES_PAGEITEM;
    return position;
}

int PowerData4EEPROMV2::writeDataByNum(uint32_t *data, uint32_t datanum)
{
    uint32_t page = getPageIndexByNum(datanum);
    uint32_t pagepos = getDataNumInPageByNum(datanum);
    if(page==-1 || pagepos==-1) return -1;
    return writeDataPerGroup(data, page, pagepos);
}

int PowerData4EEPROMV2::readDataByNum(uint32_t *data, uint32_t datanum)
{
    uint32_t page = getPageIndexByNum(datanum);
    uint32_t pagepos = getDataNumInPageByNum(datanum);
    if(page==-1 || pagepos==-1) return -1;
    return readDataPerGroup(data, page, pagepos);
}

uint32_t PowerData4EEPROMV2::getPageIndexByNum(uint32_t datanum)
{
    uint32_t ret=datanum/3;
    if(ret<0||ret>=PAGES_TOTALEEPROM)return -1;
    return ret;
}

uint32_t PowerData4EEPROMV2::getDataNumInPageByNum(uint32_t datanum)
{
    uint32_t ret=datanum%3;
    if(datanum<0)return -1;
    return ret;
}

//int PowerData4EEPROMV2::Data2Char(int data, char *convdata)
//{
//    for(int i=0;i<4;i++){
//        convdata[i]=(char)((data>>i)&0x000000FF);
//    }
//    return 1;
//}
//
//int PowerData4EEPROMV2::Char2Data(char *convdata, int& data)
//{
//    int ret=0;
//    for(int i=0;i<4;i++){
//        ret|=convdata[i];
//        if(i<3)ret<<8;
//    }
//    data=ret;
//    return 1;
//}
