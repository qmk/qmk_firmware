
/*
Copyright (c) 2010 Chris Styles (chris dot styles at mbed dot org)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef SRF08_H
#define SRF08_H

#include "mbed.h"

//!Library for the SRF08 Ultrasonic Ranger
/*!
The SRF08 is an Ultrasonic range finder, with an I2C interface that allows the measurement to be read directly in centimetres
*/
class SRF08
{
public:
  //!Creates an instance of the class.
  /*!
  Connect module at I2C address addr using I2C port pins sda and scl.
  SRF08
  */
  SRF08(PinName sda, PinName scl, int addr);

  /*!
  Destroys instance.
  */
  ~SRF08();

  //!Reads the current temperature.
  /*!
  Reads the temperature register of the TMP102 and converts it to a useable value.
  */
  float read();

private:
  I2C m_i2c;
  int m_addr;

};

#endif
