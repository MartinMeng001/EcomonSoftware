#ifndef __CS5480SENSORBOARD_H__
#define __CS5480SENSORBOARD_H__

#include <arduino.h>
#include <stdint.h>
#include <SPI.h>

// CS5480 Macro Definition Start
#define  CS_PAGE_BITS          (6)
#define CS_PAGE_INDEX0          (0<<CS_PAGE_BITS)
#define CS_PAGE_INDEX1          (1<<CS_PAGE_BITS)
#define CS_PAGE_INDEX2          (2<<CS_PAGE_BITS)
#define CS_PAGE_INDEX3          (3<<CS_PAGE_BITS)
// Page 0
#define CS_REG_CONFIG0          (CS_PAGE_INDEX0+0)
#define CS_REG_CONFIG1          (CS_PAGE_INDEX0+1)
#define CS_REG_MASK         (CS_PAGE_INDEX0+3)
#define CS_REG_PC         (CS_PAGE_INDEX0+5)
#define CS_REG_SERIALCTRL       (CS_PAGE_INDEX0+7)
#define CS_REG_PULSEWIDTH       (CS_PAGE_INDEX0+8)
#define CS_REG_PULSECTRL        (CS_PAGE_INDEX0+9)
#define CS_REG_STATUS0          (CS_PAGE_INDEX0+23)
#define CS_REG_STATUS1          (CS_PAGE_INDEX0+24)
#define CS_REG_STATUS2          (CS_PAGE_INDEX0+25)

#define CS_REG_REGLOCK          (CS_PAGE_INDEX0+34)
#define CS_REG_PSDC         (CS_PAGE_INDEX0+48)
#define CS_REG_ZXNUM          (CS_PAGE_INDEX0+55)
// Page 16
#define CS_REG_CONFIG2          (CS_PAGE_INDEX1+0)
#define CS_REG_REGCHK         (CS_PAGE_INDEX1+1)
#define CS_REG_P1AVG          (CS_PAGE_INDEX1+5)
#define CS_REG_I1RMS          (CS_PAGE_INDEX1+6)
#define CS_REG_V1RMS          (CS_PAGE_INDEX1+7)
#define CS_REG_P2AVG          (CS_PAGE_INDEX1+11)
#define CS_REG_I2RMS          (CS_PAGE_INDEX1+12)
#define CS_REG_V2RMS          (CS_PAGE_INDEX1+13)
#define CS_REG_Q1AVG          (CS_PAGE_INDEX1+14)
#define CS_REG_Q2AVG          (CS_PAGE_INDEX1+16)
#define CS_REG_S1         (CS_PAGE_INDEX1+20)
#define CS_REG_PF1          (CS_PAGE_INDEX1+21)
#define CS_REG_S2         (CS_PAGE_INDEX1+24)
#define CS_REG_PF2          (CS_PAGE_INDEX1+25)
#define CS_REG_TEMPERATURE      (CS_PAGE_INDEX1+27)
#define CS_REG_PSUM         (CS_PAGE_INDEX1+29)
#define CS_REG_SSUM         (CS_PAGE_INDEX1+30)
#define CS_REG_QSUM         (CS_PAGE_INDEX1+31)
#define CS_REG_I1GAIN         (CS_PAGE_INDEX1+33)
#define CS_REG_V1GAIN         (CS_PAGE_INDEX1+35)
#define CS_REG_P1OFF          (CS_PAGE_INDEX1+36)
#define CS_REG_I1ACOFF          (CS_PAGE_INDEX1+37)
#define CS_REG_I1DCOFF          (CS_PAGE_INDEX1+32)
#define CS_REG_Q1OFF          (CS_PAGE_INDEX1+38)
#define CS_REG_I2GAIN         (CS_PAGE_INDEX1+40)
#define CS_REG_V2GAIN         (CS_PAGE_INDEX1+42)
#define CS_REG_P2OFF          (CS_PAGE_INDEX1+43)
#define CS_REG_I2ACOFF          (CS_PAGE_INDEX1+44)
#define CS_REG_I2DCOFF          (CS_PAGE_INDEX1+39)
#define CS_REG_Q2OFF          (CS_PAGE_INDEX1+45)
#define CS_REG_EPSILON          (CS_PAGE_INDEX1+49)
#define CS_REG_ICHANLEVEL       (CS_PAGE_INDEX1+50)
#define CS_REG_SAMPLECOUNT        (CS_PAGE_INDEX1+51)
#define CS_REG_PMIN         (CS_PAGE_INDEX1+56)
#define CS_REG_TSETTLE          (CS_PAGE_INDEX1+57)
#define CS_REG_LOADMIN          (CS_PAGE_INDEX1+58)
// Page 17
#define CS_REG_V1SAGDUR         (CS_PAGE_INDEX2+0)
#define CS_REG_I1OVERLEVEL        (CS_PAGE_INDEX2+5)
// Page 18
#define CS_REG_IZXLEVEL         (CS_PAGE_INDEX3+24)
#define CS_REG_PULSERATE        (CS_PAGE_INDEX3+28)
#define CS_REG_INTGAIN          (CS_PAGE_INDEX3+43)
#define CS_REG_VZXLEVEL         (CS_PAGE_INDEX3+58)
#define CS_REG_CYCLECOUNT       (CS_PAGE_INDEX3+62)
#define CS_REG_SCALE          (CS_PAGE_INDEX3+63)

// CS instruction definition
#define CS_INS_RESET          (0x01)
#define CS_INS_STANDBY          (0x02)
#define CS_INS_WAKEUP         (0x03)
#define CS_INS_SCONV          (0x14)
#define CS_INS_CCONV          (0x15)
#define CS_INS_HCONV          (0x18)
#define CS_INS_DC_OFFSET        (0x20)
#define CS_INS_AC_OFFSET        (0x30)
#define CS_INS_GAIN         (0x38)
#define CS_INS_I1         (0x01)
#define CS_INS_V1         (0x02)
#define CS_INS_I2         (0x03)
#define CS_INS_V2         (0x04)
#define CS_INS_ALL          (0x06)
// CS5480 Macro Definition End

#define START_SINGLE_CPNVERT    0xE0
#define START_MULTI_CONVERT     0xE8
#define SYNC0           0xFE
#define SYNC1           0xFF
#define POWER_UP_HALT_CONTROL   0xA0
#define POWER_DOWN_MODE_0     0x80
#define POWER_DOWN_MODE_1     0x88
#define POWER_DOWN_MODE_2     0x90
#define POWER_DOWN_MODE_3     0x98
#define CALIBRATE_CONTROL     0xC0
// commands for calibrate control
#define CALIBRATE_CURRENT     0x08
#define CALIBRATE_VOLTAGE     0x10
#define CALIBRATE_CURRENT_VOLTAGE 0x18
#define CALIBRATE_GAIN        0x02
#define CALIBRATE_OFFSET      0x01
#define CALIBRATE_ALL       0x1B

#define CONFIG_REGISTER       (0x00<<1)
#define CURRENT_OFFSET_REGISTER   (0x01<<1)
#define CURRENT_GAIN_REGISTER   (0x02<<1)
#define VOLTAGE_OFFSET_REGISTER   (0x03<<1)
#define VOLTAGE_GAIN_REGISTER   (0x04<<1)
#define CYCLE_COUNT_REGISTER    (0x05<<1)
#define PULSE_RATE_REGISTER     (0x06<<1)
#define LAST_CURRENT_REGISTER   (0x07<<1)
#define LAST_VOLTAGE_REGISTER   (0x08<<1)
#define LAST_POWER_REGISTER     (0x09<<1)
#define TOTAL_ENERGY_REGISTER   (0x0A<<1)
#define RMS_CURRENT_REGISTER    (0x0B<<1)
#define RMS_VOLTAGE_REGISTER    (0x0C<<1)
#define TIME_BASE_CALI_REGISTER   (0x0D<<1)
#define STATUS_REGISTER       (0x0F<<1)
#define INTERRUPT_MASK_REGISTER   (0x1A<<1)

// command for configuration register
#define DIVIDE_K_1          (0x01L<<0)
#define DIVIDE_K_2          (0x01L<<1)
#define DIVIDE_K_4          (0x01L<<2)
#define INVERT_CPUCLK       (0x01L<<4)
#define ENABLE_CURRENT_HPF      (0x01L<<5)
#define ENABLE_VOLTAGE_HPF      (0x01L<<6)
#define CHIP_RESET          (0x01L<<7)
#define EDIR_VALUE          (0x01L<<8)
#define EOUT_VALUE          (0x01L<<9)
#define ENABLE_OUTPUT_DEFINE    (0x01L<<10)
#define SOFT_INT_LOW        (0x00L<<11)
#define SOFT_INT_HIGH       (0x01L<<11)
#define SOFT_INT_FALING       (0x02L<<11)
#define SOFT_INT_RASING       (0x03L<<11)
#define PHASE0            (0x00L<<13)
#define PHASE1            (0x01L<<13)
#define PHASE2            (0x02L<<13)
#define PHASE3            (0x03L<<13)
#define ENABLE_WIRE_AND       (0x01L<<15)
#define CURRENT_GAIN_10       (0x00L<<16)
#define CURRENT_GAIN_50       (0x01L<<16)

// status flag
#define INVVLID_COMMAND       (0x01L<<0)
#define LOW_SUPPLY          (0x01L<<2)
#define CURRENT_OSCILLATION     (0x01L<<3)
#define VOLTAGE_OSCILLATION     (0x01L<<4)
#define WATCH_DOG         (0x01L<<5)
#define EOUT_OUT_OF_RANGE     (0x01L<<11)
#define ENERGY_OUT_OF_RANGE     (0x01L<<12)
#define VRMS_OUT_OF_RANGE     (0x01L<<13)
#define IRMS_OUT_OF_RANGE     (0x01L<<14)
#define POWER_OUT_OF_RANGE      (0x01L<<15)
#define VOLTAGE_OUT_OF_RANGE    (0x01L<<16)
#define CURRENT_OUT_OF_RANGE    (0x01L<<17)
#define MATH_ERROR          (0x01L<<19)
#define NEGATIVE_ENERGY       (0x01L<<21)
#define ENERGY_OUTPUT       (0x01L<<22)
#define DATA_READY          (0x01L<<23)

#define PIN_NDEFINED        0xff

#define WRITE_REGISTER        0x40
#define READ_REGISTER       (~WRITE_REGISTER)

#define SIGNED_OUTPUT_MAX     (~0UL>>9)
#define UNSIGNED_OUTPUT_MAX     (~0UL>>8)
#define SIGN_BIT          (1L << 23)

//#define SETTING           SPISettings(2000000L, MSBFIRST, SPI_MODE0)200000
#define SETTING           SPISettings(200000L, MSBFIRST, SPI_MODE3)

union int32Data
{
  uint32_t data32;
  uint8_t data8[4];
};

class CS5480
{
private:
  uint8_t resetPin, edirPin, eoutPin, csPin;
  double currentGain, voltageGain, powerGain;
  uint32_t clkFreq,meaFreq;

  double signed2float(int32_t data);
  double unsigned2float(uint32_t data);
public:
  CS5480();
  CS5480(uint8_t _cs,uint8_t _reset = PIN_NDEFINED, uint8_t _edir = PIN_NDEFINED, uint8_t _eout = PIN_NDEFINED);
  void begin(uint8_t _cs,uint8_t _reset = PIN_NDEFINED, uint8_t _edir = PIN_NDEFINED, uint8_t _eout = PIN_NDEFINED);
  void init() const;
  void initcs5480();
  uint32_t readRegister(uint8_t reg) const;
  uint32_t readRegister5480(uint8_t reg) const;
  void writeRegister(uint8_t reg, uint32_t cmd) const;
  void writeRegister5480(uint8_t reg, uint32_t cmd) const;
  void clearStatus(uint32_t cmd);
  void startSingleConvert();
  void startMultiConvert();
  void resetChip() const;
  double getCurrent();
  uint32_t getRawCurrent(int chan);
  double getVoltage();
  uint32_t getRawVoltage();
  double getPower();
  uint32_t getRawPower(int chan);
  double getEnergy();
  uint32_t getRawEnergy();
  uint32_t getRawRPower(int chan);
  double getRMSCurrent();
  uint32_t getRawRMSCurrent();
  double getRMSVoltage();
  uint32_t getRawRMSVoltage();
  double getApparentPower();
  double getPowerFactor();
  uint32_t getRawPowerFactor(int chan);
  uint32_t getRawTemperature();
  uint32_t getStatus();
  void send(uint8_t cmd);
  void send5480(uint8_t cmd);
  void select() const;
  void unselect() const;
  void setCurrentGain(double gain);
  void setVoltageGain(double gain);
  void calibrate(uint8_t cmd);
  uint32_t calibrateVoltageOffset();
  uint32_t calibrateVoltageGain();
  uint32_t calibrateCurrentOffset();
  uint32_t calibrateCurrentGain();
  void setFrequency(uint32_t freq);
  void setMeasureFrequency(uint32_t freq);
};

#endif //__CS5460_H__
