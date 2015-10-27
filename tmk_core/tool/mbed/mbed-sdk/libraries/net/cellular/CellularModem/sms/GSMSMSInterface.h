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

#ifndef GSMSMSINTERFACE_H_
#define GSMSMSINTERFACE_H_

#include "SMSInterface.h"

/** Component to use the Short Messages Service (SMS)
 *
 */
class GSMSMSInterface : public ISMSInterface, protected IATCommandsProcessor, IATEventsHandler
{
public:
  /** Create SMSInterface instance
     @param pIf Pointer to the ATCommandsInterface instance to use
   */
  GSMSMSInterface(ATCommandsInterface* pIf);

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

  //IATEventsHandler
  virtual bool isATCodeHandled(const char* atCode); //Is this AT code handled
  virtual void onDispatchStart();
  virtual void onDispatchStop();
  virtual char* getEventsEnableCommand();
  virtual char* getEventsDisableCommand();
  virtual void onEvent(const char* atCode, const char* evt);

  //Updates messages count/references
  int updateInbox();

private:
  ATCommandsInterface* m_pIf;

  //Current message
  char* m_msg;
  size_t m_maxMsgLength;
  char* m_msisdn;

  //Messages list
  int m_msgRefList[MAX_SM];
  size_t m_msgRefListCount;
  bool m_needsUpdate;
  Mutex m_inboxMtx; //To protect concurrent accesses btw the user's thread and the AT thread

  enum { SMS_IDLE, SMS_SEND_CMD_SENT, SMS_GET_CMD_SENT, SMS_GET_HDR_RECEIVED, SMS_GET_COUNT_CMD_SENT, SMS_GET_COUNT_HDR_RECEIVED, SMS_CMD_PROCESSED } m_state;
};

#endif /* GSMSMSINTERFACE_H_ */
