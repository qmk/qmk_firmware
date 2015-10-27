/* IUSBHostSerial.h */
/* Copyright (c) 2010-2012 mbed.org, MIT License
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software
* and associated documentation files (the "Software"), to deal in the Software without
* restriction, including without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or
* substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
* BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef IUSBHOSTSERIAL_H_
#define IUSBHOSTSERIAL_H_

/**
 * Generic interface to abstract 3G dongles' impl
 */

#include "USBHostConf.h"

#ifdef USBHOST_3GMODULE

#include "IUSBHostSerialListener.h"

// This is needed by some versions of GCC
#undef putc
#undef getc

class IUSBHostSerial {
public:

    enum IrqType {
        RxIrq,
        TxIrq
    };

    /*
    * Get a char from the dongle's serial interface
    */
    virtual int getc() = 0;

    /*
    * Put a char to the dongle's serial interface
    */
    virtual int putc(int c) = 0;

    /*
     *  Read a packet from the dongle's serial interface, to be called after multiple getc() calls
     */
    virtual int readPacket() = 0;

    /*
     *  Write a packet to the dongle's serial interface, to be called after multiple putc() calls
     */
    virtual int writePacket() = 0;

    /**
    * Check the number of bytes available.
    *
    * @returns the number of bytes available
    */
    virtual int readable() = 0;

    /**
    * Check the free space in output.
    *
    * @returns the number of bytes available
    */
    virtual int writeable() = 0;

    /**
     *  Attach a handler to call when a packet is received / when a packet has been transmitted.
     *
     *  @param pListener instance of the listener deriving from the IUSBHostSerialListener
     */
    virtual void attach(IUSBHostSerialListener* pListener) = 0;

    /**
     * Enable or disable readable/writeable callbacks
     */
    virtual void setupIrq(bool en, IrqType irq = RxIrq) = 0;

};

#endif /* USBHOST_3GMODULE */

#endif /* IUSBHOSTSERIAL_H_ */
