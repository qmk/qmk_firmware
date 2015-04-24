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

#ifndef USBDEVICECONNECTED_H
#define USBDEVICECONNECTED_H

#include "stdint.h"
#include "USBEndpoint.h"
#include "USBHostConf.h"
#include "rtos.h"

class USBHostHub;

typedef struct {
    bool in_use;
    uint8_t nb_endpoint;
    uint8_t intf_class;
    uint8_t intf_subclass;
    uint8_t intf_protocol;
    USBEndpoint * ep[MAX_ENDPOINT_PER_INTERFACE];
    FunctionPointer detach;
    char name[10];
} INTERFACE;

/**
* USBDeviceConnected class
*/
class USBDeviceConnected
{
public:

    /**
    * Constructor
    */
    USBDeviceConnected();

    /**
    * Attach an USBEndpoint to this device
    *
    * @param intf_nb interface number
    * @param ep pointeur on the USBEndpoint which will be attached
    * @returns true if successful, false otherwise
    */
    bool addEndpoint(uint8_t intf_nb, USBEndpoint * ep);

    /**
    * Retrieve an USBEndpoint by its TYPE and DIRECTION
    *
    * @param intf_nb the interface on which to lookup the USBEndpoint
    * @param type type of the USBEndpoint looked for
    * @param dir direction of the USBEndpoint looked for
    * @param index the index of the USBEndpoint whitin the interface
    * @returns pointer on the USBEndpoint if found, NULL otherwise
    */
    USBEndpoint * getEndpoint(uint8_t intf_nb, ENDPOINT_TYPE type, ENDPOINT_DIRECTION dir, uint8_t index = 0);

    /**
    * Retrieve an USBEndpoint by its index
    *
    * @param intf_nb interface number
    * @param index index of the USBEndpoint
    * @returns pointer on the USBEndpoint if found, NULL otherwise
    */
    USBEndpoint * getEndpoint(uint8_t intf_nb, uint8_t index);

    /**
    * Add a new interface to this device
    *
    * @param intf_nb interface number
    * @param intf_class interface class
    * @param intf_subclass interface subclass
    * @param intf_protocol interface protocol
    * @returns true if successful, false otherwise
    */
    bool addInterface(uint8_t intf_nb, uint8_t intf_class, uint8_t intf_subclass, uint8_t intf_protocol);

    /**
    * Get a specific interface
    *
    * @param index index of the interface to be fetched
    * @returns interface
    */
    INTERFACE * getInterface(uint8_t index);

    /**
     *  Attach a member function to call when a the device has been disconnected
     *
     *  @param intf_nb interface number
     *  @param tptr pointer to the object to call the member function on
     *  @param mptr pointer to the member function to be called
     */
    template<typename T>
    inline void onDisconnect(uint8_t intf_nb, T* tptr, void (T::*mptr)(void)) {
        if ((mptr != NULL) && (tptr != NULL)) {
            intf[intf_nb].detach.attach(tptr, mptr);
        }
    }

    /**
     * Attach a callback called when the device has been disconnected
     *
     *  @param intf_nb interface number
     *  @param fn function pointer
     */
    inline void onDisconnect(uint8_t intf_nb, void (*fn)(void)) {
        if (fn != NULL) {
            intf[intf_nb].detach.attach(fn);
        }
    }

    /**
    * Disconnect the device by calling a callback function registered by a driver
    */
    void disconnect();

    // setters
    void init(uint8_t hub, uint8_t port, bool lowSpeed);
    inline void setAddress(uint8_t addr_) { addr = addr_; };
    inline void setVid(uint16_t vid_) { vid = vid_; };
    inline void setPid(uint16_t pid_) { pid = pid_; };
    inline void setClass(uint8_t device_class_) { device_class = device_class_; };
    inline void setSubClass(uint8_t device_subclass_) { device_subclass = device_subclass_; };
    inline void setProtocol(uint8_t pr) { proto = pr; };
    inline void setSizeControlEndpoint(uint32_t size) { sizeControlEndpoint = size; };
    inline void activeAddress(bool active) { activeAddr = active; };
    inline void setEnumerated() { enumerated = true; };
    inline void setNbIntf(uint8_t nb_intf) {nb_interf = nb_intf; };
    inline void setHubParent(USBHostHub * hub) { hub_parent = hub; };
    inline void setName(const char * name_, uint8_t intf_nb) { strcpy(intf[intf_nb].name, name_); };

    //getters
    inline uint8_t     getPort() { return port; };
    inline uint8_t     getHub() { return hub_nb; };
    inline uint8_t     getAddress() { return addr; };
    inline uint16_t    getVid() { return vid; };
    inline uint16_t    getPid() { return pid; };
    inline uint8_t     getClass() { return device_class; };
    inline uint8_t     getSubClass() { return device_subclass; };
    inline uint8_t     getProtocol() { return proto; };
    inline bool        getSpeed() { return speed; };
    inline uint32_t    getSizeControlEndpoint() { return sizeControlEndpoint; };
    inline bool        isActiveAddress() { return activeAddr; };
    inline bool        isEnumerated() { return enumerated; };
    inline USBHostHub * getHubParent() { return hub_parent; };
    inline uint8_t      getNbIntf() { return nb_interf; };
    inline const char * getName(uint8_t intf_nb) { return intf[intf_nb].name; };

    // in case this device is a hub
    USBHostHub * hub;

private:
    USBHostHub * hub_parent;

    INTERFACE intf[MAX_INTF];
    uint32_t sizeControlEndpoint;
    uint8_t hub_nb;
    uint8_t port;
    uint16_t vid;
    uint16_t pid;
    uint8_t addr;
    uint8_t device_class;
    uint8_t device_subclass;
    uint8_t proto;
    bool speed;
    volatile bool activeAddr;
    volatile bool enumerated;
    uint8_t nb_interf;

    void init();
};

#endif
