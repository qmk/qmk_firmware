/* Copyright (c) 2010-2011 mbed.org, MIT License
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

#ifndef USBBUSINTERFACE_H
#define USBBUSINTERFACE_H

#include "mbed.h"
#include "USBEndpoints.h"
#include "toolchain.h"

//#ifdef __GNUC__
//#define __packed __attribute__ ((__packed__))
//#endif

class USBHAL {
public:
    /* Configuration */
    USBHAL();
    ~USBHAL();
    void connect(void);
    void disconnect(void);
    void configureDevice(void);
    void unconfigureDevice(void);
    void setAddress(uint8_t address);
    void remoteWakeup(void);

    /* Endpoint 0 */
    void EP0setup(uint8_t *buffer);
    void EP0read(void);
    void EP0readStage(void);
    uint32_t EP0getReadResult(uint8_t *buffer);
    void EP0write(uint8_t *buffer, uint32_t size);
    void EP0getWriteResult(void);
    void EP0stall(void);

    /* Other endpoints */
    EP_STATUS endpointRead(uint8_t endpoint, uint32_t maximumSize);
    EP_STATUS endpointReadResult(uint8_t endpoint, uint8_t *data, uint32_t *bytesRead);
    EP_STATUS endpointWrite(uint8_t endpoint, uint8_t *data, uint32_t size);
    EP_STATUS endpointWriteResult(uint8_t endpoint);
    void stallEndpoint(uint8_t endpoint);
    void unstallEndpoint(uint8_t endpoint);
    bool realiseEndpoint(uint8_t endpoint, uint32_t maxPacket, uint32_t options);
    bool getEndpointStallState(unsigned char endpoint);
    uint32_t endpointReadcore(uint8_t endpoint, uint8_t *buffer);

protected:
    virtual void busReset(void){};
    virtual void EP0setupCallback(void){};
    virtual void EP0out(void){};
    virtual void EP0in(void){};
    virtual void connectStateChanged(unsigned int connected){};
    virtual void suspendStateChanged(unsigned int suspended){};
    virtual void SOF(int frameNumber){};

    virtual bool EP1_OUT_callback(){return false;};
    virtual bool EP1_IN_callback(){return false;};
    virtual bool EP2_OUT_callback(){return false;};
    virtual bool EP2_IN_callback(){return false;};
    virtual bool EP3_OUT_callback(){return false;};
    virtual bool EP3_IN_callback(){return false;};
#if !defined(TARGET_STM32F4)
    virtual bool EP4_OUT_callback(){return false;};
    virtual bool EP4_IN_callback(){return false;};
#if !(defined(TARGET_LPC11UXX) || defined(TARGET_LPC11U6X) || defined(TARGET_LPC1347) || defined(TARGET_LPC1549))
    virtual bool EP5_OUT_callback(){return false;};
    virtual bool EP5_IN_callback(){return false;};
    virtual bool EP6_OUT_callback(){return false;};
    virtual bool EP6_IN_callback(){return false;};
    virtual bool EP7_OUT_callback(){return false;};
    virtual bool EP7_IN_callback(){return false;};
    virtual bool EP8_OUT_callback(){return false;};
    virtual bool EP8_IN_callback(){return false;};
    virtual bool EP9_OUT_callback(){return false;};
    virtual bool EP9_IN_callback(){return false;};
    virtual bool EP10_OUT_callback(){return false;};
    virtual bool EP10_IN_callback(){return false;};
    virtual bool EP11_OUT_callback(){return false;};
    virtual bool EP11_IN_callback(){return false;};
    virtual bool EP12_OUT_callback(){return false;};
    virtual bool EP12_IN_callback(){return false;};
    virtual bool EP13_OUT_callback(){return false;};
    virtual bool EP13_IN_callback(){return false;};
    virtual bool EP14_OUT_callback(){return false;};
    virtual bool EP14_IN_callback(){return false;};
    virtual bool EP15_OUT_callback(){return false;};
    virtual bool EP15_IN_callback(){return false;};
#endif
#endif

private:
    void usbisr(void);
    static void _usbisr(void);
    static USBHAL * instance;

#if defined(TARGET_LPC11UXX) || defined(TARGET_LPC11U6X) || defined(TARGET_LPC1347) || defined(TARGET_LPC1549)
        bool (USBHAL::*epCallback[10 - 2])(void);
#elif defined(TARGET_STM32F4)
        bool (USBHAL::*epCallback[8 - 2])(void);
#else
        bool (USBHAL::*epCallback[32 - 2])(void);
#endif


};
#endif
