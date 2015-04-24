/* CDMASMSInterface.cpp */
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
#define __MODULE__ "CDMASMSInterface.cpp"
#endif

#include "core/fwk.h"

#include "CDMASMSInterface.h"

#include <cstdio>
#include <cstring>

using std::sscanf;

#define DEFAULT_TIMEOUT 10000

CDMASMSInterface::CDMASMSInterface(ATCommandsInterface* pIf) : m_pIf(pIf), m_msg(NULL), m_maxMsgLength(0), m_msisdn(NULL)
{
}

int CDMASMSInterface::init()
{
  m_state = SMS_IDLE;

  DBG("Get number of messages in the different inboxes");
  int ret = updateInbox();
  if(ret)
  {
    return NET_PROTOCOL;
  }
  
  DBG("Initialization done");
  return OK;
}

int CDMASMSInterface::send(const char* number, const char* message)
{
  if( strlen(number) > 16 )
  {
    return NET_INVALID; //Number too long
  }

  int ret;

  //Prepare infos
  m_state = SMS_SEND_CMD_SENT;
  
  bool intlNumber=(number[0]=='+'); //If the number starts with the + sign, replace it with 011 instead (int'l dialing code in the US)

  DBG("Send SM");
  //Send command
  char cmd[32+strlen(message)];
  std::sprintf(cmd, "AT!SSMS=0,%s%s,,\"%s\"",intlNumber?"011":"", intlNumber?(number+1):number, message); //Send with normal priority
  ret = m_pIf->execute(cmd, this, NULL, DEFAULT_TIMEOUT);

  if(ret != OK)
  {
    WARN("ret %d", ret);
    m_state = SMS_IDLE;
    return NET_PROTOCOL;
  }

  DBG("Check status");
  m_txState = SMS_PENDING;
  
  int tries = 10;
  while(tries--)
  {
    m_state = SMS_GET_TX_STATUS_CMD_SENT;
    ret = m_pIf->execute("AT!SSMS?", this, NULL, DEFAULT_TIMEOUT);
    if(ret)
    {
      m_state = SMS_IDLE;
      return ret;
    }
    m_state = SMS_IDLE;
    if(m_txState == SMS_PENDING) //Wait more
    {
      Thread::wait(1000);
      continue;
    }
    else if(m_txState == SMS_FAILED)
    {
      ERR("The modem could not send the SM");
      return NET_CONN; //Probably a conenction issue, the user can retry
    }
    else
    {
      break;
    }
  }
  if(!tries)
  {
    ERR("The is still trying to send the SM");
    return NET_TIMEOUT;
  }
  return OK;
}


int CDMASMSInterface::get(char* number, char* message, size_t maxLength)
{
  if( maxLength < 1  )
  {
    return NET_INVALID; //Buffer too short
  }

  int ret;

  DBG("Get next message");
  if( (m_msgInListsCount[0] + m_msgInListsCount[1] + m_msgInListsCount[2]) == 0)
  {
    DBG("Message list count is 0 and needs updating. Running updateInbox.");
    ret = updateInbox();
    if (ret)
    {
      return ret;
    }
  }

  if( (m_msgInListsCount[0] + m_msgInListsCount[1] + m_msgInListsCount[2]) == 0)
  {
    DBG("Message list count is 0");
    return NET_EMPTY; //No message to read
  }
  
  //Determine which index to use : 3 (read), then 1 (urgent), then 2 (regular)
  int index;
  if(m_msgInListsCount[2])
  {
    index = 3;
  }
  else if(m_msgInListsCount[0])
  {
    index = 1;
  }
  else //if(m_msgInListsCount[1])
  {
    index = 2;
  }

  //Prepare infos
  m_state = SMS_GET_CMD_SENT;
  m_msisdn = (char*) number;
  m_msg = (char*) message;
  m_maxMsgLength = maxLength;
  m_headersToRead = 3;
  
  m_msisdn[0] = '\0';

  DBG("Get SMS");
  //Read command
  char cmd[32];
  std::sprintf(cmd, "AT!GSMS?%d,1", index); //1 is the oldest message
  ret = m_pIf->execute(cmd, this, NULL, DEFAULT_TIMEOUT);
  if( ret != OK )
  {
    WARN("AT!GSMS returned %d", ret);
    m_state = SMS_IDLE;
    return NET_PROTOCOL;
  }
  
  //If message is not read, it will be put at the end of the read list
  int item;
  if( index != 3 )
  {
    //Decrement count in relevant list
    m_msgInListsCount[index-1]--;  
    //Increment count in read list
    m_msgInListsCount[3-1]++;  
    item = m_msgInListsCount[3-1];
    //Normally item should be equal to 1 as we'd have read any older messages first
    if( item != 1 )
    {
      WARN("Still some older messages pending in the read inbox");
    }
  }
  else
  {
    //The item is still the oldest one
    item = 1;
  }
  
  DBG("Deleting message");
  //Delete message from inbox
  std::sprintf(cmd, "AT!DSMS=3"/*,%d", item*/); //FIXME why doesn't that work when specifying the index??
  ret = m_pIf->executeSimple(cmd, NULL, DEFAULT_TIMEOUT);
  if(ret != OK)
  {
    ERR("Could not delete message");
  }
  else
  {
    //Now we can decrease the number of read messages
    m_msgInListsCount[3-1]--; 
  }
  
  if (m_state != SMS_CMD_PROCESSED)
  {
    WARN("Message could not be retrieved properly");
    m_state = SMS_IDLE;
    return NET_EMPTY;
  }
  
  m_state = SMS_IDLE;

  return OK;
}


int CDMASMSInterface::getCount(size_t* pCount)
{
  int ret = updateInbox();
  if(ret)
  {
      return NET_PROTOCOL;
  }

  *pCount = m_msgInListsCount[0] + m_msgInListsCount[1] + m_msgInListsCount[2]; //Urgent messages + regular messages + read messages

  return OK;
}


/*virtual*/ int CDMASMSInterface::onNewATResponseLine(ATCommandsInterface* pInst, const char* line)
{
  if(m_state == SMS_SEND_CMD_SENT)
  {
    DBG("SMS Send: %s", line);
  }
  else if(m_state == SMS_GET_TX_STATUS_CMD_SENT)
  {
    if(!strcmp(line, "sent"))
    {
      m_txState = SMS_SENT;
      m_state = SMS_CMD_PROCESSED;
    }
    else if(!strcmp(line, "failed"))
    {
      m_txState = SMS_FAILED;
      m_state = SMS_CMD_PROCESSED;
    }
    else if(!strcmp(line, "none"))
    {
      m_txState = SMS_NONE;
      m_state = SMS_CMD_PROCESSED;
    }
    else if(!strcmp(line, "pending"))
    {
      m_txState = SMS_PENDING;
      m_state = SMS_CMD_PROCESSED;
    }
  }
  else if(m_state == SMS_GET_CMD_SENT)
  {
    DBG("Header: %s", line);
    
    if(m_msisdn[0]=='\0')
    {
      sscanf(line, "From: %16s", m_msisdn);
    }
    
    m_headersToRead--;
    
    if(m_headersToRead==0) //End of headers
    {
      if(m_msisdn[0]!='\0') //Checks that the incoming number has been retrieved
      {
        m_state = SMS_GET_HDR_RECEIVED;
      }
      else
      {
        m_state = SMS_IDLE; //Error, signal it
      }
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
    DBG("Inbox: %s", line);
    int index;
    size_t count;
    if((strlen(line) > 16) && sscanf(line + 16, "{Index = %d}: %d", &index, &count) == 2)
    {
      if((index > 0) && (index <=4))
      {
        m_msgInListsCount[index-1] = count;
      }
      if(index == 4)
      {
        m_state = SMS_CMD_PROCESSED;
      }
    }
  }
  return OK;
}

/*virtual*/ int CDMASMSInterface::onNewEntryPrompt(ATCommandsInterface* pInst)
{
  return OK;
}


int CDMASMSInterface::updateInbox()
{
  //Get number of unread/read messages

  DBG("Updating inbox");
  m_msgInListsCount[0] = m_msgInListsCount[1] = m_msgInListsCount[2] = m_msgInListsCount[3] = 0; //Reset counts

  //Get counts
  m_state = SMS_GET_COUNT_CMD_SENT;
  int ret = m_pIf->execute("AT!CNTSMS", this, NULL, DEFAULT_TIMEOUT);
  if( ret != OK )
  {
    WARN("AT!CNTSMS returned %d", ret);
    m_msgInListsCount[0] = m_msgInListsCount[1] = m_msgInListsCount[2] = m_msgInListsCount[3] = 0; //Invalidate counts
    m_state = SMS_IDLE;
    return NET_PROTOCOL;
  }

  return OK;
}

