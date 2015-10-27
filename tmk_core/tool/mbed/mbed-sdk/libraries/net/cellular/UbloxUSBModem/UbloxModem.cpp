/* UbloxModem.cpp */
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

#define __DEBUG__ 3
#ifndef __MODULE__
#define __MODULE__ "UbloxModem.cpp"
#endif

#include "core/fwk.h"
#include "sms/GSMSMSInterface.h"
#include "sms/CDMASMSInterface.h"

#include "UbloxModem.h"

UbloxModem::UbloxModem(IOStream* atStream, IOStream* pppStream) :
   m_at(atStream),                          // Construct ATCommandsInterface with the AT serial channel
   m_CdmaSms(&m_at),                         // Construct SMSInterface with the ATCommandsInterface
   m_GsmSms(&m_at),                          // Construct SMSInterface with the ATCommandsInterface
   m_ussd(&m_at),                           // Construct USSDInterface with the ATCommandsInterface
   m_linkMonitor(&m_at),                    // Construct LinkMonitor with the ATCommandsInterface
   m_ppp(pppStream ? pppStream : atStream),    // Construct PPPIPInterface with the PPP serial channel
   m_ipInit(false),                         // PPIPInterface connection is initially down
   m_smsInit(false),                        // SMSInterface starts un-initialised
   m_ussdInit(false),                       // USSDInterface starts un-initialised 
   m_linkMonitorInit(false),                // LinkMonitor subsystem starts un-initialised
   m_atOpen(false),                          // ATCommandsInterface starts in a closed state
   m_onePort(pppStream == NULL),
   m_type(UNKNOWN)
{
}


genericAtProcessor::genericAtProcessor()
{ 
    i = 0; 
    str[0] = '\0'; 
}

const char* genericAtProcessor::getResponse(void) 
{ 
    return str; 
}

int genericAtProcessor::onNewATResponseLine(ATCommandsInterface* pInst, const char* line)
{
    int l = strlen(line);
    if (i + l + 2 > sizeof(str))
        return NET_OVERFLOW;
    if (i) str[i++] = ',';
    strcat(&str[i], line);
    i += l;
    return OK;
}

int genericAtProcessor::onNewEntryPrompt(ATCommandsInterface* pInst)
{
    return OK;
}

class CREGProcessor : public IATCommandsProcessor
{
public:
  CREGProcessor(bool gsm) : status(STATUS_REGISTERING)
  {
    m_gsm = gsm;
  }
  enum REGISTERING_STATUS { STATUS_REGISTERING, STATUS_OK, STATUS_FAILED };
  REGISTERING_STATUS getStatus()
  {
    return status;
  }
  const char* getAtCommand()
  {
      return m_gsm ? "AT+CREG?" : "AT+CSS?";
  }
private:
  virtual int onNewATResponseLine(ATCommandsInterface* pInst, const char* line)
  {
    int r;
    if (m_gsm)
    {
        if( sscanf(line, "+CREG: %*d,%d", &r) == 1 )
        {
          status = (r == 1 || r == 5) ? STATUS_OK : 
                   (r == 0 || r == 2) ? STATUS_REGISTERING :
          //       (r == 3)           ? STATUS_FAILED :
                                        STATUS_FAILED;
        }
    }
    else
    {
        char bc[3] = "";
        if(sscanf(line, "%*s %*c,%2s,%*d",bc)==1)
        {
            status = (strcmp("Z", bc) == 0) ? STATUS_REGISTERING : STATUS_OK;
        }
    }
    return OK;
  }
  virtual int onNewEntryPrompt(ATCommandsInterface* pInst)
  {
    return OK;
  }
  volatile REGISTERING_STATUS status;
  bool m_gsm;
};

int UbloxModem::connect(const char* apn, const char* user, const char* password)
{
  if( !m_ipInit )
  {
    m_ipInit = true;
    m_ppp.init();
  }
  m_ppp.setup(user, password, (m_type != LISA_C200) ? DEFAULT_MSISDN_GSM : DEFAULT_MSISDN_CDMA);

  int ret = init();
  if(ret)
  {
    return ret;
  }

  if (m_onePort)
  {
     m_smsInit = false; //SMS status reset
     m_ussdInit = false; //USSD status reset
     m_linkMonitorInit = false; //Link monitor status reset
  }

  ATCommandsInterface::ATResult result;

  if(apn != NULL)
  {
    char cmd[48];
    int tries = 30;
    sprintf(cmd, "AT+CGDCONT=1,\"IP\",\"%s\"", apn);
    do //Try 30 times because for some reasons it can fail *a lot* with the K3772-Z dongle
    {
      ret = m_at.executeSimple(cmd, &result);
      DBG("Result of command: Err code=%d", ret);
      if(ret)
      {
        Thread::wait(500);
      }
    } while(ret && --tries);
    DBG("ATResult: AT return=%d (code %d)", result.result, result.code);
    DBG("APN set to %s", apn);
  }

  //Connect
  DBG("Connecting");
  if (m_onePort)
  {
    m_at.close(); // Closing AT parser
    m_atOpen = false; //Will need to be reinitialized afterwards
  }
  
  DBG("Connecting PPP");

  ret = m_ppp.connect();
  DBG("Result of connect: Err code=%d", ret);
  return ret;
}


int UbloxModem::disconnect()
{
  DBG("Disconnecting from PPP");
  int ret = m_ppp.disconnect();
  if(ret)
  {
    ERR("Disconnect returned %d, still trying to disconnect", ret);
  }

  //Ugly but leave dongle time to recover
  Thread::wait(500);

  if (m_onePort)
  {
    //ATCommandsInterface::ATResult result;
    DBG("Starting AT thread");
    ret = m_at.open();
    if(ret)
    {
      return ret;
    }
  }

  DBG("Trying to hangup");

  if (m_onePort)
  {
    //Reinit AT parser
    ret = m_at.init(false);
    DBG("Result of command: Err code=%d\n", ret);
    if(ret)
    {
      m_at.close(); // Closing AT parser
      DBG("AT Parser closed, could not complete disconnection");
      return NET_TIMEOUT;
    }
  
  }
  return OK;
}

int UbloxModem::sendSM(const char* number, const char* message)
{
  int ret = init();
  if(ret)
  {
    return ret;
  }

  ISMSInterface* sms;
  if (m_type == LISA_C200)  sms = &m_CdmaSms;
  else                      sms = &m_GsmSms;
  if(!m_smsInit)
  {
    ret = sms->init();
    if(ret)
    {
      return ret;
    }
    m_smsInit = true;
  }

  ret = sms->send(number, message);
  if(ret)
  {
    return ret;
  }

  return OK;
}

int UbloxModem::getSM(char* number, char* message, size_t maxLength)
{
  int ret = init();
  if(ret)
  {
    return ret;
  }

  ISMSInterface* sms;
  if (m_type == LISA_C200)  sms = &m_CdmaSms;
  else                      sms = &m_GsmSms;
  if(!m_smsInit)
  {
    ret = sms->init();
    if(ret)
    {
      return ret;
    }
    m_smsInit = true;
  }

  ret = sms->get(number, message, maxLength);
  if(ret)
  {
    return ret;
  }

  return OK;
}

int UbloxModem::getSMCount(size_t* pCount)
{
  int ret = init();
  if(ret)
  {
    return ret;
  }

  ISMSInterface* sms;
  if (m_type == LISA_C200)  sms = &m_CdmaSms;
  else                      sms = &m_GsmSms;
  if(!m_smsInit)
  {
    ret = sms->init();
    if(ret)
    {
      return ret;
    }
    m_smsInit = true;
  }

  ret = sms->getCount(pCount);
  if(ret)
  {
    return ret;
  }

  return OK;
}

ATCommandsInterface* UbloxModem::getATCommandsInterface()
{
  return &m_at;
}

int UbloxModem::init()
{
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
  ret = m_at.init(false);
  if(ret)
  {
    return ret;
  }
  
  
  ATCommandsInterface::ATResult result;
  genericAtProcessor atiProcessor;
  ret = m_at.execute("ATI", &atiProcessor, &result);
  if (OK != ret)
    return ret;
  const char* info = atiProcessor.getResponse();
  INFO("Modem Identification [%s]", info);
  if (strstr(info, "LISA-C200")) {
      m_type = LISA_C200;
      m_onePort = true; // force use of only one port
  }
  else if (strstr(info, "LISA-U200")) {
      m_type = LISA_U200;
  }
  else if (strstr(info, "SARA-G350")) {
      m_type = SARA_G350;
  }
  
  // enable the network indicator 
  if (m_type == SARA_G350) {
      m_at.executeSimple("AT+UGPIOC=16,2", &result);
  }
  else if (m_type == LISA_U200) {
      m_at.executeSimple("AT+UGPIOC=20,2", &result); 
  }
  else if (m_type == LISA_C200) {
      // LISA-C200 02S/22S : GPIO1 do not support network status indication
      // m_at.executeSimple("AT+UGPIOC=20,2", &result); 
  }
  INFO("Modem Identification [%s]", info);
  
  CREGProcessor cregProcessor(m_type != LISA_C200);
  //Wait for network registration
  do
  {
    DBG("Waiting for network registration");
    ret = m_at.execute(cregProcessor.getAtCommand(), &cregProcessor, &result);
    DBG("Result of command: Err code=%d\n", ret);
    DBG("ATResult: AT return=%d (code %d)\n", result.result, result.code);
    if(cregProcessor.getStatus() == CREGProcessor::STATUS_REGISTERING)
    {
      Thread::wait(3000);
    }
  } while(cregProcessor.getStatus() == CREGProcessor::STATUS_REGISTERING);
  if(cregProcessor.getStatus() == CREGProcessor::STATUS_FAILED)
  {
    ERR("Registration denied");
    return NET_AUTH;
  }
 
  m_atOpen = true;

  return OK;
}

int UbloxModem::cleanup()
{
  if(m_ppp.isConnected())
  {
    WARN("Data connection is still open"); //Try to encourage good behaviour from the user
    m_ppp.disconnect(); 
  }
  
  m_smsInit = false;
  m_ussdInit = false;
  m_linkMonitorInit = false;
  //We don't reset m_ipInit as PPPIPInterface::init() only needs to be called once
  
  if(m_atOpen)
  {
    m_at.close();
    m_atOpen = false;
  }
  
  return OK;
}

int UbloxModem::sendUSSD(const char* command, char* result, size_t maxLength)
{
  int ret = init();
  if(ret)
  {
    return ret;
  }

  if(!m_ussdInit)
  {
    ret = m_ussd.init();
    if(ret)
    {
      return ret;
    }
    m_ussdInit = true;
  }

  ret = m_ussd.send(command, result, maxLength);
  if(ret)
  {
    return ret;
  }

  return OK;
}

int UbloxModem::getLinkState(int* pRssi, LinkMonitor::REGISTRATION_STATE* pRegistrationState, LinkMonitor::BEARER* pBearer)
{
  int ret = init();
  if(ret)
  {
    return ret;
  }
  
  if(!m_linkMonitorInit)
  {
    ret = m_linkMonitor.init(m_type != LISA_C200);
    if(ret)
    {
      return ret;
    }
    m_linkMonitorInit = true;
  }

  ret = m_linkMonitor.getState(pRssi, pRegistrationState, pBearer);
  if(ret)
  {
    return ret;
  }

  return OK;
}

int UbloxModem::getPhoneNumber(char* phoneNumber)
{
  int ret = init();
  if(ret)
  {
    return ret;
  }
  
  if(!m_linkMonitorInit)
  {
    ret = m_linkMonitor.init(m_type != LISA_C200);
    if(ret)
    {
      return ret;
    }
    m_linkMonitorInit = true;
  }

  ret = m_linkMonitor.getPhoneNumber(phoneNumber);
  if(ret)
  {
    return ret;
  }

  return OK;
}

#include "USBHost.h"
#include "UbloxGSMModemInitializer.h"
#include "UbloxCDMAModemInitializer.h"

UbloxUSBModem::UbloxUSBModem() :
   UbloxModem(&m_atStream, &m_pppStream),
   m_dongle(),                              // Construct WANDongle: USB interface with two serial channels to the modem (USBSerialStream objects)
   m_atStream(m_dongle.getSerial(1)),       // AT commands are sent down one serial channel.
   m_pppStream(m_dongle.getSerial(0)),      // PPP connections are managed via another serial channel.
   m_dongleConnected(false)                 // Dongle is initially not ready for anything
{
    USBHost* host = USBHost::getHostInst();
    m_dongle.addInitializer(new UbloxGSMModemInitializer(host));
    m_dongle.addInitializer(new UbloxCDMAModemInitializer(host));
}

int UbloxUSBModem::init()
{
  if( !m_dongleConnected )
  {
    m_dongleConnected = true;
    while( !m_dongle.connected() )
    {
      m_dongle.tryConnect();
      Thread::wait(10);
    }
    if(m_dongle.getDongleType() == WAN_DONGLE_TYPE_UBLOX_LISAU200)
    {
      INFO("Using a u-blox LISA-U200 3G/WCDMA Modem");
      m_type = LISA_U200;
    }
    else if(m_dongle.getDongleType() == WAN_DONGLE_TYPE_UBLOX_LISAC200)
    {
      INFO("Using a u-blox LISA-C200 CDMA Modem");
      m_type = LISA_C200;
      m_onePort = true;
    }
    else
    {
      WARN("Using an Unknown Dongle");
    }
  }
  return UbloxModem::init();
}

int UbloxUSBModem::cleanup()
{
  UbloxModem::cleanup();
  m_dongle.disconnect();
  m_dongleConnected = false;
  return OK;
}

UbloxSerModem::UbloxSerModem() :
   UbloxModem(&m_atStream, NULL),
   m_Serial(P0_15/*MDMTXD*/,P0_16/*MDMRXD*/),
   m_atStream(m_Serial)
{
  m_Serial.baud(115200/*MDMBAUD*/);
  m_Serial.set_flow_control(SerialBase::RTSCTS, P0_22/*MDMRTS*/, P0_17/*MDMCTS*/);
}

