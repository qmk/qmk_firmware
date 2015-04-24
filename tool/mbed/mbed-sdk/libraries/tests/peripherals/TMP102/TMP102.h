#ifndef TMP102_H
#define TMP102_H

#include "mbed.h"

//!Library for the TI TMP102 temperature sensor.
/*!
The TMP102 is an I2C digital temperature sensor in a small SOT563 package, with a 0.0625C resolution and 0.5C accuracy.
*/
class TMP102
{
public:
  //!Creates an instance of the class.
  /*!
  Connect module at I2C address addr using I2C port pins sda and scl.
  TMP102
  \param addr <table><tr><th>A0 pin connection</th><th>Address</th></tr><tr><td>GND</td><td>0x90</td></tr><tr><td>V+</td><td>0x92</td></tr><tr><td>SDA</td><td>0x94</td></tr><tr><td>SCL</td><td>0x96</td></tr></table>
  */
  TMP102(PinName sda, PinName scl, int addr);

  /*!
  Destroys instance.
  */
  ~TMP102();

  //!Reads the current temperature.
  /*!
  Reads the temperature register of the TMP102 and converts it to a useable value.
  */
  float read();

  I2C m_i2c;

private:
  int m_addr;

};

#endif
