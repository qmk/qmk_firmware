
/*
Copyright (c) 2010 Chris Styles ( chris dot styles at mbed dot org )

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

#include "SRF08.h"


SRF08::SRF08(PinName sda, PinName scl, int addr) : m_i2c(sda, scl), m_addr(addr) {
    char cmd[2];

// Set up SRF08 max range and receiver sensitivity over I2C bus
    cmd[0] = 0x02;                          // Range register
    cmd[1] = 0x1C;                          // Set max range about 100cm
    m_i2c.write(m_addr, cmd, 2);
    cmd[0] = 0x01;                          // Receiver gain register
    cmd[1] = 0x1B;                          // Set max receiver gain
    m_i2c.write(m_addr, cmd, 2);

}

SRF08::~SRF08() {

}

float SRF08::read() {

    char cmd[2];
    char echo[2];


// Get range data from SRF08
// Send Tx burst command over I2C bus
    cmd[0] = 0x00;                      // Command register
    cmd[1] = 0x51;                      // Ranging results in cm
    m_i2c.write(m_addr, cmd, 2);          // Send ranging burst

    wait(0.07);                         // Wait for return echo

// Read back range over I2C bus
    cmd[0] = 0x02;                        // Address of first echo
    m_i2c.write(m_addr, cmd, 1, 1);         // Send address of first echo
    m_i2c.read(m_addr, echo, 2);            // Read two-byte echo result

// Generate PWM mark/space ratio from range data
    float range = (echo[0]<<8)+echo[1];

    return range;
}
