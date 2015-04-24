/* IOSerialStream.cpp */
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

#define __DEBUG__ 0 //Maximum verbosity
#ifndef __MODULE__
#define __MODULE__ "IOSerialStream.cpp"
#endif

#include "core/fwk.h"

#include <cstring>

#include "IOSerialStream.h"

#define UART_X ((LPC_UART_TypeDef *)(UART_1))

IOSerialStream::IOSerialStream(mbed::RawSerial& serial) : m_serial(serial), m_serialTxFifoEmpty(true),
m_availableSphre(1), m_spaceSphre(1), m_inBuf(), m_outBuf()
{
  m_availableSphre.wait();
  m_spaceSphre.wait();
  //Attach interrupts
  m_serial.attach(this, &IOSerialStream::readable, mbed::SerialBase::RxIrq);
  m_serial.attach(this, &IOSerialStream::writeable, mbed::SerialBase::TxIrq);
}

/*virtual*/ IOSerialStream::~IOSerialStream()
{
  m_serial.attach(NULL, mbed::SerialBase::RxIrq);
  m_serial.attach(NULL, mbed::SerialBase::TxIrq);
}

//0 for non-blocking (returns immediately), osWaitForever for infinite blocking
/*virtual*/ int IOSerialStream::read(uint8_t* buf, size_t* pLength, size_t maxLength, uint32_t timeout/*=osWaitForever*/)
{
  DBG("Trying to read at most %d chars", maxLength);
  int ret = waitAvailable(timeout);
  if(ret)
  {
    WARN("Error %d while waiting for incoming data", ret);
    return ret;
  }
  int readLen = MIN( available(), maxLength );
  *pLength = readLen;
  setupReadableISR(false);
  while(readLen--)
  {
    m_inBuf.dequeue(buf);
    buf++;
  }
  setupReadableISR(true);
  DBG("Read %d chars successfully", *pLength);
  return OK;
}

/*virtual*/ size_t IOSerialStream::available()
{
  setupReadableISR(false); //m_inBuf.available() is not reentrant
  size_t len = m_inBuf.available();
  setupReadableISR(true);
  return len;
}

/*virtual*/ int IOSerialStream::waitAvailable(uint32_t timeout/*=osWaitForever*/) //Wait for data to be available
{
  int ret;
  if(available()) //Is data already available?
  {
    m_availableSphre.wait(0); //Clear the queue as data is available
    return OK;
  }

  DBG("Waiting for data availability %d ms (-1 is infinite)", timeout);
  ret = m_availableSphre.wait(timeout); //Wait for data to arrive or for abort
  if(ret <= 0)
  {
    DBG("Timeout");
    return NET_TIMEOUT;
  }
  if(!available()) //Even if abort has been called, return that data is available
  {
    DBG("Aborted");
    return NET_INTERRUPTED;
  }
  DBG("Finished waiting");
  m_availableSphre.wait(0); //Clear the queue as data is available
  return OK;
}

/*virtual*/ int IOSerialStream::abortRead() //Abort current reading (or waiting) operation
{
  if( !available() ) //If there is data pending, no need to abort
  {
    m_availableSphre.release(); //Force exiting the waiting state; kludge to pass a RC directly
  }
  else
  {
    DBG("Serial is readable"); ;
  }
  return OK;
}

void IOSerialStream::setupReadableISR(bool en)
{
  if(en)
  {
    UART_X->IER |= 1 << 0;
  }
  else
  {
    UART_X->IER &= ~(1 << 0);
  }
}

void IOSerialStream::readable() //Callback from m_serial when new data is available
{
  do
  {
    m_inBuf.queue(m_serial.getc());
  } while(m_serial.readable());
  m_availableSphre.release(); //Force exiting the waiting state
}

//0 for non-blocking (returns immediately), osWaitForever for infinite blocking
/*virtual*/ int IOSerialStream::write(uint8_t* buf, size_t length, uint32_t timeout/*=osWaitForever*/)
{
  DBG("Trying to write %d chars", length);
  int ret = waitSpace(timeout);
  if(ret)
  {
    WARN("Error %d while waiting for space", ret);
    return ret;
  }
  DBG("Writing %d chars", length);
  setupWriteableISR(false);
  while(length)
  {
    m_outBuf.queue(*buf);
    buf++;
    length--;
    if(length && !space())
    {
      DBG("Waiting to write remaining %d chars", length);
      setupWriteableISR(true);
      ret = waitSpace(timeout);
      if(ret)
      {
        WARN("Error %d while waiting for space", ret);
        return ret;
      }
      setupWriteableISR(false);
    }
  }
  //If m_serial tx fifo is empty we need to manually tx a byte in order to trigger the interrupt
  if( m_outBuf.available() && m_serialTxFifoEmpty )
  {
    m_serialTxFifoEmpty = false;
    uint8_t c;
    m_outBuf.dequeue(&c);
    m_serial.putc((char)c);
  }
  setupWriteableISR(true);
  DBG("Write successful");
  return OK;
}

/*virtual*/ size_t IOSerialStream::space()
{
  setupWriteableISR(false); //m_outBuf.available() is not reentrant
  size_t len = CIRCBUF_SIZE - m_outBuf.available();
  setupWriteableISR(true);
  return len;
}

/*virtual*/ int IOSerialStream::waitSpace(uint32_t timeout/*=osWaitForever*/) //Wait for space to be available
{
  int ret;
  if(space()) //Is still space already left?
  {
    m_spaceSphre.wait(0); //Clear the queue as space is available
    return OK;
  }

  DBG("Waiting for data space %d ms (-1 is infinite)", timeout);
  ret = m_spaceSphre.wait(timeout); //Wait for space to be made or for abort
  if(ret <= 0)
  {
    DBG("Timeout");
    return NET_TIMEOUT;
  }
  if(!space()) //Even if abort has been called, return that space is available
  {
    DBG("Aborted");
    return NET_INTERRUPTED;
  }
  m_spaceSphre.wait(0); //Clear the queue as space is available
  return OK;
}

/*virtual*/ int IOSerialStream::abortWrite() //Abort current writing (or waiting) operation
{
  if( !space() ) //If there is space left, no need to abort
  {
    m_spaceSphre.release(); //Force exiting the waiting state
  }
  return OK;
}

void IOSerialStream::setupWriteableISR(bool en)
{
  if(en)
  {
    UART_X->IER |= 1 << 1;
  }
  else
  {
    UART_X->IER &= ~(1 << 1);
  }
}

void IOSerialStream::writeable() //Callback from m_serial when new space is available
{
  if(m_outBuf.isEmpty())
  {
    m_serialTxFifoEmpty = true;
  }
  else
  {
    while(m_serial.writeable() && !m_outBuf.isEmpty())
    {
      uint8_t c;
      m_outBuf.dequeue(&c);
      m_serial.putc((char)c);
    }
  }
  m_spaceSphre.release(); //Force exiting the waiting state
}
