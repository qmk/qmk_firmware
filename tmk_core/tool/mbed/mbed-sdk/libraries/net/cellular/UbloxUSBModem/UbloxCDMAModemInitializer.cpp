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

#define __DEBUG__ 4
#ifndef __MODULE__
#define __MODULE__ "UbloxCDMAModemInitializer.cpp"
#endif

#include "core/dbg.h"

#include <stdint.h>

#include "UbloxCDMAModemInitializer.h"

UbloxCDMAModemInitializer::UbloxCDMAModemInitializer(USBHost* pHost) : WANDongleInitializer(pHost)
{
}

uint16_t UbloxCDMAModemInitializer::getMSDVid()
{
    return 0x05C6;
}
uint16_t UbloxCDMAModemInitializer::getMSDPid()
{
    return 0x0000;    //No MSD mode (presumably)
}

uint16_t UbloxCDMAModemInitializer::getSerialVid()
{
    return 0x05C6;
}
uint16_t UbloxCDMAModemInitializer::getSerialPid()
{
    return 0x9004;
}

bool UbloxCDMAModemInitializer::switchMode(USBDeviceConnected* pDev)
{
    return true;
}

int UbloxCDMAModemInitializer::getSerialPortCount()
{
    return 2;
}

/*virtual*/ void UbloxCDMAModemInitializer::setVidPid(uint16_t vid, uint16_t pid)
{
    m_currentSerialIntf = 0;
    m_currentEndpoint = 0;
}

/*virtual*/ bool UbloxCDMAModemInitializer::parseInterface(uint8_t intf_nb, uint8_t intf_class, uint8_t intf_subclass, uint8_t intf_protocol) //Must return true if the interface should be parsed
{
    DBG("Interface #%d; Class:%02x; SubClass:%02x; Protocol:%02x", intf_nb, intf_class, intf_subclass, intf_protocol);

    if( intf_class == 0xFF ) {
        if( m_currentSerialIntf == 0 || m_currentSerialIntf == 1) {
            m_serialIntfMap[m_currentSerialIntf++] = intf_nb;
            return true;
        }
        m_currentSerialIntf++;
    }

    return false;
}

/*virtual*/ bool UbloxCDMAModemInitializer::useEndpoint(uint8_t intf_nb, ENDPOINT_TYPE type, ENDPOINT_DIRECTION dir) //Must return true if the endpoint will be used
{
    DBG("USBEndpoint on Interface #%d; Type:%d; Direction:%d Current %d", intf_nb, type, dir, m_currentEndpoint);
    if(type == BULK_ENDPOINT) {
        if( intf_nb == 1 || intf_nb == 0) {
            m_currentEndpoint++;
            return true;
        } else {
            m_currentEndpoint++;
        }
    }

		/*
    if(type == INTERRUPT_ENDPOINT) {
        if( intf_nb == 1) {
            m_currentEndpoint++;
            return true;
        } else {
            m_currentEndpoint++;
        }
    }
		*/
		
    return false;
}


/*virtual*/ int UbloxCDMAModemInitializer::getType()
{
    return WAN_DONGLE_TYPE_UBLOX_LISAC200;
}

