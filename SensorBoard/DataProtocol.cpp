#include "DataProtocol.h"

DataProtocol::DataProtocol()
{

}

int DataProtocol::setProtocolData(String &recdata, int hwaddr)
{
  return parseCmd(recdata, hwaddr);
}

int DataProtocol::getRealtimeData()
{
  return 0;
}

int DataProtocol::getDataByTime(time_t databegintime)
{
  return 0;
}

int DataProtocol::getDataByIndex(int index)
{
  return 0;
}

int DataProtocol::getSoftwareId()
{
  return 0;
}

int DataProtocol::setSoftwareId(char id)
{
  return 0;
}

int DataProtocol::getRTCTime()
{
  return 0;
}

int DataProtocol::setRTCTime(time_t timenow)
{
  return 0;
}
// 485Addr(3bytes);command(1bytes);dataOpt;
int DataProtocol::parseCmd(String &recdata, int hwaddr)
{
  if(recdata.substring(0,3).toInt()==hwaddr) return recdata.charAt(4);
  return 0;
//    int ret=0;
//    switch (recdata.charAt(4)) {
//    case CMD_REQ_REALTIMEDATA:
//        ret = getRealtimeData();
//        break;
//    case CMD_REQ_DATABYTIME:
//        //ret=getDataByTime();
//        break;
//    case CMD_REQ_DATABYINDEX:
//        ret=getDataByIndex(0);
//        break;
//    case CMD_SET_485ID:
//        //ret=setSoftwareId();
//        break;
//    case CMD_REQ_485ID:
//        ret=getSoftwareId();
//        break;
//    case CMD_SET_RTCTIME:
//        //ret=setRTCTime();
//        break;
//    case CMD_REQ_RTCTIME:
//        ret=getRTCTime();
//        break;
//    default:
//        //ret = setNoAck();
//        break;
//    }
//    if(ret!=1)setNoAck();
//    replyData();
//    return ret;
}

int DataProtocol::replyData()
{
  return 0;
}
int DataProtocol::setNoAck(){
  return 0;
}
