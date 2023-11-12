/*************************************************** 
  Arduino library for the AT24CM01
  
  Author: Jonathan Dempsey JDWifWaf@gmail.com
  
  Version: 1.0.1
  License: Apache 2.0
 ****************************************************/

#include <Wire.h>
#include "EEPROMData4SensorBoard.h"

#define DEBUG 0
           
#define GETADR(MGADR) ((MGADR >> 16) | ATDEVADR)
#define CHCKSIZE(x) ((x)>8 || (x)==0) ? Serial.print("\n<AT24C512> Error - Size given too large or small (1-8)") : 0
#define CHCKADDR(x) ((x)>ATMAXADR) ? Serial.print("\n<AT24C512> Error - Address given too large (0 - 65536)") : 0

/*
#define AT24CM01_ADR_A1H 0x08
#define AT24CM01_ADR_A2H 0x14
#define AT24CM01_ADR_A1L 0x00
#define AT24CM01_ADR_A2L 0x00            // Not needed unless you want to determine address manually and shift the bytes

#define AT24CM01_PAGE_ADR0 0x50
#define AT24CM01_PAGE_ADR1 0x51
#define AT24CM01_WPAGE_ADR0 0x00
#define AT24CM01_WPAGE_ADR1 0x02
#define AT24CM01_WORD_ADR 0xA0
*/
AT24C512 eepromdata(4);
AT24C512::AT24C512(int wrpin){
  pinMode(wrpin, OUTPUT);
  _wrpin=wrpin;
}
void AT24C512::begin(TwoWire &inWire) 
{
  disWriteProtected();
  this->ATWire = &inWire;
  this->ATWire->begin();
  this->ATWire->setClock(AT2CSPEED);
}
void AT24C512::enWriteProtected(){
  digitalWrite(4, HIGH);
}
void AT24C512::disWriteProtected(){
  digitalWrite(4, LOW);
}
uint32_t AT24C512::read(uint32_t address, uint8_t size)
{
  if(CHCKADDR(address) || CHCKSIZE(size))
    return 0;
 
  this->ATWire->beginTransmission((uint8_t)GETADR(address));
  this->ATWire->write((uint8_t)((address & 0xFFFF) >> 8));  
  this->ATWire->write((uint8_t)(address & 0xFF));
  this->ATWire->endTransmission();

  this->ATWire->requestFrom((uint8_t)GETADR(address), (uint8_t)size); 
  uint32_t buff0 = 0;
  uint32_t buff1 = 0; 
  if(this->ATWire->available())
  { 
    for(uint8_t x = 0; x < size; x++)
    {
      buff1 = this->ATWire->read();
      if(!buff1)
        continue;
      buff0 |= (buff1 << x*8);
    }
  }
  return buff0;
}

void AT24C512::read(uint32_t address, uint8_t data[], uint8_t indexCount)
{
  if(CHCKADDR(address))
    return;

  memset(data, 0, indexCount);
 
  this->ATWire->beginTransmission((uint8_t)GETADR(address));
  this->ATWire->write((uint8_t)((address & 0xFFFF) >> 8));
  this->ATWire->write((uint8_t)(address & 0xFF));
  this->ATWire->endTransmission();

  this->ATWire->requestFrom((uint8_t)GETADR(address), indexCount); 
  if(this->ATWire->available())
  { 
    for(uint8_t x = 0; x < indexCount; x++)
      data[x] = this->ATWire->read();
  }
}

void AT24C512::write(uint32_t address, uint32_t data)
{
  if(CHCKADDR(address))
    return;

  this->ATWire->beginTransmission((uint8_t)GETADR(address));                // Start, and determine segment address 
  this->ATWire->write((uint8_t)((address & 0x00FF) >> 8));                  // Set curser to address for writing
  this->ATWire->write((uint8_t)(address & 0xFF));
  
  uint8_t sBuff = 0;
  for(uint8_t x = 0; (data & (0xFFFFFFFF << x*8)); x++)                // Determine data size
  {                                                                    
    sBuff = (data >> x*8) & 0xFF;                                      // Value if required into appropriate parts
    this->ATWire->write(sBuff);                                              // Address rolls over when stop is not called - see datasheet.
  }
  
  this->ATWire->endTransmission();                                           // Stop
  
  delay(ATWDelay);                                                     // Delay required to stop write/read failing if carried out abruptly
}

void AT24C512::write(uint32_t address, uint32_t data, uint8_t size)
{
  if(CHCKADDR(address) || CHCKSIZE(size))
    return;
  this->ATWire->beginTransmission((uint8_t)GETADR(address));                 // Start, and determine segment address 
  this->ATWire->write((uint8_t)((address & 0x00FF) >> 8));                   // Set curser to address for writing
  this->ATWire->write((uint8_t)(address & 0xFF));
  
  uint8_t sBuff = 0;
  for(uint8_t x = 0; x < size; x++)                                      
  {                                                                   
    sBuff = (data >> x*8) & 0xFF;                                            // Split into bytes and write
    this->ATWire->write(sBuff);                                              // Address rolls over when stop is not called - see datasheet;
  }
  
  this->ATWire->endTransmission();                                           // Stop
  
  delay(ATWDelay);                                                           // Delay required to stop write/read failing if carried out abruptly
}

void AT24C512::write(uint32_t address, uint8_t data[], uint8_t indexCount)
{
  if(CHCKADDR(address))
    return;
  
  this->ATWire->beginTransmission((uint8_t)GETADR(address));
  this->ATWire->write((uint8_t)((address & 0x00FF) >> 8));
  this->ATWire->write((uint8_t)(address & 0xFF));
  
  for(uint8_t x = 0; x < indexCount; x++)
    this->ATWire->write(data[x]);

  this->ATWire->endTransmission();
  
  delay(ATWDelay);
}
