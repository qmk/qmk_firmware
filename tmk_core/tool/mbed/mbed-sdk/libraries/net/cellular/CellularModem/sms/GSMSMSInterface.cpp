/* GSMSMSInterface.cpp */
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

#define __DEBUG__ 2
#ifndef __MODULE__
#define __MODULE__ "GSMSMSInterface.cpp"
#endif

#include "core/fwk.h"

#include "GSMSMSInterface.h"

#include <cstdio>
#include <cstring>

#define DEFAULT_TIMEOUT 10000

GSMSMSInterface::GSMSMSInterface(ATCommandsInterface* pIf) : m_pIf(pIf), m_msg(NULL), m_maxMsgLength(0), m_msisdn(NULL)
{
  m_pIf->registerEventsHandler(this); //Add us to the unsolicited result codes handlers
}

int GSMSMSInterface::init()
{
  m_msgRefListCount = 0;
  m_needsUpdate = true;
  m_state = SMS_IDLE;

  DBG("Set format");
  //Set Text mode format
  int ret = m_pIf->executeSimple("AT+CMGF=1", NULL, DEFAULT_TIMEOUT);
  if(ret != OK)
  {
    return NET_PROTOCOL;
  }

  DBG("Setup new messages indication");
  //Setup new messages indication
  ret = m_pIf->executeSimple("AT+CNMI=2,1,0,0,0", NULL, DEFAULT_TIMEOUT);
  if(ret != OK)
  {
    return NET_PROTOCOL;
  }

  DBG("Try to fetch inbox");
  m_inboxMtx.lock();
  if( m_needsUpdate )
  {
    ret = updateInbox(); //Fetch existing messages references
    if(ret)
    {
      m_inboxMtx.unlock();
      return NET_PROTOCOL;
    }
  }
  m_inboxMtx.unlock();

  DBG("Initialization done");
  return OK;
}

int GSMSMSInterface::send(const char* number, const char* message)
{
  if( strlen(number) > 16 )
  {
    return NET_INVALID; //Number too long to match 3GPP spec
  }

  int ret;

  //Prepare infos
  m_state = SMS_SEND_CMD_SENT;
  m_msg = (char*) message;

  DBG("Send SM");
  //Send command
  char cmd[32];
  std::sprintf(cmd, "AT+CMGS=\"%s\"", number);
  ret = m_pIf->execute(cmd, this, NULL, DEFAULT_TIMEOUT);

  if( (ret != OK) || (m_state != SMS_CMD_PROCESSED) )
  {
    WARN("ret %d, state %d", ret, m_state);
    m_state = SMS_IDLE;
    return NET_PROTOCOL;
  }

  DBG("SM sent");
  m_state = SMS_IDLE;
  return OK;
}


int GSMSMSInterface::get(char* number, char* message, size_t maxLength)
{
  if( maxLength < 1  )
  {
    return NET_INVALID; //Buffer too short
  }

  int ret;

  DBG("Get next message");
  m_inboxMtx.lock();
  if( ((m_msgRefListCount == 0) && m_needsUpdate) || ((m_msgRefListCount > 0) && (m_msgRefList[0] == -1)) )
  {
    DBG("Message list count is 0 and needs updating or next index is unknown, calling updateInbox()");
    ret = updateInbox();
    
    if (ret)
    {
      m_inboxMtx.unlock();
      return ret;
    }
  }
  
  DBG("%d messages to read", m_msgRefListCount);

  if(m_msgRefListCount == 0)
  {
    m_inboxMtx.unlock();
    DBG("Message list count is 0, I think it's empty and returning.");
    return NET_EMPTY; //No message to read
  }

  //Prepare infos
  m_state = SMS_GET_CMD_SENT;
  m_msisdn = (char*) number;
  m_msg = (char*) message;
  m_maxMsgLength = maxLength;

  DBG("Get SMS");
  //List command
  char cmd[32];
  std::sprintf(cmd, "AT+CMGR=%d", m_msgRefList[0]);
  ret = m_pIf->execute(cmd, this, NULL, DEFAULT_TIMEOUT);
  if( ret != OK )
  {
    WARN("AT+CMGR returned %d", ret);
    m_state = SMS_IDLE;
    m_inboxMtx.unlock();
    return NET_PROTOCOL;
  }

  if (m_state != SMS_CMD_PROCESSED)
  {
    WARN("State variable is not 'SMS_CMD_PROCESSED' - returning 'NET_EMPTY'");
  }

  DBG("Deleting message from index number: %d", m_msgRefList[0] );
  //Delete message from outbox
  std::sprintf(cmd, "AT+CMGD=%d", m_msgRefList[0]);
  ret = m_pIf->executeSimple(cmd, NULL, DEFAULT_TIMEOUT);
  if(ret != OK)
  {
    ERR("Could not delete message");
  }
  //Remove message from list
  std::memmove(&m_msgRefList[0], &m_msgRefList[1], MIN(m_msgRefListCount-1,MAX_SM-1)*sizeof(m_msgRefList[0]));
  m_msgRefListCount--;
  
  if(m_msgRefListCount > MAX_SM - 1) //Last message index is unknown, so put -1 to tell the lib to fetch it when needed
  {
    DBG("Last message index is unknown, will need to be updated");
    m_msgRefList[MAX_SM - 1] = -1;
  }
  
  DBG("%d messages to read", m_msgRefListCount);
  
  if (m_state != SMS_CMD_PROCESSED)
  {
    m_state = SMS_IDLE;
    m_inboxMtx.unlock();
    return NET_EMPTY;
  }
  
  m_state = SMS_IDLE;
  m_inboxMtx.unlock();

  return OK;
}


int GSMSMSInterface::getCount(size_t* pCount)
{
  int ret;

  m_inboxMtx.lock();
  if( m_needsUpdate )
  {
    ret = updateInbox();
    if(ret)
    {
      m_inboxMtx.unlock();
      return NET_PROTOCOL;
    }
  }

  *pCount = m_msgRefListCount;
  m_inboxMtx.unlock();

  return OK;
}


/*virtual*/ int GSMSMSInterface::onNewATResponseLine(ATCommandsInterface* pInst, const char* line)
{
  if(m_state == SMS_SEND_CMD_SENT)
  {
    if( std::sscanf(line, "+CMGS: %*d") == 0 )
    {
      DBG("SM sent");
      m_state = SMS_CMD_PROCESSED;
    }
  }
  else if(m_state == SMS_GET_CMD_SENT)
  {
    DBG("Header: %s", line);
    if( std::sscanf(line, "+CMGR: %*[^,],\"%16[^\"]\"", m_msisdn) == 1 ) //Get message ref
    {
      m_state = SMS_GET_HDR_RECEIVED;
    }
  }
  else if(m_state == SMS_GET_HDR_RECEIVED)
  {
    DBG("Message: %s", line);
    size_t cpyLen = MIN( std::strlen(line), m_maxMsgLength - 1 );
    std::memcpy( m_msg, line, cpyLen );
    m_msg[cpyLen] = '\0';
    m_state = SMS_CMD_PROCESSED;
  }
  else if(m_state == SMS_GET_COUNT_CMD_SENT)
  {
    DBG("Header: %s", line);
    int msgRef;
    if( std::sscanf(line, "+CMGL: %d,\"REC", &msgRef) == 1 ) //Filter on REC READ and REC UNREAD messages 
    {
      m_state = SMS_GET_COUNT_HDR_RECEIVED;
      //Add message to list
      if(m_msgRefListCount < MAX_SM)
      {
        m_msgRefList[m_msgRefListCount] = msgRef;
      }
      m_msgRefListCount++; //Always count message
      DBG("m_msgRefListCount=%d",m_msgRefListCount);
    }
  }
  else if(m_state == SMS_GET_COUNT_HDR_RECEIVED)
  {
    DBG("Message (debug only): %s", line); //For debug only
    m_state = SMS_GET_COUNT_CMD_SENT;
  }
  return OK;
}

/*virtual*/ int GSMSMSInterface::onNewEntryPrompt(ATCommandsInterface* pInst)
{
  if(m_state == SMS_SEND_CMD_SENT)
  {
    char* crPtr = strchr(m_msg, CR);
    if(crPtr != NULL)
    {
      int crPos = crPtr - m_msg;
      //Replace m_inputBuf[crPos] with null-terminating char
      m_msg[crPos] = '\x0';

      //If there is a CR char, split message there

      //Do print the message
      int ret = pInst->sendData(m_msg);
      if(ret)
      {
        return ret;
      }

      char cr[2] = {CR, '\0'};
      ret = pInst->sendData(cr);
      if(ret)
      {
        return ret;
      }

      m_msg += crPos;

      if(m_msg[0] == LF)
      {
        m_msg++; //Discard LF char as well
      }

      return NET_MOREINFO;
    }
    else
    {
      //Do print the message
      pInst->sendData(m_msg);
      return OK;
    }
  }

  return OK;
}

/*virtual*/ bool GSMSMSInterface::isATCodeHandled(const char* atCode) //Is this AT code handled
{
  DBG("AT code is %s", atCode);
  if( strcmp("+CMTI", atCode) == 0 )
  {
    return true;
  }

  DBG("Not handled");
  return false;
}

/*virtual*/ void GSMSMSInterface::onDispatchStart()
{
    
}

/*virtual*/ void GSMSMSInterface::onDispatchStop()
{
    
}

/*virtual*/ char* GSMSMSInterface::getEventsEnableCommand()
{
  return "AT+CNMI=2,1,0,0,0";
}

/*virtual*/ char* GSMSMSInterface::getEventsDisableCommand()
{
  return "AT+CNMI=0,0,0,0,0"; //Indications will be buffered within the modem and flushed back when the former command is executed
}

/*virtual*/ void GSMSMSInterface::onEvent(const char* atCode, const char* evt)
{
  if( strcmp("+CMTI", atCode) != 0 )
  {
    return; //Not supported
  }

  DBG("Unsollicited result code: %s - %s", atCode, evt);

  //Get index
  int msgRef;
  if(( std::sscanf(evt, "\"SM\",%d", &msgRef) == 1 ) || 
     ( std::sscanf(evt, "\"ME\",%d", &msgRef) == 1 ))
  {
    DBG("Adding message to list (ref %d)", msgRef);
    if(m_inboxMtx.trylock())
    {
      //Add message to list
      if(m_msgRefListCount < MAX_SM)
      {
        m_msgRefList[m_msgRefListCount] = msgRef;
      }
      m_msgRefListCount++; //Always count message
      m_inboxMtx.unlock();
    }
    else
    {
      WARN("Could not get lock");
      m_needsUpdate = true;
    }
  }
}

int GSMSMSInterface::updateInbox()
{
  //Get memory indexes of unread messages

  DBG("Updating inbox");
  m_msgRefListCount = 0; //Reset list
  m_needsUpdate = false; //Assume we won't need update after this routine (can be set to true by an incoming SM event)

  //First list the "REC READ" messages that were not processed in the previous session
  m_state = SMS_GET_COUNT_CMD_SENT;
  int ret = m_pIf->execute("AT+CMGL=\"REC READ\"", this, NULL, DEFAULT_TIMEOUT);
  if( ret != OK )
  {
    WARN("AT+CMGL returned %d", ret);
    m_state = SMS_IDLE;
    m_msgRefListCount = 0; //List could be invalid
    m_needsUpdate = true;
    return NET_PROTOCOL;
  }
  
  //Now list the "REC UNREAD" messages that were received by the modem since
  m_state = SMS_GET_COUNT_CMD_SENT;
  ret = m_pIf->execute("AT+CMGL=\"REC UNREAD\"", this, NULL, DEFAULT_TIMEOUT);
  if( ret != OK )
  {
    WARN("AT+CMGL returned %d", ret);
    m_state = SMS_IDLE;
    m_msgRefListCount = 0; //List could be invalid
    m_needsUpdate = true;
    return NET_PROTOCOL;
  }

  DBG("%d incoming messages in inbox", m_msgRefListCount);

  m_state = SMS_IDLE;

  return OK;
}


