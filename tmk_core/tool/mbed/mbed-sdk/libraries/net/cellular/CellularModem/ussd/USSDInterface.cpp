/* USSDInterface.cpp */
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
#define __MODULE__ "USSDInterface.cpp"
#endif

#include "core/fwk.h"

#include "USSDInterface.h"

#include <cstdio>

#define DEFAULT_TIMEOUT 10000
#define USSD_TIMEOUT 15000

USSDInterface::USSDInterface(ATCommandsInterface* pIf) : m_pIf(pIf), m_responseMtx(), m_responseSphre(1), m_result(NULL), m_maxResultLength(0)
{
  m_responseSphre.wait(0); //Take ownership of the semaphore
  m_pIf->registerEventsHandler(this); //Add us to the unsolicited result codes handlers
}

int USSDInterface::init()
{
  DBG("Initialization done");
  return OK;
}

int USSDInterface::send(const char* command, char* result, size_t maxLength)
{
  if (strlen(command) > 20) //Prevent buffer overflow
  {
    return NET_TOOSMALL;
  }

  m_responseMtx.lock();
  m_result = result;
  m_maxResultLength = maxLength;
  m_responseMtx.unlock();

  m_responseSphre.wait(0); //Make sure there is not a pending result that needs to be discarded

  DBG("Send USSD command & register for unsolicited result codes");
  //Send USSD command to the network
  char cmd[32];
  std::sprintf(cmd, "AT+CUSD=1,\"%s\"", command);
  int ret = m_pIf->execute(cmd, this, NULL, DEFAULT_TIMEOUT);
  if( ret != OK )
  {
    return NET_PROTOCOL;
  }
  
  //Did we already get a response (3GPP rev < 6) ?

  //Now wait for response
  int res = m_responseSphre.wait(USSD_TIMEOUT);

  //Reset data
  m_responseMtx.lock();
  m_result = NULL;
  m_maxResultLength = 0;
  m_responseMtx.unlock();

  if(res <= 0)
  {
    DBG("No result received");
    ret = m_pIf->executeSimple("AT+CUSD=2", NULL, DEFAULT_TIMEOUT); //Cancel command
    if( ret != OK )
    {
      return NET_PROTOCOL;
    }
    return NET_TIMEOUT;
  }

  DBG("Result received: %s", result);

  return OK;
}

/*virtual*/ int USSDInterface::onNewATResponseLine(ATCommandsInterface* pInst, const char* line)
{
  const char* pSemicol = strchr(line, ':');
  if( ( (pSemicol - line) != strlen("+CUSD") ) || ( memcmp(line, "+CUSD", strlen("+CUSD")) != 0) )
  {
    WARN("Unknown code");
    return OK;
  }

  const char* pData = NULL;
  if( pSemicol != NULL ) //Split the identifier & the result code (if it exists)
  {
    pData = pSemicol + 1;
    if(pData[0]==' ')
    {
      pData++; //Suppress whitespace
    }
    processResult(pData);
  }
  return OK;
}

/*virtual*/ int USSDInterface::onNewEntryPrompt(ATCommandsInterface* pInst)
{
  return OK;
}

/*virtual*/ bool USSDInterface::isATCodeHandled(const char* atCode) //Is this AT code handled
{
  DBG("AT code is %s", atCode);
  if( strcmp("+CUSD", atCode) == 0 )
  {
    return true;
  }

  DBG("Not handled");
  return false;
}

/*virtual*/ void USSDInterface::onDispatchStart()
{


}

/*virtual*/ void USSDInterface::onDispatchStop()
{

}

/*virtual*/ char* USSDInterface::getEventsEnableCommand()
{
  return NULL; //No need to disable events here
}

/*virtual*/ char* USSDInterface::getEventsDisableCommand()
{
  return NULL; //No need to re-enable events here
}

/*virtual*/ void USSDInterface::onEvent(const char* atCode, const char* evt)
{
  if( strcmp("+CUSD", atCode) != 0 )
  {
    WARN("Wrong AT Code");
    return; //Not supported
  }

  processResult(evt);
}

void USSDInterface::processResult(const char* data)
{
  char* pStart = (char*) strchr(data,'\"');
  if(pStart==NULL)
  {
    WARN("Could not find opening quote");
    return; //Invalid/incomplete response
  }
  pStart++; //Point to first char of response
  char* pEnd = (char*) strchr(pStart,'\"');
  if(pEnd==NULL)
  {
    WARN("Could not find closing quote");
    return; //Invalid/incomplete response
  }
  m_responseMtx.lock();
  if(m_maxResultLength == 0) //No pending command
  {
    WARN("No pending command");
    m_responseMtx.unlock();
    return;
  }
  size_t cpyLen = MIN( pEnd - pStart, m_maxResultLength - 1 );
  memcpy((void*)m_result, pStart, cpyLen);
  m_result[cpyLen] = '\0';
  DBG("Got USSD response: %s", m_result);
  m_responseMtx.unlock();
  m_responseSphre.release(); //Signal user thread that response is ready
}
