/* IPInterface.h */
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

#ifndef IPINTERFACE_H_
#define IPINTERFACE_H_

#include "core/fwk.h"

/** Generic IP-based network interface
 *
 */
class IPInterface
{
public:
    IPInterface();
    virtual ~IPInterface();

    //int init(); //Initialize interface; no connection should be performed at this stage
    virtual int connect() = 0; //Do connect the interface
    virtual int disconnect() = 0;
    //It is encouraged that the derived class implement a "setup(...)" function to configure the interface before the connection
    
    char* getIPAddress(); //Get IP Address as a string ('a.b.c.d')
    bool isConnected(); //Is the interface connected?

    static IPInterface* getDefaultInterface(); //For use by TCP, UDP sockets library

    //WARN: Implementation will have to be more careful in case of multiple interfaces (or implement a routing protocol based on local IP addresses differentiation)
    void registerAsDefaultInterface(); //First come, first served
    void unregisterAsDefaultInterface(); //Must be called before inst is destroyed to avoid invalid ptr fault

protected:
    //Must be called by subclasses
    void setIPAddress(char* ipAddr);
    void setConnected(bool connected);

private:
    char m_ipAddr[16];
    bool m_connected;

    static IPInterface* s_pDefaultInterface;
};

#endif /* IPINTERFACE_H_ */
