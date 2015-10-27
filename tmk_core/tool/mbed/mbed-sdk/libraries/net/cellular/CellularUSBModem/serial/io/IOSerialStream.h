/* IOSerialStream.h */
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
#ifndef IOSERIALSTREAM_H_
#define IOSERIALSTREAM_H_

#include "core/fwk.h"

#include "RawSerial.h"

#include "rtos.h"
#include "core/MtxCircBuffer.h"

/** Input Serial Stream for physical serial interfaces (UART...)
This class is not thread-safe, except for the *Abort() methods that can be called by any thread/ISR
*/
class IOSerialStream : public IOStream
{
public:
  enum { CIRCBUF_SIZE = 255 };
  IOSerialStream(mbed::RawSerial& serial);
  /*virtual*/ ~IOSerialStream();

  //0 for non-blocking (returns immediately), osWaitForever for infinite blocking
  virtual int read(uint8_t* buf, size_t* pLength, size_t maxLength, uint32_t timeout=osWaitForever);
  virtual size_t available();
  virtual int waitAvailable(uint32_t timeout=osWaitForever); //Wait for data to be available
  virtual int abortRead(); //Abort current reading (or waiting) operation


  //0 for non-blocking (returns immediately), osWaitForever for infinite blocking
  virtual int write(uint8_t* buf, size_t length, uint32_t timeout=osWaitForever);
  virtual size_t space();
  virtual int waitSpace(uint32_t timeout=osWaitForever); //Wait for space to be available
  virtual int abortWrite(); //Abort current writing (or waiting) operation

private:

  mbed::RawSerial& m_serial;
  volatile bool m_serialTxFifoEmpty;

  void setupReadableISR(bool en);
  void readable(); //Callback from m_serial when new data is available

  Semaphore m_availableSphre; //Used for signalling

  void setupWriteableISR(bool en);
  void writeable(); //Callback from m_serial when new space is available

  Semaphore m_spaceSphre; //Used for signalling

  MtxCircBuffer<uint8_t, CIRCBUF_SIZE + 1> m_inBuf;
  MtxCircBuffer<uint8_t, CIRCBUF_SIZE + 1> m_outBuf;

};

#endif /* IOSERIALSTREAM_H_ */
