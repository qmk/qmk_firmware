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

#ifndef UBLOXCDMAMODEMINITIALIZER_H
#define UBLOXCDMAMODEMINITIALIZER_H

#include <stdint.h>

#include "WANDongleInitializer.h"
#include "USBHost.h"
#include "IUSBEnumerator.h"

enum
{
  WAN_DONGLE_TYPE_UBLOX_LISAC200 = 0xC200,
};

class UbloxCDMAModemInitializer : public WANDongleInitializer
{
public:
    UbloxCDMAModemInitializer(USBHost* pHost);
    
    virtual uint16_t getMSDVid();
    virtual uint16_t getMSDPid();
    
    virtual uint16_t getSerialVid();
    virtual uint16_t getSerialPid();
    
    virtual bool switchMode(USBDeviceConnected* pDev);
    
    virtual int getSerialPortCount();
    
    virtual void setVidPid(uint16_t vid, uint16_t pid);
    
    virtual bool parseInterface(uint8_t intf_nb, uint8_t intf_class, uint8_t intf_subclass, uint8_t intf_protocol); //Must return true if the interface should be parsed
    
    virtual bool useEndpoint(uint8_t intf_nb, ENDPOINT_TYPE type, ENDPOINT_DIRECTION dir); //Must return true if the endpoint will be used
    
    virtual int getType();
    
private:

  int m_currentSerialIntf;
  int m_currentEndpoint;
};

#endif

