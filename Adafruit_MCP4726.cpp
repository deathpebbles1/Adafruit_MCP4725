/**************************************************************************/
/*!
    @file     Adafruit_MCP4726.cpp
    @author   K.Townsend (Adafruit Industries)
    @edited by J. Bin

        I2C Driver for Microchip's MCP4726 I2C DAC

        This is a modified library for the MCP4726 breakout, based off of the original adafruit MCP4725 library, for thier breakout board linked below.
        ----> http://www.adafruit.com/products/935

        Adafruit invests time and resources providing this open source code,
        please support Adafruit and open-source hardware by purchasing
        products from Adafruit!

        @section  HISTORY

*/
/**************************************************************************/

#include "Adafruit_MCP4726.h"

/**************************************************************************/
/*!
    @brief  Instantiates a new MCP4726 class
*/
/**************************************************************************/
Adafruit_MCP4726::Adafruit_MCP4726() {}

/**************************************************************************/
/*!
    @brief  Setups the hardware and checks the DAC was found
    @param i2c_address The I2C address of the DAC, defaults to 0x60
    @param wire The I2C TwoWire object to use, defaults to &Wire
    @returns True if DAC was found on the I2C address.
*/
/**************************************************************************/
bool Adafruit_MCP4726::begin(uint8_t i2c_address, TwoWire *wire) {
  if (i2c_dev) {
    delete i2c_dev;
  }

  i2c_dev = new Adafruit_I2CDevice(i2c_address, wire);

  if (!i2c_dev->begin()) {
    return false;
  }

  return true;
}


/**************************************************************************/
/*!
    @param i2c_frequency What we should set the I2C clock to when writing
    to the DAC, defaults to 400 KHz. 
    @param[in] Vref 
    Selected voltage reference source. Can choose between VDD 9(aka, supply voltage),
    Vref pin, or use the VRef pin with a buffer. Buffer is good for high impedence
    voltage reference sources.
    @returns True if DAC was found on the I2C address.
*/
/**************************************************************************/ 
bool Adafruit_MCP4726::setConfig(uint8_t Vref, uint8_t gain, uint32_t i2c_frequency){
    i2c_dev->setSpeed(i2c_frequency);
    config = (Vref | gain);

    uint8_t packet[1];
    
    packet[0] = (MCP4726_CMD_WRITECONFIG | config);
    
    if (!i2c_dev->write(packet, 1)) {
    return false;
  }
  i2c_dev->setSpeed(100000); // reset to arduino default
  return true;
}


/**************************************************************************/
/*!
    @brief  Sets the output voltage to a fraction of source vref.  (Value
            can be 0..4095)

    @param[in]  output
                The 12-bit value representing the relationship between
                the DAC's input voltage and its output voltage.
    @param[in]  writeEEPROM
                If this value is true, 'output' will also be written
                to the MCP4726's internal non-volatile memory, meaning
                that the DAC will retain the current voltage output
                after power-down or reset.
    @param i2c_frequency What we should set the I2C clock to when writing
    to the DAC, defaults to 400 KHz
    @returns True if able to write the value over I2C
*/
/**************************************************************************/
bool Adafruit_MCP4726::setVoltage(uint16_t output, bool writeEEPROM,
                                  uint32_t i2c_frequency) {
  i2c_dev->setSpeed(i2c_frequency); // Set I2C frequency to desired speed

  uint8_t packet[3];

  if (writeEEPROM) {
    packet[0] = (MCP4726_CMD_WRITEDACEEPROM | config);
  } else {
    packet[0] = (MCP4726_CMD_WRITEDAC | config);
  }
  packet[1] = output / 16;        // Upper data bits (D11.D10.D9.D8.D7.D6.D5.D4)
  packet[2] = (output % 16) << 4; // Lower data bits (D3.D2.D1.D0.x.x.x.x)

  if (!i2c_dev->write(packet, 3)) {
    return false;
  }

  i2c_dev->setSpeed(100000); // reset to arduino default
  return true;
}
