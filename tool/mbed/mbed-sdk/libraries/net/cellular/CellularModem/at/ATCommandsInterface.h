/* ATCommandsInterface.h */
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

#ifndef ATCOMMANDSINTERFACE_H_
#define ATCOMMANDSINTERFACE_H_

#include "core/fwk.h"
#include "rtos.h"

#define MAX_AT_EVENTS_HANDLERS 4

class ATCommandsInterface;

/** Interface implemented by components handling AT events
 *
 */
class IATEventsHandler
{
protected:
  virtual bool isATCodeHandled(const char* atCode) = 0; //Is this AT code handled
  virtual void onDispatchStart() = 0;
  virtual void onDispatchStop() = 0;
  virtual char* getEventsEnableCommand() = 0;
  virtual char* getEventsDisableCommand() = 0;
  virtual void onEvent(const char* atCode, const char* evt) = 0;
  friend class ATCommandsInterface;
};

/** Interface implemented by components executing complex AT commands
 *
 */
class IATCommandsProcessor
{
protected:
  virtual int onNewATResponseLine(ATCommandsInterface* pInst, const char* line) = 0;
  virtual int onNewEntryPrompt(ATCommandsInterface* pInst) = 0;
  friend class ATCommandsInterface;
};

#define AT_INPUT_BUF_SIZE 192//64

//Signals to be sent to the processing thread
#define AT_SIG_PROCESSING_START 1
#define AT_SIG_PROCESSING_STOP 2
//Messages to be sent to the processing thread
#define AT_CMD_READY 1
#define AT_TIMEOUT 2
#define AT_STOP 3
//Messages to be sent from the processing thread
#define AT_RESULT_READY 1

/** AT Commands interface class
 *
 */
class ATCommandsInterface : protected IATCommandsProcessor
{
public:
  ATCommandsInterface(IOStream* pStream);

  //Open connection to AT Interface in order to execute command & register/unregister events
  int open();

  //Initialize AT link
  int init(bool reset = true);

  //Close connection
  int close();
  
  bool isOpen();

  class ATResult
  {
  public:
    enum { AT_OK, AT_ERROR, AT_CONNECT, AT_CMS_ERROR, AT_CME_ERROR } result;
    int code;
  };

  int executeSimple(const char* command, ATResult* pResult, uint32_t timeout=1000);
  int execute(const char* command, IATCommandsProcessor* pProcessor, ATResult* pResult, uint32_t timeout=1000);
  
  int registerEventsHandler(IATEventsHandler* pHdlr);
  int deregisterEventsHandler(IATEventsHandler* pHdlr);

  //Commands that can be called during onNewATResponseLine callback, additionally to close()
  //Access to this method is protected (can ONLY be called on processing thread during IATCommandsProcessor::onNewATResponseLine execution)
  int sendData(const char* data);

  static void staticCallback(void const* p);
private:
  int executeInternal(const char* command, IATCommandsProcessor* pProcessor, ATResult* pResult, uint32_t timeout=1000);
  
  int tryReadLine();
  int trySendCommand();
  int processReadLine();
  int processEntryPrompt();
  
  void enableEvents();
  void disableEvents();

  int ATResultToReturnCode(ATResult result); //Helper

  virtual int onNewATResponseLine(ATCommandsInterface* pInst, const char* line); //Default implementation for simple commands handling
  virtual int onNewEntryPrompt(ATCommandsInterface* pInst); //Default implementation (just sends Ctrl+Z to exit the prompt)

  void process(); //Processing thread

  IOStream* m_pStream;
  
  bool m_open; //< TRUE when the AT interface is open, and FALSE when it is not.

  const char* m_transactionCommand;
  const char* m_transactionData;

  IATCommandsProcessor* m_pTransactionProcessor;
  ATResult m_transactionResult;

  enum { IDLE, COMMAND_SENT, READING_RESULT, ABORTED } m_transactionState;

  char m_inputBuf[AT_INPUT_BUF_SIZE]; // Stores characters received from the modem.
  int m_inputPos; // Current position of fill pointer in the input buffer.

  Mutex m_transactionMtx;

  // These are RTOS queues, concurrent access protected. In this case both only contain an integer.
  Mail<int,1> m_env2AT; // used by calling function to inform processing thread of events
  Mail<int,1> m_AT2Env; // used by processing thread to inform calling function of events

  IATEventsHandler* m_eventsHandlers[MAX_AT_EVENTS_HANDLERS]; // all registered events handlers

  Mutex m_processingMtx;
  Thread m_processingThread;

  Mutex m_eventsMgmtMtx; //Lock events use within the calling thread
  Mutex m_eventsProcessingMtx; //Lock events use within the processing thread
};

#endif /* ATCOMMANDSINTERFACE_H_ */
