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

#ifndef USBHOSTHUB_H
#define USBHOSTHUB_H

#include "USBHostConf.h"

#if MAX_HUB_NB

#include "USBHostTypes.h"
#include "IUSBEnumerator.h"

class USBHost;
class USBDeviceConnected;
class USBEndpoint;

/**
 * A class to use a USB Hub
 */
class USBHostHub : public IUSBEnumerator {
public:
    /**
    * Constructor
    */
    USBHostHub();

    /**
    * Check if a USB Hub is connected
    *
    * @return true if a serial device is connected
    */
    bool connected();

    /**
     * Try to connect device
     *
     * @param dev device to connect
     * @return true if connection was successful
     */
    bool connect(USBDeviceConnected * dev);

    /**
    * Automatically called by USBHost when a device
    * has been enumerated by usb_thread
    *
    * @param dev device connected
    */
    void deviceConnected(USBDeviceConnected * dev);

    /**
    * Automatically called by USBHost when a device
    * has been disconnected from this hub
    *
    * @param dev device disconnected
    */
    void deviceDisconnected(USBDeviceConnected * dev);

    /**
    * Rest a specific port
    *
    * @param port port number
    */
    void portReset(uint8_t port);

    /*
    * Called by USBHost to set the instance of USBHost
    *
    * @param host host instance
    */
    void setHost(USBHost * host);

    /**
    * Called by USBhost when a hub has been disconnected
    */
    void hubDisconnected();

protected:
    //From IUSBEnumerator
    virtual void setVidPid(uint16_t vid, uint16_t pid);
    virtual bool parseInterface(uint8_t intf_nb, uint8_t intf_class, uint8_t intf_subclass, uint8_t intf_protocol); //Must return true if the interface should be parsed
    virtual bool useEndpoint(uint8_t intf_nb, ENDPOINT_TYPE type, ENDPOINT_DIRECTION dir); //Must return true if the endpoint will be used

private:
    USBHost * host;
    USBDeviceConnected * dev;
    bool dev_connected;
    USBEndpoint * int_in;
    uint8_t nb_port;
    uint8_t hub_characteristics;

    void rxHandler();

    uint8_t buf[sizeof(HubDescriptor)];

    int hub_intf;
    bool hub_device_found;

    void setPortFeature(uint32_t feature, uint8_t port);
    void clearPortFeature(uint32_t feature, uint8_t port);
    uint32_t getPortStatus(uint8_t port);

    USBDeviceConnected * device_children[MAX_HUB_PORT];

    void init();
    void disconnect();

};

#endif

#endif
