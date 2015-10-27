/* UbloxUSBCDMAModem.cpp */
/* Copyright (C) 2012 mbed.org, MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
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
#define __MODULE__ "UbloxUSBCDMAModem.cpp"
#endif

#include "core/fwk.h"

#include "UbloxUSBCDMAModem.h"
#include "UbloxCDMAModemInitializer.h"
#include "USBHost.h"

#define USE_ONE_PORT 1

UbloxUSBCDMAModem::UbloxUSBCDMAModem(PinName powerGatingPin /*= NC*/, bool powerGatingOnWhenPinHigh /* = true*/, int serial /* 0 */) : m_dongle(),
m_stream(m_dongle.getSerial(serial)), 
m_at(&m_stream),
m_sms(&m_at), m_ppp(&m_stream),
m_dongleConnected(false), m_ipInit(false), m_smsInit(false), m_atOpen(false),
m_powerGatingPin(powerGatingPin), m_powerGatingOnWhenPinHigh(powerGatingOnWhenPinHigh)
{
  USBHost* host = USBHost::getHostInst();
  m_dongle.addInitializer(new UbloxCDMAModemInitializer(host));
  if( m_powerGatingPin != NC )
  {
    power(false); //Dongle will have to be powered on manually
  }
}

class CSSProcessor : public IATCommandsProcessor
{
public:
  CSSProcessor() : status(STATUS_REGISTERING)
  {

  }
  enum REGISTERING_STATUS { STATUS_REGISTERING, STATUS_OK };
  REGISTERING_STATUS getStatus()
  {
    return status;
  }
private:
  virtual int onNewATResponseLine(ATCommandsInterface* pInst, const char* line)
  {
    char b;
		char bc[3] = "";
		int sid = 99999; 
		
    //if( sscanf(line, "%*d, %c", &r) == 1 )
    if(sscanf(line, "%*s %c,%2s,%d", &b,bc,&sid)==3)
		{
				if(strcmp("Z", bc) == 0)
					status = STATUS_REGISTERING;
				else
					status = STATUS_OK;
    }
    return OK;
  }
  virtual int onNewEntryPrompt(ATCommandsInterface* pInst)
  {
    return OK;
  }
  volatile REGISTERING_STATUS status;
};

int UbloxUSBCDMAModem::connect(const char* apn, const char* user, const char* password)
{
  if( !m_ipInit )
  {
    m_ipInit = true;
    m_ppp.init();
  }
  m_ppp.setup(user, password, DEFAULT_MSISDN_CDMA);

  int ret = init();
  if(ret)
  {
    return ret;
  }

  #if USE_ONE_PORT
  m_smsInit = false; //SMS status reset
  //m_ussdInit = false; //USSD status reset
  //m_linkMonitorInit = false; //Link monitor status reset
  #endif

  ATCommandsInterface::ATResult result;

  if(apn != NULL)
  {
    char cmd[48];
    sprintf(cmd, "AT+CGDCONT=1,\"IP\",\"%s\"", apn);
    ret = m_at.executeSimple(cmd, &result);
    DBG("Result of command: Err code=%d", ret);
    DBG("ATResult: AT return=%d (code %d)", result.result, result.code);
    DBG("APN set to %s", apn);
  }


  //Connect
  DBG("Connecting");
  #if USE_ONE_PORT
  m_at.close(); // Closing AT parser
  m_atOpen = false; //Will need to be reinitialized afterwards
  #endif

  DBG("Connecting PPP");

  ret = m_ppp.connect();
  DBG("Result of connect: Err code=%d", ret);
  return ret;
}


int UbloxUSBCDMAModem::disconnect()
{
  DBG("Disconnecting from PPP");
  int ret = m_ppp.disconnect();
  if(ret)
  {
    ERR("Disconnect returned %d, still trying to disconnect", ret);
  }

  //Ugly but leave dongle time to recover
  Thread::wait(500);

  #if USE_ONE_PORT
  ATCommandsInterface::ATResult result;
  DBG("Starting AT thread");
  ret = m_at.open();
  if(ret)
  {
    return ret;
  }
  #endif

  DBG("Trying to hangup");

  #if 0 //Does not appear to work
  int tries = 10;
  do
  {
    ret = m_at.executeSimple("+++", &result, 1000);
    DBG("Result of command: Err code=%d\n", ret);
    DBG("ATResult: AT return=%d (code %d)\n", result.result, result.code);
  } while(tries-- && ret);
  if(!ret)
  {
    ret = m_at.executeSimple("ATH", &result);
    DBG("Result of command: Err code=%d\n", ret);
    DBG("ATResult: AT return=%d (code %d)\n", result.result, result.code);
  }
  #endif

  #if USE_ONE_PORT
  //Reinit AT parser
  ret = m_at.init();
  DBG("Result of command: Err code=%d\n", ret);
  if(ret)
  {
    m_at.close(); // Closing AT parser
    DBG("AT Parser closed, could not complete disconnection");
    return NET_TIMEOUT;
  }

  #if 0
  m_at.close(); // Closing AT parser
  DBG("AT Parser closed");
  #endif
  #endif
  return OK;
}

int UbloxUSBCDMAModem::sendSM(const char* number, const char* message)
{
  int ret = init();
  if(ret)
  {
    return ret;
  }

  if(!m_smsInit)
  {
    ret = m_sms.init();
    if(ret)
    {
      return ret;
    }
    m_smsInit = true;
  }

  ret = m_sms.send(number, message);
  if(ret)
  {
    return ret;
  }

  return OK;
}

int UbloxUSBCDMAModem::getSM(char* number, char* message, size_t maxLength)
{
  int ret = init();
  if(ret)
  {
    return ret;
  }

  if(!m_smsInit)
  {
    ret = m_sms.init();
    if(ret)
    {
      return ret;
    }
    m_smsInit = true;
  }

  ret = m_sms.get(number, message, maxLength);
  if(ret)
  {
    return ret;
  }

  return OK;
}

int UbloxUSBCDMAModem::getSMCount(size_t* pCount)
{
  int ret = init();
  if(ret)
  {
    return ret;
  }

  if(!m_smsInit)
  {
    ret = m_sms.init();
    if(ret)
    {
      return ret;
    }
    m_smsInit = true;
  }

  ret = m_sms.getCount(pCount);
  if(ret)
  {
    return ret;
  }

  return OK;
}

ATCommandsInterface* UbloxUSBCDMAModem::getATCommandsInterface()
{
  return &m_at;
}

int UbloxUSBCDMAModem::power(bool enable)
{
  if( m_powerGatingPin == NC )
  {
    return NET_INVALID; //A pin name has not been provided in the constructor
  }

  if(!enable) //Will force components to re-init
  {
    cleanup();
  }
  
  DigitalOut powerGatingOut(m_powerGatingPin);
  powerGatingOut = m_powerGatingOnWhenPinHigh?enable:!enable;

  return OK;
}

bool UbloxUSBCDMAModem::power()
{
  if( m_powerGatingPin == NC )
  {
    return true; //Assume power is always on 
  }
  
  DigitalOut powerGatingOut(m_powerGatingPin);
  return m_powerGatingOnWhenPinHigh?powerGatingOut:!powerGatingOut;
}

int UbloxUSBCDMAModem::init()
{
  if( !m_dongleConnected )
  {
    if(!power())
    {
      //Obviously cannot initialize the dongle if it is disconnected...
      ERR("Power is off");
      return NET_INVALID;
    }
    m_dongleConnected = true;
    while( !m_dongle.connected() )
    {
      m_dongle.tryConnect();
      Thread::wait(100);
    }
  }

  if(m_atOpen)
  {
    return OK;
  }

  DBG("Starting AT thread if needed");
  int ret = m_at.open();
  if(ret)
  {
    return ret;
  }

  DBG("Sending initialisation commands");
  ret = m_at.init();
  if(ret)
  {
    return ret;
  }

 if(m_dongle.getDongleType() == WAN_DONGLE_TYPE_UBLOX_LISAC200)
  {
    INFO("Using a UBLOX C200 Dongle");
  }
  else
  {
    WARN("Using an Unknown Dongle");
  }

  ATCommandsInterface::ATResult result;

  //Wait for network registration
  CSSProcessor cssProcessor;
  do
  {
    DBG("Waiting for network registration");
    ret = m_at.execute("AT+CSS?", &cssProcessor, &result);
    DBG("Result of command: Err code=%d\n", ret);
    DBG("ATResult: AT return=%d (code %d)\n", result.result, result.code);
    if(cssProcessor.getStatus() == CSSProcessor::STATUS_REGISTERING)
    {
      Thread::wait(3000);
    }
  } while(cssProcessor.getStatus() == CSSProcessor::STATUS_REGISTERING);

  m_atOpen = true;

  return OK;
}

int UbloxUSBCDMAModem::cleanup()
{
  if(m_ppp.isConnected())
  {
    WARN("Data connection is still open"); //Try to encourage good behaviour from the user
    m_ppp.disconnect(); 
  }
  
  m_smsInit = false;
//  m_linkMonitorInit = false;
  //We don't reset m_ipInit as PPPIPInterface::init() only needs to be called once
  
  if(m_atOpen)
  {
    m_at.close();
    m_atOpen = false;
  }
  
  m_dongle.disconnect();
  m_dongleConnected = false;
  
  return OK;
}


