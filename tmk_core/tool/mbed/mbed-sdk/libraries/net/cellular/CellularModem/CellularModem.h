/* CellularModem.h */
/* Copyright (C) 2013 mbed.org, MIT License
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

#ifndef CELLULARMODEM_H_
#define CELLULARMODEM_H_

#include "core/fwk.h"
#include "at/ATCommandsInterface.h"

class CellularModem
{
public:
  //Internet-related functions

  /** Open a 3G internet connection
      @return 0 on success, error code on failure
  */
  virtual int connect(const char* apn = NULL, const char* user = NULL, const char* password = NULL) = 0;

  /** Close the internet connection
     @return 0 on success, error code on failure
  */
  virtual int disconnect() = 0;


  /** Send a SM
     @param number The receiver's phone number
     @param message The message to send
     @return 0 on success, error code on failure
   */
  virtual int sendSM(const char* number, const char* message) = 0;


  /** Receive a SM
     @param number Pointer to a buffer to store the sender's phone number (must be at least 17 characters-long, including the sapce for the null-terminating char)
     @param message Pointer to a buffer to store the the incoming message
     @param maxLength Maximum message length that can be stored in buffer (including null-terminating character)
     @return 0 on success, error code on failure
   */
  virtual int getSM(char* number, char* message, size_t maxLength) = 0;

  /** Get the number of SMs in the incoming box
     @param pCount pointer to store the number of unprocessed SMs on
     @return 0 on success, error code on failure
   */
  virtual int getSMCount(size_t* pCount) = 0;

  /** Get the ATCommandsInterface instance
    @return Pointer to the ATCommandsInterface instance
   */
  virtual ATCommandsInterface* getATCommandsInterface() = 0;
  
  /** Switch power on or off
    In order to use this function, a pin name must have been entered in the constructor
    @param enable true to switch the dongle on, false to switch it off
    @return 0 on success, error code on failure
  */
  virtual int power(bool enable) = 0;
};


#endif /* CELLULARMODEM_H_ */
