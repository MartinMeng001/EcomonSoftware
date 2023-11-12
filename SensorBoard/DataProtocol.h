#ifndef DATAPROTOCOL_H
#define DATAPROTOCOL_H
#include <arduino.h>
#include <time.h>
#define CMD_NOACK               '0'
#define CMD_REQ_REALTIMEDATA    '1'
#define CMD_REQ_DATABYTIME      '2'
#define CMD_REQ_DATABYINDEX     '3'
#define CMD_SET_485ID           '4'
#define CMD_REQ_485ID           '5'
#define CMD_SET_RTCTIME         '6'
#define CMD_REQ_RTCTIME         '7'
#define CMD_REQ_VERSIONINFO     'V'

class DataProtocol
{
public:
    DataProtocol();
    int setProtocolData(String &recdata, int hwaddr);
protected:
    int getRealtimeData();
    int getDataByTime(time_t databegintime);
    int getDataByIndex(int index);
    int getSoftwareId();
    int setSoftwareId(char id);
    int getRTCTime();
    int setRTCTime(time_t timenow);
    int setNoAck();
    int parseCmd(String &recdata, int hwaddr);
    int replyData();
};

#endif // DATAPROTOCOL_H
