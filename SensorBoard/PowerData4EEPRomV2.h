#ifndef POWERDATA4EEPROMV2_H
#define POWERDATA4EEPROMV2_H

#include <arduino.h>
#include <time.h>

#define SUPPORT_DATAITEMS   1440
#define BYTES_PERPAGE       128
#define BYTES_PAGEITEM      40
#define NUMS_PERPAGEITEM    10
#define PAGES_TOTALEEPROM   480

#define VERSION_EEPROM_MAGICDATA  0x80809090

struct PowerData4EEPROMV2_Item{
    uint32_t index;  // 0~1440
    time_t time4index;
    uint32_t totals; // max 1440
};

class PowerData4EEPROMV2
{
public:
    PowerData4EEPROMV2();
    void writeData2EEPRom(uint32_t* data, time_t datatime);
    int readData2EEPRom(uint32_t* data, time_t datatime);
    time_t getTime4Index();
    void begin();
protected:
    // basic function
    void resetDataSpace();
    void initcurrentpos();
    void updateCurrentPos();
    void setDataTotals(uint32_t num);
    void setDataIndex(uint32_t num);
    int checkMagicStr();
    void writeMagicStr();
    int writeDataByNum(uint32_t* data, uint32_t datanum);
    int readDataByNum(uint32_t* data, uint32_t datanum);
    int writeDataPerGroup(uint32_t* data, uint32_t page, uint32_t pagepos);
    int readDataPerGroup(uint32_t* data, uint32_t page, uint32_t pagepos);
    int writeData2Postion(uint32_t& data, uint32_t position);
    int readDataFromPosition(uint32_t& data, uint32_t position);
    // position
    uint32_t getPositionByTime(time_t datatime);
    uint32_t getPositionByPage(uint32_t page, uint32_t pagepos);
    uint32_t getPageIndexByNum(uint32_t datanum);
    uint32_t getDataNumInPageByNum(uint32_t datanum);
    uint32_t getPos(time_t datatime, time_t lastdatatime);
    uint32_t getpageByNum(uint32_t num);
    uint32_t getindexByNum(uint32_t num);
    // Data Convert
//    int Data2Char(int data, char* convdata);
//    int Char2Data(char* convdata, int& data);

  private:
    PowerData4EEPROMV2_Item currentpos;
};

#endif // POWERDATA4EEPROMV2_H
