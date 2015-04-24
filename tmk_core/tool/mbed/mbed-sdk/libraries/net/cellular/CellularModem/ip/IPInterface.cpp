/* IPInterface.cpp */
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

#include "IPInterface.h"

#include <cstring> //For strcpy


IPInterface::IPInterface() : m_connected(false)
{

}

/*virtual*/ IPInterface::~IPInterface()
{

}

void IPInterface::registerAsDefaultInterface() //First come, first served
{
  s_pDefaultInterface = this;
}

void IPInterface::unregisterAsDefaultInterface() //Must be called before inst is destroyed to avoid invalid ptr fault
{
  s_pDefaultInterface = NULL;
}

/*static*/ IPInterface* IPInterface::getDefaultInterface() //For use by TCP, UDP sockets library
{
  return s_pDefaultInterface;
}

/*static*/ IPInterface* IPInterface::s_pDefaultInterface = NULL;


char* IPInterface::getIPAddress() //Get IP Address as a string ('a.b.c.d')
{
  if(isConnected())
  {
    return m_ipAddr;
  }
  else
  {
    return NULL;
  }
}

bool IPInterface::isConnected() //Is the interface connected?
{
  return m_connected;
}

void IPInterface::setIPAddress(char* ipAddr)
{
  std::strcpy(m_ipAddr, ipAddr); //Let's trust the derived class not to buffer overflow us
}

void IPInterface::setConnected(bool connected)
{
  m_connected = connected;
}

