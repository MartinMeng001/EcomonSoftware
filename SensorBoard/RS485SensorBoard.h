#ifndef RS485ENSORBOARD_H
#define RS485SENSORBOARD_H
#include "Arduino.h"

class RS485SensorBoard{
  public:
    RS485SensorBoard(int pin, uint32_t baudrate);
    int read(char* buff, int maxsize, int timeout);
    int write(char* buff, int maxsize);
    void begin();
    void enableWrite();
    void enableRead();    
  protected:

  private:
    int _pin;
    uint32_t _baudrate;
};

static RS485SensorBoard RS485Sensorboard(5,115200);

#endif
