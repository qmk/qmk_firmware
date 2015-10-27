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

#ifndef WANDONGLESERIALPORT_H
#define WANDONGLESERIALPORT_H

#include "USBHostConf.h"

#ifdef USBHOST_3GMODULE

#include "USBHost.h"
#include "IUSBHostSerial.h"

#include "rtos.h"


#define WANDONGLE_MAX_OUTEP_SIZE 64
#define WANDONGLE_MAX_INEP_SIZE 64

/** A class to use a WAN (3G/LTE) access dongle
 *
 */
class WANDongleSerialPort : public IUSBHostSerial {
public:
    /*
    * Constructor
    *
    */
    WANDongleSerialPort();

    void init( USBHost* pHost );

    void connect( USBDeviceConnected* pDev, USBEndpoint* pInEp, USBEndpoint* pOutEp );

    void disconnect( );

    /*
    * Get a char from the dongle's serial interface
    */
    virtual int getc();

    /*
    * Put a char to the dongle's serial interface
    */
    virtual int putc(int c);

    /*
     *  Read a packet from the dongle's serial interface, to be called after multiple getc() calls
     */
    virtual int readPacket();

    /*
     *  Write a packet to the dongle's serial interface, to be called after multiple putc() calls
     */
    virtual int writePacket();

    /**
    * Check the number of bytes available.
    *
    * @returns the number of bytes available
    */
    virtual int readable();

    /**
    * Check the free space in output.
    *
    * @returns the number of bytes available
    */
    virtual int writeable();

    /**
     *  Attach a handler to call when a packet is received / when a packet has been transmitted.
     *
     *  @param pListener instance of the listener deriving from the IUSBHostSerialListener
     */
    virtual void attach(IUSBHostSerialListener* pListener);

    /**
     * Enable or disable readable/writeable callbacks
     */
    virtual void setupIrq(bool en, IrqType irq = RxIrq);


protected:
    USBEndpoint * bulk_in;
    USBEndpoint * bulk_out;
    USBHost * host;
    USBDeviceConnected * dev;

    uint8_t buf_out[WANDONGLE_MAX_OUTEP_SIZE];
    volatile uint32_t buf_out_len;
    uint32_t max_out_size;
    volatile bool lock_tx;
    volatile bool cb_tx_en;
    volatile bool cb_tx_pending;
    Mutex tx_mtx;

    uint8_t buf_in[WANDONGLE_MAX_INEP_SIZE];
    volatile uint32_t buf_in_len;
    volatile uint32_t buf_in_read_pos;
    volatile bool lock_rx;
    volatile bool cb_rx_en;
    volatile bool cb_rx_pending;
    Mutex rx_mtx;

    IUSBHostSerialListener* listener;

    void reset();

    void rxHandler();
    void txHandler();

};

#endif /* USBHOST_3GMODULE */

#endif

