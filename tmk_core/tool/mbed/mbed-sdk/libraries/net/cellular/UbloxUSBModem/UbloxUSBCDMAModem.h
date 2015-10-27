/* UbloxUSBCDMAModem.h */
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

#ifndef UBLOXUSBCDMAMODEM_H_
#define UBLOXUSBCDMAMODEM_H_

#include "core/fwk.h"

#include "WANDongle.h"
#include "at/ATCommandsInterface.h"
#include "USBSerialStream.h"
#include "ip/PPPIPInterface.h"
#include "sms/CDMASMSInterface.h"
#include "CellularModem.h"

/** u-blox LISA-C200 modem
 */
class UbloxUSBCDMAModem: public CellularModem
{
public:
  /** Create Sprint USB Modem (Sierra Wireless 598U) API instance
      @param powerGatingPin Optional pin commanding a power gating transistor on the modem's power line 
      @param powerGatingOnWhenPinHigh true if the pin needs to be high to power the dongle, defaults to true
   */
  UbloxUSBCDMAModem(PinName powerGatingPin = NC, bool powerGatingOnWhenPinHigh = true, int serial = 0);

  //Internet-related functions

  /** Open a 3G internet connection
      @return 0 on success, error code on failure
  */
  virtual int connect(const char* apn = NULL, const char* user = NULL, const char* password = NULL);

  /** Close the internet connection
     @return 0 on success, error code on failure
  */
  virtual int disconnect();


  /** Send a SM
     @param number The receiver's phone number
     @param message The message to send
     @return 0 on success, error code on failure
   */
  virtual int sendSM(const char* number, const char* message);


  /** Receive a SM
     @param number Pointer to a buffer to store the sender's phone number (must be at least 17 characters-long, including the sapce for the null-terminating char)
     @param message Pointer to a buffer to store the the incoming message
     @param maxLength Maximum message length that can be stored in buffer (including null-terminating character)
     @return 0 on success, error code on failure
   */
  virtual int getSM(char* number, char* message, size_t maxLength);

  /** Get the number of SMs in the incoming box
     @param pCount pointer to store the number of unprocessed SMs on
     @return 0 on success, error code on failure
   */
  virtual int getSMCount(size_t* pCount);

  /** Get the ATCommandsInterface instance
     @return Pointer to the ATCommandsInterface instance
   */
  virtual ATCommandsInterface* getATCommandsInterface();

  /** Switch power on or off
    In order to use this function, a pin name must have been entered in the constructor
    @param enable true to switch the dongle on, false to switch it off
    @return 0 on success, error code on failure
  */
  virtual int power(bool enable);

protected:
  bool power();
  
  int init();
  int cleanup();

private:
  WANDongle m_dongle;
  
  USBSerialStream m_stream;
  
  ATCommandsInterface m_at;
  
  CDMASMSInterface m_sms;
  
  PPPIPInterface m_ppp;

  bool m_dongleConnected;
  bool m_ipInit;
  bool m_smsInit;
  bool m_atOpen;
  
  PinName m_powerGatingPin;
  bool m_powerGatingOnWhenPinHigh;
};


#endif /* UBLOXUSBCDMAMODEM_H_ */

