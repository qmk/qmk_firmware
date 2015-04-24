/* Copyright (c) 2010-2012 mbed.org, MIT License
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software
* and associated documentation files (the "Software"), to deal in the Software without
* restriction, including without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
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

#include "USBHostConf.h"

#ifdef USBHOST_3GMODULE

#define __DEBUG__ 0
#ifndef __MODULE__
#define __MODULE__ "WANDongleSerialPort.cpp"
#endif

#include "dbg.h"
#include <stdint.h>
#include "rtos.h"

#include "WANDongleSerialPort.h"

WANDongleSerialPort::WANDongleSerialPort() : cb_tx_en(false), cb_rx_en(false), listener(NULL)
{
  reset();
}

void WANDongleSerialPort::init(USBHost* pHost)
{
  host = pHost;
}

void WANDongleSerialPort::reset()
{
  tx_mtx.lock();
  rx_mtx.lock();

  bulk_in = NULL;
  bulk_out = NULL;

  buf_out_len = 0;
  max_out_size = 0;
  lock_tx = false;
  cb_tx_pending = false;

  buf_in_len = 0;
  buf_in_read_pos = 0;
  lock_rx = false;
  cb_rx_pending = false;

  tx_mtx.unlock();
  rx_mtx.unlock();
}

int WANDongleSerialPort::readPacket()
{
  USB_DBG("Read packet on %p", this);
  rx_mtx.lock();
  if(lock_rx)
  {
    USB_ERR("Fail");
    rx_mtx.unlock();
    return -1;
  }

  if( bulk_in == NULL )
  {
    USB_WARN("Port is disconnected");
    rx_mtx.unlock();
    return -1;
  }

  lock_rx = true; //Receiving
  rx_mtx.unlock();
//  USB_DBG("readPacket");
  //lock_rx.lock();
  USB_TYPE res = host->bulkRead(dev, (USBEndpoint *)bulk_in, buf_in, ((USBEndpoint *)bulk_in)->getSize(), false); //Queue transfer
  if(res != USB_TYPE_PROCESSING)
  {
    //lock_rx.unlock();
    USB_ERR("host->bulkRead() returned %d", res);
    Thread::wait(100);
    return -1;
  }
  return 0;
}

int WANDongleSerialPort::writePacket()
{
  tx_mtx.lock();
  if(lock_tx)
  {
    USB_ERR("Fail");
    tx_mtx.unlock();
    return -1;
  }

  if( bulk_out == NULL )
  {
    USB_WARN("Port is disconnected");
    tx_mtx.unlock();
    return -1;
  }

  lock_tx = true; //Transmitting
  tx_mtx.unlock();
//  USB_DBG("writePacket");

  //lock_tx.lock();
  USB_TYPE res = host->bulkWrite(dev, (USBEndpoint *)bulk_out, buf_out, buf_out_len, false); //Queue transfer
  if(res != USB_TYPE_PROCESSING)
  {
    //lock_tx.unlock();
    USB_ERR("host->bulkWrite() returned %d", res);
    Thread::wait(100);
    return -1;
  }
  return 0;
}

int WANDongleSerialPort::putc(int c)
{
  tx_mtx.lock();
  if(!lock_tx)
  {
    if(buf_out_len < max_out_size)
    {
      buf_out[buf_out_len] = (uint8_t)c;
      buf_out_len++;
    }
  }
  else
  {
    USB_ERR("CAN'T WRITE!");
  }
  tx_mtx.unlock();
  return c;
}

int WANDongleSerialPort::getc()
{
  rx_mtx.lock();
  int c = 0;
  if(!lock_rx)
  {
    if(buf_in_read_pos < buf_in_len)
    {
      c = (int)buf_in[buf_in_read_pos];
      buf_in_read_pos++;
    }
  }
  else
  {
    USB_ERR("CAN'T READ!");
  }
  rx_mtx.unlock();
  return c;
}

int WANDongleSerialPort::readable()
{
  rx_mtx.lock();
  if (lock_rx)
  {
    rx_mtx.unlock();
    return 0;
  }

 /* if( !lock_rx.trylock() )
  {
    return 0;
  }*/
  int res = buf_in_len - buf_in_read_pos;
  //lock_rx.unlock();
  rx_mtx.unlock();
  return res;
}

int WANDongleSerialPort::writeable()
{
  tx_mtx.lock();
  if (lock_tx)
  {
    tx_mtx.unlock();
    return 0;
  }

  /*if( !lock_tx.trylock() )
  {
    return 0;
  }*/
  int res = max_out_size - buf_out_len;
  tx_mtx.unlock();
 //lock_tx.unlock();
  return res;
}

void WANDongleSerialPort::attach(IUSBHostSerialListener* pListener)
{
  if(pListener == NULL)
  {
    setupIrq(false, RxIrq);
    setupIrq(false, TxIrq);
  }
  listener = pListener;
  if(pListener != NULL)
  {
    setupIrq(true, RxIrq);
    setupIrq(true, TxIrq);
  }
}

void WANDongleSerialPort::setupIrq(bool en, IrqType irq /*= RxIrq*/)
{
  switch(irq)
  {
  case RxIrq:
    rx_mtx.lock();
    cb_rx_en = en;
    if(en && cb_rx_pending)
    {
      cb_rx_pending = false;
      rx_mtx.unlock();
      listener->readable(); //Process the interrupt that was raised
    }
    else
    {
      rx_mtx.unlock();
    }
    break;
  case TxIrq:
    tx_mtx.lock();
    cb_tx_en = en;
    if(en && cb_tx_pending)
    {
      cb_tx_pending = false;
      tx_mtx.unlock();
      listener->writeable(); //Process the interrupt that was raised
    }
    else
    {
      tx_mtx.unlock();
    }
    break;
  }
}


void WANDongleSerialPort::connect( USBDeviceConnected* pDev, USBEndpoint* pInEp, USBEndpoint* pOutEp )
{
  dev = pDev;
  bulk_in = pInEp;
  bulk_out = pOutEp;
  max_out_size = bulk_out->getSize();
  if( max_out_size > WANDONGLE_MAX_OUTEP_SIZE )
  {
    max_out_size = WANDONGLE_MAX_OUTEP_SIZE;
  }
  bulk_in->attach(this, &WANDongleSerialPort::rxHandler);
  bulk_out->attach(this, &WANDongleSerialPort::txHandler);
  readPacket(); //Start receiving data
}

void WANDongleSerialPort::disconnect( )
{
    reset();
}

//Private methods


void WANDongleSerialPort::rxHandler()
{
  if (((USBEndpoint *) bulk_in)->getState() == USB_TYPE_IDLE) //Success
  {
    buf_in_read_pos = 0;
    buf_in_len = ((USBEndpoint *) bulk_in)->getLengthTransferred(); //Update length
    //lock_rx.unlock();
    rx_mtx.lock();
    lock_rx = false; //Transmission complete
    if(cb_rx_en)
    {
      rx_mtx.unlock();
      listener->readable(); //Call handler from the IRQ context
      //readPacket() should be called by the handler subsequently once the buffer has been emptied
    }
    else
    {
      cb_rx_pending = true; //Queue the callback
      rx_mtx.unlock();
    }

  }
  else //Error, try reading again
  {
    //lock_rx.unlock();
    USB_DBG("Trying again");
    readPacket();
  }
}

void WANDongleSerialPort::txHandler()
{
  if (((USBEndpoint *) bulk_out)->getState() == USB_TYPE_IDLE) //Success
  {
    tx_mtx.lock();
    buf_out_len = 0; //Reset length
    lock_tx = false; //Transmission complete
    //lock_tx.unlock();
    if(cb_tx_en)
    {
      tx_mtx.unlock();
      listener->writeable(); //Call handler from the IRQ context
      //writePacket() should be called by the handler subsequently once the buffer has been filled
    }
    else
    {
      cb_tx_pending = true; //Queue the callback
      tx_mtx.unlock();
    }
  }
  else //Error, try reading again
  {
    //lock_tx.unlock();
    writePacket();
  }
}

#endif /* USBHOST_3GMODULE */
