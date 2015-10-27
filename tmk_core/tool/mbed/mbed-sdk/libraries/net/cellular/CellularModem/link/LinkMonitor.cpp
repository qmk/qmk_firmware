/* LinkMonitor.cpp */
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

#define __DEBUG__ 0
#ifndef __MODULE__
#define __MODULE__ "LinkMonitor.cpp"
#endif

#include "core/fwk.h"

#include "LinkMonitor.h"

#include <cstdio>
using std::sscanf;

#define DEFAULT_TIMEOUT 10000

LinkMonitor::LinkMonitor(ATCommandsInterface* pIf) : m_pIf(pIf), m_rssi(0), m_registrationState(REGISTRATION_STATE_UNKNOWN), m_bearer(BEARER_UNKNOWN)
{
  m_gsm = true;
}

int LinkMonitor::init(bool gsm)
{
  m_gsm = gsm;
  if (m_gsm)
  {
    // we need to make sure that we setup the operator selection to be in 'numeric' format.
    // i.e. it is made up of a network and country code when returned by the modem e.g. Operator = 23415. This allows easy logic parsing for
    // setting up other network parameters in future.
    DBG("LinkMonitor::init() being called. This should only happen once: executinging AT+COPS=0,2");  
    int ret = m_pIf->executeSimple("AT+COPS=0,2", NULL, DEFAULT_TIMEOUT); //Configure to set the operator string to Country Code and mobile network code
    if(ret != OK)
    {
      WARN(" NET_PROTOCOL error from sending the AT+COPS command to the modem. ");
      return NET_PROTOCOL;
    }
  }
  return OK;
}

/*virtual*/ int LinkMonitor::onNewATResponseLine(ATCommandsInterface* pInst, const char* line)
{
  DBG("Line is %s", line);
  char n[32] = "";
  char s[32] = "";
  int v;
  if( sscanf(line, "+CREG: %*d,%d", &v) >= 1 ) //Reg state is valid
  {
    DBG("+CREG %d", v);
    switch( v )
    {
      case 0:
        m_registrationState = REGISTRATION_STATE_UNKNOWN;
        break;
      case 1:
        m_registrationState = REGISTRATION_STATE_HOME_NETWORK;
        break;
      case 2:
        m_registrationState = REGISTRATION_STATE_REGISTERING;
        break;
      case 3:
        m_registrationState = REGISTRATION_STATE_DENIED;  
        break;
      case 4:
        m_registrationState = REGISTRATION_STATE_NO_SIGNAL;  
        break;        
      case 5:
        m_registrationState = REGISTRATION_STATE_ROAMING;  
        break;
      default:
        m_registrationState = REGISTRATION_STATE_UNKNOWN;  
        break;
    }
  }
  else if( sscanf(line, "+COPS: %*d,%*d,\"%*[^\"]\",%d", &v) >= 1 )
  {
    DBG("+COPS %d", v);
    switch( v )
    {
      case 0:
        m_bearer = BEARER_GSM;
        break;
      case 2:
        m_bearer = BEARER_UMTS;
        break;
      case 3:
        m_bearer = BEARER_EDGE;
        break;
      case 4: //HSDPA
      case 5: //HSUPA
      case 6: //HSDPA + HSUPA
        m_bearer = BEARER_HSPA;
        break;
      case 7:
        m_bearer = BEARER_LTE;
        break;  
      case 1: //GSM Compact
      default:
        m_bearer = BEARER_UNKNOWN;
        break;
    }
  }
  else if( sscanf(line, "+CSQ: %d,%*d", &v) >= 1 )
  {
    DBG("+CSQ %d", v);
    if(v == 99) //Unknown
    {
      m_rssi = 0; //Unknown
    }
    else
    {
      m_rssi = -113 + 2*v;
    }
  }
  else if ( (sscanf(line, "+CNUM: \"%[^\"]\",\"%[^\"]\",%d", n, s, &v) == 3) || 
            (sscanf(line, "+CNUM: \"\",\"%[^\"]\",%d", s, &v) == 2) )
  {
      if (*s && ((v == 145/*number includes + */) || (v == 129/*otherwise*/))) {
        strcpy(m_phoneNumber, s);
      }
  }
  return OK;
}

/*virtual*/ int LinkMonitor::onNewEntryPrompt(ATCommandsInterface* pInst)
{
  return OK;
}

int LinkMonitor::getState(int* pRssi, REGISTRATION_STATE* pRegistrationState, BEARER* pBearer)
{
  m_rssi = 0;
  m_registrationState = REGISTRATION_STATE_UNKNOWN;
  m_bearer = BEARER_UNKNOWN;
  int ret = m_pIf->execute(m_gsm ? "AT+CREG?;+COPS?;+CSQ" : "AT+CREG?;+CSQ", this, NULL, DEFAULT_TIMEOUT); //Configure to get registration info & get it; get signal quality
  if(ret != OK)
  {
    return NET_PROTOCOL;
  }
  *pRssi = m_rssi;
  *pRegistrationState = m_registrationState;
  *pBearer = m_bearer;
  return OK;
}

int LinkMonitor::getPhoneNumber(char* phoneNumber)
{
  *m_phoneNumber = '\0';
  if (m_gsm) {
    int ret = m_pIf->execute("AT+CNUM", this, NULL, DEFAULT_TIMEOUT);
    if(ret != OK)
    {
      return NET_PROTOCOL;
    }
  }
  strcpy(phoneNumber, m_phoneNumber);
  return OK;
}