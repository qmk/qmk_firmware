/* SMSInterface.h */
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

#ifndef CDMASMSINTERFACE_H_
#define CDMASMSINTERFACE_H_

#include "SMSInterface.h"

#define MAX_SM 8

/** Component to use the Short Messages Service (SMS)
 *
 */
class CDMASMSInterface : public ISMSInterface, protected IATCommandsProcessor
{
public:
  /** Create SMSInterface instance
     @param pIf Pointer to the ATCommandsInterface instance to use
   */
  CDMASMSInterface(ATCommandsInterface* pIf);

  /** Initialize interface
    Configure SMS commands & register for SMS-related unsolicited result codes
   */
  virtual int init();

  /** Send a SM
     @param number The receiver's phone number
     @param message The message to send
     @return 0 on success, error code on failure
   */
  virtual int send(const char* number, const char* message);


  /** Receive a SM
     @param number Pointer to a buffer to store the sender's phone number (must be at least 17 characters-long, including the space for the null-terminating char)
     @param message Pointer to a buffer to store the the incoming message
     @param maxLength Maximum message length that can be stored in buffer (including null-terminating character)
     @return 0 on success, error code on failure
   */
  virtual int get(char* number, char* message, size_t maxLength);


  /** Get the number of SMs in the incoming box
     @param pCount pointer to store the number of unprocessed SMs on
     @return 0 on success, error code on failure
   */
  virtual int getCount(size_t* pCount);

protected:
  //IATCommandsProcessor
  virtual int onNewATResponseLine(ATCommandsInterface* pInst, const char* line);
  virtual int onNewEntryPrompt(ATCommandsInterface* pInst);

  int updateInbox(); //Update messages count in the different inboxes

private:
  ATCommandsInterface* m_pIf;

  //Current message
  char* m_msg;
  size_t m_maxMsgLength;
  char* m_msisdn;

  //Messages list
  size_t m_msgInListsCount[4]; //4 lists
  
  size_t m_headersToRead;
  
  enum { SMS_NONE, SMS_SENT, SMS_PENDING, SMS_FAILED } m_txState;
  enum { SMS_IDLE, SMS_SEND_CMD_SENT, SMS_GET_TX_STATUS_CMD_SENT, SMS_GET_CMD_SENT, SMS_GET_HDR_RECEIVED, SMS_GET_COUNT_CMD_SENT, SMS_CMD_PROCESSED } m_state;
};

#endif /* CDMASMSINTERFACE_H_ */
