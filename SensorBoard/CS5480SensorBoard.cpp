#include <math.h>
#include <pins_arduino.h>
#include <SPI.h>
//#include <Serial.h>
#include "CS5480SensorBoard.h"

const unsigned char  cs_page_table[] = {0, 16, 17, 18};
/**
 * \brief constructor without arguments
 */
CS5480::CS5480(): resetPin(PIN_NDEFINED), edirPin(PIN_NDEFINED), eoutPin(PIN_NDEFINED), 
csPin(PIN_NDEFINED),currentGain(1.0),voltageGain(1.0),powerGain(1.0),clkFreq(4096000L), meaFreq(1)
{
}

/**
 * \brief constructor with arguments
 * \param _cs chip select pin
 * \param _reset rest pin
 * \param _edir EDIR pin
 * \param _eout EOUT pin
 */
CS5480::CS5480(uint8_t _cs, uint8_t _reset, uint8_t _edir, uint8_t _eout):currentGain(1.0)
, voltageGain(1.0),powerGain(1.0),clkFreq(4096000L),meaFreq(1)
{
  csPin = _cs;
  pinMode(csPin, OUTPUT);
  digitalWrite(csPin, HIGH);
  resetPin = _reset;
  if (_reset != PIN_NDEFINED)
  {
    pinMode(resetPin, OUTPUT);
    digitalWrite(resetPin, HIGH);
  }
  edirPin = _edir;
  if (_edir != PIN_NDEFINED)
  {
    pinMode(edirPin, INPUT);
  }
  eoutPin = _eout;
  if (_eout != PIN_NDEFINED)
  {
    pinMode(eoutPin, INPUT);
  }
}
void CS5480::begin(uint8_t _cs,uint8_t _reset, uint8_t _edir, uint8_t _eout){
  csPin = _cs;
  pinMode(csPin, OUTPUT);
  digitalWrite(csPin, HIGH);
  resetPin = _reset;
  if (_reset != PIN_NDEFINED)
  {
    pinMode(resetPin, OUTPUT);
    digitalWrite(resetPin, HIGH);
  }
  edirPin = _edir;
  if (_edir != PIN_NDEFINED)
  {
    pinMode(edirPin, INPUT);
  }
  eoutPin = _eout;
  if (_eout != PIN_NDEFINED)
  {
    pinMode(eoutPin, INPUT);
  }  

  //init();
  //initcs5480();
  //startMultiConvert();
}
/**
 * \brief Initialize the chip with sync signal and places the chip in the command 
 * mode where it waits until a valid command is received.
 */
void CS5480::init() const
{
  pinMode(MISO, INPUT_PULLUP);
  select();
  SPI.begin();
  SPI.beginTransaction(SETTING);
  if(resetPin != PIN_NDEFINED)
  {
    digitalWrite(resetPin, HIGH);
  }
  SPI.transfer(SYNC1);
  SPI.transfer(SYNC1);
  SPI.transfer(SYNC1);
  SPI.transfer(SYNC0);
  SPI.endTransaction();
  unselect();
  resetChip();
  delay(1500);
}
void CS5480::initcs5480(){
  unsigned long val;
  val = 0x021eaa; // normal
  //if(mode==2)
  val = val|0x000000;  // have AC 0x421aaa;
  //else val= val|0x800000; // No AC 0x821aaa  
  writeRegister5480(CS_REG_CONFIG2, val);
  startMultiConvert();
}
/**
 * \brief read a register and return the 24-bit data
 * \param reg register address
 * \return 24-bit raw data in MSB
 */
uint32_t CS5480::readRegister(uint8_t reg) const
{
  uint32_t data = 0;
  select();
  SPI.beginTransaction(SETTING);
  reg &= READ_REGISTER;
  SPI.transfer(reg);
  for(uint8_t i = 0;i < 3;++i)
  {
    data <<= 8;
    data |= SPI.transfer(SYNC0);
  }
  SPI.endTransaction();
  unselect();
  return data;
}
uint32_t CS5480::readRegister5480(uint8_t reg) const{
  unsigned char cmd_send[2], cmd;
  uint32_t data = 0;
  cmd = 0x80|cs_page_table[(reg>>CS_PAGE_BITS)];cmd_send[0]=cmd;
  cmd = ((unsigned char)(~(3<<CS_PAGE_BITS)))&reg;
  cmd |= 0x00; cmd_send[1]=cmd;
  //cmd_send[2]=0xFF; cmd_send[3]=0xFF; cmd_send[4]=0xFF;
//  Serial.print("read \t");
//  Serial.print(cmd_send[0],HEX);Serial.print("\t");Serial.println(cmd_send[1],HEX);
  select();
  SPI.beginTransaction(SETTING);
  SPI.transfer(cmd_send[0]);
  SPI.transfer(cmd_send[1]);
  for(uint8_t i = 0;i < 3;i++)
  {
    data <<= 8;
    //data |= SPI.transfer(SYNC0);
    data |= SPI.transfer(SYNC1);
    
  }
  SPI.endTransaction();
  unselect();
  return data;
}
/**
 * \brief write a register for max 24-bit data
 * \param reg register address
 * \param cmd at most 24-bit data, more bits will be ignored
 */
void CS5480::writeRegister(uint8_t reg, uint32_t cmd) const
{
  int32Data data;
  select();
  SPI.beginTransaction(SETTING);
  reg |= WRITE_REGISTER;
  SPI.transfer(reg);
  data.data32 = cmd;
  for(int8_t i = 2;i >=0; --i)
  {// LSB in memory
    SPI.transfer(data.data8[i]);
  }
  SPI.endTransaction();
  unselect();
}
void CS5480::writeRegister5480(uint8_t reg, uint32_t cmd) const{
  unsigned char pcmd[5];
//  Serial.print("write \t");
//  Serial.print(reg,HEX);Serial.print("\t");
  // Page select
  pcmd[0] = 0x80|cs_page_table[(reg>>CS_PAGE_BITS)];
  // Command
  pcmd[1] = ((unsigned char)(~(3<<CS_PAGE_BITS)))&reg;
  pcmd[1] |= 0x40;
  // Data
  pcmd[2] = (unsigned char)((cmd>>16)&0x0000ff);
  pcmd[3] = (unsigned char)((cmd>>8)&0x0000ff);
  pcmd[4] = (unsigned char)((cmd>>0)&0x0000ff);
//  Serial.println("write");
//  for(int8_t i = 0;i <5; i++)
//  {
//    Serial.print(pcmd[i],HEX);Serial.print("\t");
//  }
//  Serial.print("\n");
  select();
  SPI.beginTransaction(SETTING);
  for(int8_t i = 0;i <5; i++)
  {
    SPI.transfer(pcmd[i]);
    //Serial.print(pcmd[i],HEX);Serial.print("\t");
  }
  SPI.endTransaction();
  unselect();
}
/**
 * \brief clear some bits in status register
 * \param cmd status command
 */
void CS5480::clearStatus(uint32_t cmd)
{
  //writeRegister(STATUS_REGISTER, cmd);
  writeRegister5480(CS_REG_STATUS0, cmd);
}

void CS5480::startSingleConvert()
{
  //send(START_SINGLE_CPNVERT);
  send5480(CS_INS_SCONV);
}

void CS5480::startMultiConvert()
{
  //send(START_MULTI_CONVERT);
  send5480(CS_INS_CCONV);
}

void CS5480::resetChip() const
{
  if(resetPin != PIN_NDEFINED)
  {
    digitalWrite(resetPin, LOW);
    delayMicroseconds(130);
    digitalWrite(resetPin, HIGH);
    delayMicroseconds(50);
  }
  else
  {
    writeRegister(CONFIG_REGISTER, CHIP_RESET);
    delayMicroseconds(50);
  }
}

double CS5480::getCurrent()
{
  //return signed2float(readRegister(LAST_CURRENT_REGISTER)) * currentGain;//readRegister5480
  return signed2float(readRegister5480(CS_REG_I1RMS)) * currentGain;
}

uint32_t CS5480::getRawCurrent(int chan)
{
  //return readRegister(LAST_CURRENT_REGISTER);
  if(chan==1)return readRegister5480(CS_REG_I1RMS);
  else return readRegister5480(CS_REG_I2RMS);
}

double CS5480::getVoltage()
{
  //return signed2float(readRegister(LAST_VOLTAGE_REGISTER)) * voltageGain;
  return signed2float(readRegister5480(CS_REG_V1RMS)) * voltageGain;
}

uint32_t CS5480::getRawVoltage()
{
  //return readRegister(LAST_VOLTAGE_REGISTER);
  return readRegister5480(CS_REG_V1RMS);
}

double CS5480::getPower()
{
  //return signed2float(readRegister(LAST_POWER_REGISTER)) * powerGain;
  return signed2float(readRegister5480(CS_REG_P1AVG)) * powerGain;
}

uint32_t CS5480::getRawPower(int chan)
{
  //return readRegister(LAST_POWER_REGISTER);
  if(chan==1)return readRegister(CS_REG_P1AVG);
  else return readRegister(CS_REG_P2AVG);
}

uint32_t CS5480::getRawRPower(int chan)
{
  //return readRegister(LAST_POWER_REGISTER);
  if(chan==1)return readRegister(CS_REG_Q1AVG);
  else return readRegister(CS_REG_Q2AVG);
}

double CS5480::getRMSCurrent()
{
  //return unsigned2float(readRegister(RMS_CURRENT_REGISTER)) * currentGain;
  return unsigned2float(readRegister5480(CS_REG_I1RMS)) * currentGain;
}

uint32_t CS5480::getRawRMSCurrent()
{
  //return readRegister(RMS_CURRENT_REGISTER);
  return readRegister5480(CS_REG_I1RMS);
}

double CS5480::getRMSVoltage()
{
  //return unsigned2float(readRegister(RMS_VOLTAGE_REGISTER)) * voltageGain;
  return unsigned2float(readRegister5480(CS_REG_V1RMS)) * voltageGain;
}

uint32_t CS5480::getRawRMSVoltage()
{
  //return readRegister(RMS_VOLTAGE_REGISTER);
  return readRegister(CS_REG_V1RMS);
}

double CS5480::getApparentPower()
{
  //return getRMSCurrent() * getRMSVoltage();
  return signed2float(readRegister5480(CS_REG_Q1AVG)) * powerGain;
}

double CS5480::getPowerFactor()
{
//  double factor = getEnergy() / getApparentPower();
//  if (isnan(factor))
//    return 0.0;
//  return constrain(factor,-1.0,1.0);
  return signed2float(readRegister5480(CS_REG_PF1));
}
uint32_t CS5480::getRawPowerFactor(int chan){
  if(chan==1)return readRegister5480(CS_REG_PF1);
  else return readRegister5480(CS_REG_PF2);
}
uint32_t CS5480::getRawTemperature(){
  readRegister5480(CS_REG_TEMPERATURE);
}
uint32_t CS5480::getStatus()
{
  //return readRegister(STATUS_REGISTER);
  return readRegister5480(CS_REG_STATUS0);
}

void CS5480::select() const
{
  digitalWrite(csPin, LOW);
}

void CS5480::unselect() const
{
  digitalWrite(csPin, HIGH);
}

void CS5480::setCurrentGain(double gain)
{
  currentGain = gain;
  powerGain = currentGain * voltageGain;
}

void CS5480::setVoltageGain(double gain)
{
  voltageGain = gain;
  powerGain = currentGain * voltageGain;
}

/**
 * \brief send a 8-bit command with no return
 * \param cmd 8-bit command
 */
void CS5480::send(uint8_t cmd)
{
  select();
  SPI.beginTransaction(SETTING);
  SPI.transfer(cmd);
  SPI.endTransaction();
  unselect();
}
void CS5480::send5480(uint8_t cmd){
  unsigned char checksum;
  checksum = 0xff;

  // Instruction
  cmd |= 0xc0;
  checksum -= cmd;
//  Serial.println("send");
//  Serial.println(cmd,HEX);
  select();
  SPI.beginTransaction(SETTING);
  SPI.transfer(cmd);
  SPI.endTransaction();
  unselect();
}
/**
 * \brief calibrate voltage/current gain/offset register
 * \param cmd calibrate command, must be commands for calibrate control
 */
void CS5480::calibrate(uint8_t cmd)
{
  cmd = CALIBRATE_CONTROL | (cmd & CALIBRATE_ALL);
  send(cmd);
  while(!(getStatus() & DATA_READY));
  // wait until data ready;
  clearStatus(DATA_READY);
}

uint32_t CS5480::calibrateVoltageOffset()
{
  calibrate(CALIBRATE_VOLTAGE | CALIBRATE_OFFSET);
  return readRegister(VOLTAGE_OFFSET_REGISTER);
}

uint32_t CS5480::calibrateVoltageGain()
{
  calibrate(CALIBRATE_VOLTAGE | CALIBRATE_GAIN);
  return readRegister(VOLTAGE_GAIN_REGISTER);
}

uint32_t CS5480::calibrateCurrentOffset()
{
  calibrate(CALIBRATE_CURRENT | CALIBRATE_OFFSET);
  return readRegister(CURRENT_OFFSET_REGISTER);
}

uint32_t CS5480::calibrateCurrentGain()
{
  calibrate(CALIBRATE_CURRENT | CALIBRATE_GAIN);
  return readRegister(CURRENT_GAIN_REGISTER);
}

double CS5480::signed2float(int32_t data)
{
  if(data & SIGN_BIT)
  {// signed
    // clear sign bit
    data ^= SIGN_BIT;
    // make it neg
    data = data - SIGNED_OUTPUT_MAX;
  }
  return double(data) / SIGNED_OUTPUT_MAX;
}


double CS5480::unsigned2float(uint32_t data)
{
  return double(data) / UNSIGNED_OUTPUT_MAX;
}

double CS5480::getEnergy()
{
  return signed2float(readRegister(TOTAL_ENERGY_REGISTER)) * powerGain * meaFreq;
}

uint32_t CS5480::getRawEnergy()
{
  return readRegister(TOTAL_ENERGY_REGISTER);
}

/**
* \brief set chip clk frequency and set divide K properly.
* \param freq clk frequency (Hz)
*/
void CS5480::setFrequency(uint32_t freq)
{
  clkFreq = freq;
  if(freq <= 5000000L)
  {
    writeRegister(CONFIG_REGISTER, DIVIDE_K_1);
  }
  else if(freq <= 10000000L)
  {
    writeRegister(CONFIG_REGISTER, DIVIDE_K_2);
  }
  else
  {
    writeRegister(CONFIG_REGISTER, DIVIDE_K_4);
  }
}

/**
* \brief set chip measure (report) frequency and set energy gain properly.
* \param freq frequency (Hz)
*/
void CS5480::setMeasureFrequency(uint32_t freq)
{
  meaFreq = freq;
  writeRegister(CYCLE_COUNT_REGISTER, clkFreq / 1024 / freq);
}
