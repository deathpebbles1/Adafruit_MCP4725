

/*****************************************/
//Libraries!//

#include <Adafruit_MCP4726.h>
#include <Wire.h>


/*******************************************/
Adafruit_MCP4726 dac; // creates the dac class. "dac" is the name you'll use in the rest of the code.


void setup() {
 dac.begin(0x60); // sets the i2c address. Most MCP4726's use 0x60 as their default, but yours may be different.
 dac.setConfig(VREF_VREFPIN, GAIN_1X); // sets the config bits. VREF can be "VREF_VDD", "VREF_VREFPIN", or "VREF_VREFPIN_BUFFERED". Gain can be set to either "GAIN_1X" or "GAIN_2X".
 
 dac.setVoltage(0, true);              // sends a command to write your config to EEPROM as well as set the dac voltage to 0. 
                                       // Whatever you set the dac to here, will be what the dac outputs upon startup.

}

/*****************************************/

/*VREF selection chooses where your dac gets its voltage reference from. VREF_VDD uses the supply voltage, VREF_VREFPIN uses the dedicated VREF pin,
and VREF_VREFPIN_BUFFERED uses the same dedicated VREF pin, but also uses an internal buffering amplifier. Useful for high impedence voltage ref sources.
Using the buffer adds additional error due to the amplifier having offsets.

Unbuffered impedence is around 210 kohm, with roughly 29 pF of capacitance.
The GAIN selection changes only if you're using the dedicated VREF pin. Using a gain of 1x is self explanatory. Gain of 2x, multiplies your input voltage reference
by two. 
*/

/*******************************************/

void loop() {
  
  dac.setVoltage(4095, false);
  delay(100);
  dac.setVoltage(2094, false);          // Sets the dac to start at full output, then mid, then lowest. 
  delay(100);
  dac.setVoltage(0, false);

}
