#ifndef __ACTIONENTRYSENSORBOARD_H__
#define __ACTIONENTRYSENSORBOARD_H__

#include <arduino.h>
#include "Logic4Input.h"
#include "Logic4PowerDataRealtime.h"
#include "PowerData4EEPRomV2.h"
#include "DataProtocol.h"
class ActionEntry{
  public:
    ActionEntry();
    void begin();
    void setInput(int status);
    void setHardAddr(int addr);
    void setECOData(int channel, uint32_t voltage, uint32_t current, uint32_t power, uint32_t rpower, uint32_t pf, uint32_t temperature);
    void set485Command(String cmd);
  protected:
    //void run();
    void action4InputOnEvent();
    void action4InputOffEvent();
  private:
    int _hwaddr;
    Logic4Input _inputLogic;
    PowerDataRealtime _powerRealtimeLogic;
    PowerData4EEPROMV2 _powerData4EEPRomV2;
    DataProtocol _dataProtocol;
};
static ActionEntry sensorBoardActionEntry;
#endif
