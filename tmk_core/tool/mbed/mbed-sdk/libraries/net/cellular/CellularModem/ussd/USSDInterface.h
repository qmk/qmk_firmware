/* USSDInterface.h */
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

#ifndef USSDINTERFACE_H_
#define USSDINTERFACE_H_

#include "core/fwk.h"

#include "rtos.h"

#include "at/ATCommandsInterface.h"

/** Component to send/receive Unstructured Supplementary Service Data (USSD)
 *
 */
class USSDInterface : protected IATCommandsProcessor, IATEventsHandler
{
public:
  /** Create USSDInterface instance
     @param pIf Pointer to the ATCommandsInterface instance to use
   */
  USSDInterface(ATCommandsInterface* pIf);

  /** Initialize interface
   Configure USSD commands & register for USSD-related unsolicited result codes
  */
  int init();

  /** Send a USSD command & wait for its result
    @param command The command to send
    @param result Buffer in which to store the result
    @param maxLength Maximum result length that can be stored in buffer (including null-terminating character)
    @return 0 on success, error code on failure
  */
  int send(const char* command, char* result, size_t maxLength);

protected:
  //IATCommandsProcessor, needed for implementations of 3GGP standard < r06
  virtual int onNewATResponseLine(ATCommandsInterface* pInst, const char* line);
  virtual int onNewEntryPrompt(ATCommandsInterface* pInst);
  
  //IATEventsHandler, needed for implementations of 3GGP standard >= r06
  virtual bool isATCodeHandled(const char* atCode); //Is this AT code handled
  virtual void onDispatchStart();
  virtual void onDispatchStop();
  virtual char* getEventsEnableCommand();
  virtual char* getEventsDisableCommand();
  virtual void onEvent(const char* atCode, const char* evt);

private:
  void processResult(const char* data);

  ATCommandsInterface* m_pIf;
  Mutex m_responseMtx; //To protect concurrent accesses btw the user's thread and the AT thread
  Semaphore m_responseSphre;

  //Result
  volatile char* m_result;
  volatile size_t m_maxResultLength;

};


#endif /* USSDINTERFACE_H_ */
