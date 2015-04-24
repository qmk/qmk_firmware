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

#ifndef WANDONGLE_H
#define WANDONGLE_H

#include "USBHostConf.h"

#ifdef USBHOST_3GMODULE

#include "USBHost.h"
#include "IUSBHostSerial.h"

#include "rtos.h"

#include "WANDongleSerialPort.h"
#include "WANDongleInitializer.h"
#include "IUSBEnumerator.h"

#define WANDONGLE_MAX_OUTEP_SIZE 64
#define WANDONGLE_MAX_INEP_SIZE 64

/** A class to use a WAN (3G/LTE) access dongle
 *
 */
class WANDongle : public IUSBEnumerator {
public:
    /*
    * Constructor
    *
    * @param rootdir mount name
    */
    WANDongle();

    /*
    * Destructor
    */
    virtual ~WANDongle();

    /*
    * Check if a serial port device is connected
    *
    * @return true if a serial device is connected
    */
    bool connected();

    /*
     * Try to connect device
     *
     * * @return true if connection was successful
     */
    bool tryConnect();

    /*
     * Disconnect device
     *
     * * @return true if disconnection was successful
     */
    bool disconnect();

    int getDongleType();

    IUSBHostSerial& getSerial(int index);
    int getSerialCount();
    bool addInitializer(WANDongleInitializer* pInitializer);

    //From IUSBEnumerator

    virtual void setVidPid(uint16_t vid, uint16_t pid);

    virtual bool parseInterface(uint8_t intf_nb, uint8_t intf_class, uint8_t intf_subclass, uint8_t intf_protocol); //Must return true if the interface should be parsed

    virtual bool useEndpoint(uint8_t intf_nb, ENDPOINT_TYPE type, ENDPOINT_DIRECTION dir); //Must return true if the endpoint will be used

protected:
    USBHost * host;
    USBDeviceConnected * dev;
    bool dev_connected;

    WANDongleInitializer* m_pInitializer;

    void init();

    WANDongleSerialPort m_serial[WANDONGLE_MAX_SERIAL_PORTS];
    int m_serialCount;

    int m_totalInitializers;
    WANDongleInitializer* m_Initializers[WANDONGLE_MAX_INITIALIZERS];
};

#endif /* USBHOST_3GMODULE */

#endif
