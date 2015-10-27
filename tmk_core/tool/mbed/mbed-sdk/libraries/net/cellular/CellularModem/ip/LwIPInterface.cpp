/* LwIPInterface.cpp */
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


#include "core/fwk.h"

#include "LwIPInterface.h"

extern "C" {
#include "lwip/init.h"
#include "lwip/tcpip.h"
}

LwIPInterface::LwIPInterface() : IPInterface(), m_rdySphre(1)
{
  m_rdySphre.wait();
}

LwIPInterface::~LwIPInterface()
{

}

int LwIPInterface::init() //Init LwIP-specific stuff, create the right bindings, etc
{
  //lwip_init(); //All LwIP initialisation functions called on a per-module basis (according to lwipopts.h)
  tcpip_init(LwIPInterface::tcpipRdyCb, this); //Start TCP/IP processing thread
  m_rdySphre.wait(); //Wait for callback to produce resource
  return OK;
}

/*static*/ void LwIPInterface::tcpipRdyCb(void* ctx) //Result of TCP/IP thread launch
{
  LwIPInterface* pIf = (LwIPInterface*) ctx;
  pIf->m_rdySphre.release();
}
