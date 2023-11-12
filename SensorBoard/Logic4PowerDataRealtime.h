#ifndef __POWERDATAREALTIMESENSORBOARD_H__
#define __POWERDATAREALTIMESENSORBOARD_H__
#include <arduino.h>
#include <time.h>
#define MINUTEINTERVAL_EEPROM_PER_DATA  5
#define TOTAL_CHANNELNUMS               6

struct PowerDataItem4Realtime{
    time_t datatime;
    uint32_t voltage;
    uint32_t current;
    uint32_t power;
    uint32_t reactivepower;
    uint32_t powerfactory;
    uint32_t temperature;
};

struct PowerDataItem4EEPROM{
    time_t datatime;
    uint32_t power[TOTAL_CHANNELNUMS];
};

class PowerDataRealtime{
  public:
  PowerDataRealtime();
  int setData(PowerDataItem4Realtime &item, int chan);
  int getRealtimeData(PowerDataItem4Realtime& item, int chan);
  void setStartTime4EEPROM(time_t starttime);
  int getEEPROMData(PowerDataItem4EEPROM& powerdataitem);
  protected:
  void resetData();
  void resetEEPROMdata();
  int checkChannel(int chan);
  int setpowerdataitem4EEPROM(uint32_t data, int channel, time_t datatime);
  int data2EEPROMLogicCheck(time_t starttime, time_t datatime);
  private:
  PowerDataItem4Realtime realtimedata[TOTAL_CHANNELNUMS];
  PowerDataItem4EEPROM _eepromdata;
  time_t starttime4eeprom;
};

#endif
