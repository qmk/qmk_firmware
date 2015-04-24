/* LinkMonitor.h */
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

#ifndef LINKMONITOR_H_
#define LINKMONITOR_H_

#include "core/fwk.h"

#include "rtos.h"

#include "at/ATCommandsInterface.h"

/** Component to monitor link quality
 *
 */
class LinkMonitor : protected IATCommandsProcessor
{
public:
  /** Create LinkMonitor instance
     @param pIf Pointer to the ATCommandsInterface instance to use
   */
  LinkMonitor(ATCommandsInterface* pIf);

  /** Initialize monitor
   */
  int init(bool gsm = true);

  /** Registration State
  */  
  enum REGISTRATION_STATE
  {
    REGISTRATION_STATE_UNKNOWN, //!< Unknown
    REGISTRATION_STATE_REGISTERING, //!< Registering
    REGISTRATION_STATE_DENIED, //!< Denied
    REGISTRATION_STATE_NO_SIGNAL, //!< No Signal
    REGISTRATION_STATE_HOME_NETWORK, //!< Registered on home network
    REGISTRATION_STATE_ROAMING //!< Registered on roaming network
  };

  /** Bearer type
  */
  enum BEARER
  {
    BEARER_UNKNOWN, //!< Unknown
    BEARER_GSM, //!< GSM (2G)
    BEARER_EDGE, //!< EDGE (2.5G)
    BEARER_UMTS, //!< UMTS (3G)
    BEARER_HSPA, //!< HSPA (3G+)
    BEARER_LTE //!< LTE (4G)
  };
  
  /** Get link state
    @param pRssi pointer to store the current RSSI in dBm, between -51 dBm and -113 dBm if known; -51 dBm means -51 dBm or more; -113 dBm means -113 dBm or less; 0 if unknown
    @param pRegistrationState pointer to store the current registration state
    @param pBearer pointer to store the current bearer
    @return 0 on success, error code on failure
  */
  int getState(int* pRssi, REGISTRATION_STATE* pRegistrationState, BEARER* pBearer);
  
  /** Get my phone number
    @param phoneNumber pointer to store the current phoneNumber
    @return 0 on success, error code on failure
  */
  int getPhoneNumber(char* phoneNumber);
protected:
  //IATCommandsProcessor
  virtual int onNewATResponseLine(ATCommandsInterface* pInst, const char* line);
  virtual int onNewEntryPrompt(ATCommandsInterface* pInst);
  
private:
  ATCommandsInterface* m_pIf;
  
  int m_rssi;
  bool m_gsm;
  REGISTRATION_STATE m_registrationState;
  BEARER m_bearer;
  char m_phoneNumber[16];
};

#endif /* LINKMONITOR_H_ */
