/* mbed Microcontroller Library - SPIHalfDuplex
 * Copyright (c) 2010-2011 ARM Limited. All rights reserved.
 */
#ifndef MBED_SPIHALFDUPLEX_H
#define MBED_SPIHALFDUPLEX_H

#include "platform.h"

#if DEVICE_SPI

#include "SPI.h"

namespace mbed {

/** A SPI half-duplex master, used for communicating with SPI slave devices
 * over a shared data line.
 *
 * The default format is set to 8-bits for both master and slave, and a
 * clock frequency of 1MHz
 *
 * Most SPI devies will also require Chip Select and Reset signals. These
 * can be controlled using <DigitalOut> pins.
 *
 * Although this is for a shared data line, both MISO and MOSI are defined,
 * and should be tied together externally to the mbed. This class handles
 * the tri-stating of the MOSI pin.
 *
 * Example:
 * @code
 * // Send a byte to a SPI half-duplex slave, and record the response
 *
 * #include "mbed.h"
 *
 * SPIHalfDuplex device(p5, p6, p7) // mosi, miso, sclk
 *
 * int main() {
 *     int respone = device.write(0xAA);
 * }
 * @endcode
 */

class SPIHalfDuplex : public SPI {

public:

    /** Create a SPI half-duplex master connected to the specified pins
     *
     * Pin Options:
     *  (5, 6, 7) or (11, 12, 13)
     *
     *  mosi or miso can be specfied as NC if not used
     *
     *  @param mosi SPI Master Out, Slave In pin
     *  @param miso SPI Master In, Slave Out pin
     *  @param sclk SPI Clock pin
     *  @param name (optional) A string to identify the object
     */
    SPIHalfDuplex(PinName mosi, PinName miso, PinName sclk);

    /** Write to the SPI Slave and return the response
     *
     *  @param value Data to be sent to the SPI slave
     *
     *  @returns
     *    Response from the SPI slave
     */
    virtual int write(int value);

    /** Set the number of databits expected from the slave, from 4-16
     *
     *  @param sbits Number of expected bits in the slave response
     */
    void slave_format(int sbits);

protected:
    PinName _mosi;
    PinName _miso;
    int     _sbits;
}; // End of class

} // End of namespace mbed

#endif

#endif
