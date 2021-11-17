/**************************************************************************/
/*!
    @file     Adafruit_MCP4726.h
*/
/**************************************************************************/

#ifndef _ADAFRUIT_MCP4726_H_
#define _ADAFRUIT_MCP4726_H_

#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Wire.h>

#define MCP4726_I2CADDR_DEFAULT (0x60) ///< Default i2c address for the MCP4726.
#define MCP4726_CMD_WRITEDAC (0x40)    ///< Writes data to the DAC
#define MCP4726_CMD_WRITEDACEEPROM (0x60) ///< Writes data to the DAC and the EEPROM (persisting the assigned value after reset)


// new definitions for MCP4726 specific commands
#define MCP4726_CMD_VREF_VDD (0x00)
#define MCP4726_CMD_VREF_VREFPIN (0x10)
#define MCP4726_CMD_VREF_VREFPIN_BUFFERED (0x18)
#define MCP4726_GAIN_1X (0x00)
#define MCP4726_GAIN_2x (0x01)

/**************************************************************************/
/*!
    @brief  Class for communicating with an MCP4726 DAC
*/
/**************************************************************************/
class Adafruit_MCP4726 {
public:
  Adafruit_MCP4726();
  bool begin(uint8_t i2c_address = MCP4726_I2CADDR_DEFAULT,
             TwoWire *wire = &Wire);
  bool setVoltage(uint16_t output, bool writeEEPROM,
                  uint32_t dac_frequency = 400000);

private:
  Adafruit_I2CDevice *i2c_dev = NULL;
};

#endif
