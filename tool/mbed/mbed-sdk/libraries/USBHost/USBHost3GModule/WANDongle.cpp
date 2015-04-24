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

#include "USBHostConf.h"

#ifdef USBHOST_3GMODULE

#include "dbg.h"
#include <stdint.h>
#include "rtos.h"

#include "WANDongle.h"
#include "WANDongleInitializer.h"

WANDongle::WANDongle() : m_pInitializer(NULL), m_serialCount(0), m_totalInitializers(0)
{
    host = USBHost::getHostInst();
    init();
}


bool WANDongle::connected() {
  return dev_connected;
}

bool WANDongle::tryConnect()
{
  //FIXME should run on USB thread

  USB_DBG("Trying to connect device");

  if (dev_connected) {
      USB_DBG("Device is already connected!");
      return true;
  }

  m_pInitializer = NULL;

  //Protect from concurrent access from USB thread
  USBHost::Lock lock(host);

  for (int i = 0; i < MAX_DEVICE_CONNECTED; i++)
  {
      if ((dev = host->getDevice(i)) != NULL)
      {
          m_pInitializer = NULL; //Will be set in setVidPid callback

          USB_DBG("Enumerate");
          int ret = host->enumerate(dev, this);
          if(ret)
          {
            return false;
          }

          USB_DBG("Device has VID:%04x PID:%04x", dev->getVid(), dev->getPid());

          if(m_pInitializer) //If an initializer has been found
          {
            USB_DBG("m_pInitializer=%p", m_pInitializer);
            USB_DBG("m_pInitializer->getSerialVid()=%04x", m_pInitializer->getSerialVid());
            USB_DBG("m_pInitializer->getSerialPid()=%04x", m_pInitializer->getSerialPid());
            if ((dev->getVid() == m_pInitializer->getSerialVid()) && (dev->getPid() == m_pInitializer->getSerialPid()))
            {
              USB_DBG("The dongle is in virtual serial mode");
              host->registerDriver(dev, 0, this, &WANDongle::init);
              m_serialCount = m_pInitializer->getSerialPortCount();
              if( m_serialCount > WANDONGLE_MAX_SERIAL_PORTS )
              {
                m_serialCount = WANDONGLE_MAX_SERIAL_PORTS;
              }
              for(int j = 0; j < m_serialCount; j++)
              {
                USB_DBG("Connecting serial port #%d", j+1);
                USB_DBG("Ep %p", m_pInitializer->getEp(dev, j, false));
                USB_DBG("Ep %p", m_pInitializer->getEp(dev, j, true));
                m_serial[j].connect( dev, m_pInitializer->getEp(dev, j, false), m_pInitializer->getEp(dev, j, true) );
              }

              USB_DBG("Device connected");

              dev_connected = true;


              return true;
            }
            else if ((dev->getVid() == m_pInitializer->getMSDVid()) && (dev->getPid() == m_pInitializer->getMSDPid()))
            {
              USB_DBG("Vodafone K3370 dongle detected in MSD mode");
              //Try to switch
              if( m_pInitializer->switchMode(dev) )
              {
                USB_DBG("Switched OK");
                return false; //Will be connected on a next iteration
              }
              else
              {
                USB_ERR("Could not switch mode");
                return false;
              }
            }
          } //if()
      } //if()
  } //for()
  return false;
}

bool WANDongle::disconnect()
{
  dev_connected = false;
  for(int i = 0; i < WANDONGLE_MAX_SERIAL_PORTS; i++)
  {
    m_serial[i].disconnect();
  }
  return true;
}

int WANDongle::getDongleType()
{
  if( m_pInitializer != NULL )
  {
    return m_pInitializer->getType();
  }
  else
  {
    return WAN_DONGLE_TYPE_UNKNOWN;
  }
}

IUSBHostSerial& WANDongle::getSerial(int index)
{
  return m_serial[index];
}

int WANDongle::getSerialCount()
{
  return m_serialCount;
}

//Private methods
void WANDongle::init()
{
  m_pInitializer = NULL;
  dev_connected = false;
  for(int i = 0; i < WANDONGLE_MAX_SERIAL_PORTS; i++)
  {
    m_serial[i].init(host);
  }
}


/*virtual*/ void WANDongle::setVidPid(uint16_t vid, uint16_t pid)
{
  WANDongleInitializer* initializer;

  for(int i = 0; i < m_totalInitializers; i++)
  {
    initializer = m_Initializers[i];
    USB_DBG("initializer=%p", initializer);
    USB_DBG("initializer->getSerialVid()=%04x", initializer->getSerialVid());
    USB_DBG("initializer->getSerialPid()=%04x", initializer->getSerialPid());
    if ((dev->getVid() == initializer->getSerialVid()) && (dev->getPid() == initializer->getSerialPid()))
    {
      USB_DBG("The dongle is in virtual serial mode");
      m_pInitializer = initializer;
      break;
    }
    else if ((dev->getVid() == initializer->getMSDVid()) && (dev->getPid() == initializer->getMSDPid()))
    {
      USB_DBG("Dongle detected in MSD mode");
      m_pInitializer = initializer;
      break;
    }
    initializer++;
  } //for
  if(m_pInitializer)
  {
    m_pInitializer->setVidPid(vid, pid);
  }
}

/*virtual*/ bool WANDongle::parseInterface(uint8_t intf_nb, uint8_t intf_class, uint8_t intf_subclass, uint8_t intf_protocol) //Must return true if the interface should be parsed
{
  if(m_pInitializer)
  {
    return m_pInitializer->parseInterface(intf_nb, intf_class, intf_subclass, intf_protocol);
  }
  else
  {
    return false;
  }
}

/*virtual*/ bool WANDongle::useEndpoint(uint8_t intf_nb, ENDPOINT_TYPE type, ENDPOINT_DIRECTION dir) //Must return true if the endpoint will be used
{
  if(m_pInitializer)
  {
    return m_pInitializer->useEndpoint(intf_nb, type, dir);
  }
  else
  {
    return false;
  }
}


bool WANDongle::addInitializer(WANDongleInitializer* pInitializer)
{
  if (m_totalInitializers >= WANDONGLE_MAX_INITIALIZERS)
    return false;
  m_Initializers[m_totalInitializers++] = pInitializer;
  return true;
}

WANDongle::~WANDongle()
{
  for(int i = 0; i < m_totalInitializers; i++)
    delete m_Initializers[i];
}

#endif /* USBHOST_3GMODULE */
