/* mbed USBHost Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef USBENDPOINT_H
#define USBENDPOINT_H

#include "FunctionPointer.h"
#include "USBHostTypes.h"
#include "rtos.h"

class USBDeviceConnected;

/**
* USBEndpoint class
*/
class USBEndpoint
{
public:
    /**
    * Constructor
    */
    USBEndpoint() {
        state = USB_TYPE_FREE;
        nextEp = NULL;
    };

    /**
    * Initialize an endpoint
    *
    * @param hced hced associated to the endpoint
    * @param type endpoint type
    * @param dir endpoint direction
    * @param size endpoint size
    * @param ep_number endpoint number
    * @param td_list array of two allocated transfer descriptors
    */
    void init(HCED * hced, ENDPOINT_TYPE type, ENDPOINT_DIRECTION dir, uint32_t size, uint8_t ep_number, HCTD* td_list[2]);

    /**
    * Set next token. Warning: only useful for the control endpoint
    *
    * @param token IN, OUT or SETUP token
    */
    void setNextToken(uint32_t token);

    /**
    * Queue an endpoint
    *
    * @param endpoint endpoint which will be queued in the linked list
    */
    void queueEndpoint(USBEndpoint * endpoint);


    /**
    * Queue a transfer on the endpoint
    */
    void queueTransfer();

    /**
    * Unqueue a transfer from the endpoint
    *
    * @param td hctd which will be unqueued
    */
    void unqueueTransfer(volatile HCTD * td);

    /**
     *  Attach a member function to call when a transfer is finished
     *
     *  @param tptr pointer to the object to call the member function on
     *  @param mptr pointer to the member function to be called
     */
    template<typename T>
    inline void attach(T* tptr, void (T::*mptr)(void)) {
        if((mptr != NULL) && (tptr != NULL)) {
            rx.attach(tptr, mptr);
        }
    }

    /**
     * Attach a callback called when a transfer is finished
     *
     * @param fptr function pointer
     */
    inline void attach(void (*fptr)(void)) {
        if(fptr != NULL) {
            rx.attach(fptr);
        }
    }

    /**
    * Call the handler associted to the end of a transfer
    */
    inline void call() {
        rx.call();
    };


    // setters
    inline void setState(USB_TYPE st) { state = st; }
    void setState(uint8_t st);
    void setDeviceAddress(uint8_t addr);
    inline void setLengthTransferred(int len) { transferred = len; };
    void setSpeed(uint8_t speed);
    void setSize(uint32_t size);
    inline void setDir(ENDPOINT_DIRECTION d) { dir = d; }
    inline void setIntfNb(uint8_t intf_nb_) { intf_nb = intf_nb_; };

    // getters
    const char *                getStateString();
    inline USB_TYPE             getState() { return state; }
    inline ENDPOINT_TYPE        getType() { return type; };
    inline uint8_t              getDeviceAddress() { return hced->control & 0x7f; };
    inline int                  getLengthTransferred() { return transferred; }
    inline uint8_t *            getBufStart() { return buf_start; }
    inline uint8_t              getAddress(){ return address; };
    inline uint32_t             getSize() { return (hced->control >> 16) & 0x3ff; };
    inline volatile HCTD *      getHeadTD() { return (volatile HCTD*) ((uint32_t)hced->headTD & ~0xF); };
    inline volatile HCTD**      getTDList() { return td_list; };
    inline volatile HCED *      getHCED() { return hced; };
    inline ENDPOINT_DIRECTION   getDir() { return dir; }
    inline volatile HCTD *      getProcessedTD() { return td_current; };
    inline volatile HCTD*       getNextTD() { return td_current; };
    inline bool                 isSetup() { return setup; }
    inline USBEndpoint *        nextEndpoint() { return (USBEndpoint*)nextEp; };
    inline uint8_t              getIntfNb() { return intf_nb; };

    USBDeviceConnected * dev;

    Queue<uint8_t, 1> ep_queue;

private:
    ENDPOINT_TYPE type;
    volatile USB_TYPE state;
    ENDPOINT_DIRECTION dir;
    bool setup;

    uint8_t address;

    int transfer_len;
    int transferred;
    uint8_t * buf_start;

    FunctionPointer rx;

    USBEndpoint* nextEp;

    // USBEndpoint descriptor
    volatile HCED * hced;

    volatile HCTD * td_list[2];
    volatile HCTD * td_current;
    volatile HCTD * td_next;

    uint8_t intf_nb;

};

#endif
