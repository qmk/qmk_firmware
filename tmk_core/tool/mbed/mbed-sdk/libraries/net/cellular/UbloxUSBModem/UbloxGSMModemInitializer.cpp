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

#include "UbloxGSMModemInitializer.h"
#include "core/dbg.h"

#define __DEBUG__ 0
#ifndef __MODULE__
#define __MODULE__ "UbloxGSMModemInitializer.cpp"
#endif

//-----------------------------------------------------------------------
// mamm, u-blox Modem
//-----------------------------------------------------------------------

UbloxGSMModemInitializer::UbloxGSMModemInitializer(USBHost* pHost) : WANDongleInitializer(pHost)
{
  
}

uint16_t UbloxGSMModemInitializer::getMSDVid()      { return 0x1546; }
uint16_t UbloxGSMModemInitializer::getMSDPid()      { return 0x0000; }

uint16_t UbloxGSMModemInitializer::getSerialVid()   { return 0x1546; }
uint16_t UbloxGSMModemInitializer::getSerialPid()   { return 0x1102; }

bool UbloxGSMModemInitializer::switchMode(USBDeviceConnected* pDev)
{
  for (int i = 0; i < pDev->getNbIntf(); i++)
  {
    if (pDev->getInterface(i)->intf_class == MSD_CLASS)
    {
      USBEndpoint* pEp = pDev->getEndpoint(i, BULK_ENDPOINT, OUT);
      if ( pEp != NULL ) 
      {
        ERR("MSD descriptor found on device %p, intf %d", (void *)pDev, i);
      }
    }  
  }
  return false;
}

#define UBX_SERIALCOUNT 7 

int UbloxGSMModemInitializer::getSerialPortCount()
{
  return UBX_SERIALCOUNT;
}

/*virtual*/ void UbloxGSMModemInitializer::setVidPid(uint16_t vid, uint16_t pid)
{
    if( (vid == getSerialVid() ) && ( pid == getSerialPid() ) )
    {
      m_hasSwitched = true;
      m_currentSerialIntf = 0;
      m_endpointsToFetch = UBX_SERIALCOUNT*2;
    }
    else
    {
      m_hasSwitched = false;
      m_endpointsToFetch = 1;
    }
}

/*virtual*/ bool UbloxGSMModemInitializer::parseInterface(uint8_t intf_nb, uint8_t intf_class, uint8_t intf_subclass, uint8_t intf_protocol) //Must return true if the interface should be parsed
{
  if( m_hasSwitched )
  {
    DBG("Interface #%d; Class:%02x; SubClass:%02x; Protocol:%02x", intf_nb, intf_class, intf_subclass, intf_protocol);
    if( intf_class == 0x0A )
    {
      if( (m_currentSerialIntf == 0) || (m_currentSerialIntf == 1) )
      {
        m_serialIntfMap[m_currentSerialIntf++] = intf_nb;
        return true;
      }
      m_currentSerialIntf++;
    }
  }
  else
  {
    if( (intf_nb == 0) && (intf_class == MSD_CLASS) )
    {
      return true;
    }
  }
  return false;
}

/*virtual*/ bool UbloxGSMModemInitializer::useEndpoint(uint8_t intf_nb, ENDPOINT_TYPE type, ENDPOINT_DIRECTION dir) //Must return true if the endpoint will be used
{
  if( m_hasSwitched )
  {
    DBG("USBEndpoint on Interface #%d; Type:%d; Direction:%d", intf_nb, type, dir);
    if( (type == BULK_ENDPOINT) && m_endpointsToFetch )
    {
      m_endpointsToFetch--;
      return true;
    }
  }
  else
  {
    if( (type == BULK_ENDPOINT) && (dir == OUT) && m_endpointsToFetch )
    {
      m_endpointsToFetch--;
      return true;
    }
  }
  return false;
}

/*virtual*/ int UbloxGSMModemInitializer::getType()
{
  return WAN_DONGLE_TYPE_UBLOX_LISAU200;
}

