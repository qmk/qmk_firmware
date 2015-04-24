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

#ifndef USBHOST_H
#define USBHOST_H

#include "USBHALHost.h"
#include "USBDeviceConnected.h"
#include "IUSBEnumerator.h"
#include "USBHostConf.h"
#include "rtos.h"
#include "dbg.h"
#include "USBHostHub.h"

/**
* USBHost class
*   This class is a singleton. All drivers have a reference on the static USBHost instance
*/
class USBHost : public USBHALHost {
public:
    /**
    * Static method to create or retrieve the single USBHost instance
    */
    static USBHost * getHostInst();

    /**
    * Control read: setup stage, data stage and status stage
    *
    * @param dev the control read will be done for this device
    * @param requestType request type
    * @param request request
    * @param value value
    * @param index index
    * @param buf pointer on a buffer where will be store the data received
    * @param len length of the transfer
    *
    * @returns status of the control read
    */
    USB_TYPE controlRead(USBDeviceConnected * dev, uint8_t requestType, uint8_t request, uint32_t value, uint32_t index, uint8_t * buf, uint32_t len);

    /**
    * Control write: setup stage, data stage and status stage
    *
    * @param dev the control write will be done for this device
    * @param requestType request type
    * @param request request
    * @param value value
    * @param index index
    * @param buf pointer on a buffer which will be written
    * @param len length of the transfer
    *
    * @returns status of the control write
    */
    USB_TYPE controlWrite(USBDeviceConnected * dev, uint8_t requestType, uint8_t request, uint32_t value, uint32_t index, uint8_t * buf, uint32_t len);

    /**
    * Bulk read
    *
    * @param dev the bulk transfer will be done for this device
    * @param ep USBEndpoint which will be used to read a packet
    * @param buf pointer on a buffer where will be store the data received
    * @param len length of the transfer
    * @param blocking if true, the read is blocking (wait for completion)
    *
    * @returns status of the bulk read
    */
    USB_TYPE bulkRead(USBDeviceConnected * dev, USBEndpoint * ep, uint8_t * buf, uint32_t len, bool blocking = true);

    /**
    * Bulk write
    *
    * @param dev the bulk transfer will be done for this device
    * @param ep USBEndpoint which will be used to write a packet
    * @param buf pointer on a buffer which will be written
    * @param len length of the transfer
    * @param blocking if true, the write is blocking (wait for completion)
    *
    * @returns status of the bulk write
    */
    USB_TYPE bulkWrite(USBDeviceConnected * dev, USBEndpoint * ep, uint8_t * buf, uint32_t len, bool blocking = true);

    /**
    * Interrupt read
    *
    * @param dev the bulk transfer will be done for this device
    * @param ep USBEndpoint which will be used to write a packet
    * @param buf pointer on a buffer which will be written
    * @param len length of the transfer
    * @param blocking if true, the read is blocking (wait for completion)
    *
    * @returns status of the interrupt read
    */
    USB_TYPE interruptRead(USBDeviceConnected * dev, USBEndpoint * ep, uint8_t * buf, uint32_t len, bool blocking = true);

    /**
    * Interrupt write
    *
    * @param dev the bulk transfer will be done for this device
    * @param ep USBEndpoint which will be used to write a packet
    * @param buf pointer on a buffer which will be written
    * @param len length of the transfer
    * @param blocking if true, the write is blocking (wait for completion)
    *
    * @returns status of the interrupt write
    */
    USB_TYPE interruptWrite(USBDeviceConnected * dev, USBEndpoint * ep, uint8_t * buf, uint32_t len, bool blocking = true);

    /**
    * Enumerate a device.
    *
    * @param dev device which will be enumerated
    *
    * @returns status of the enumeration
    */
    USB_TYPE enumerate(USBDeviceConnected * dev, IUSBEnumerator* pEnumerator);

    /**
    * reset a specific device
    *
    * @param dev device which will be resetted
    */
    USB_TYPE resetDevice(USBDeviceConnected * dev);

    /**
    * Get a device
    *
    * @param index index of the device which will be returned
    *
    * @returns pointer on the "index" device
    */
    USBDeviceConnected * getDevice(uint8_t index);

    /*
    * If there is a HID device connected, the host stores the length of the report descriptor.
    * This avoid to the driver to re-ask the configuration descriptor to request the report descriptor
    *
    * @returns length of the report descriptor
    */
    inline uint16_t getLengthReportDescr() {
        return lenReportDescr;
    };

    /**
     *  register a driver into the host associated with a callback function called when the device is disconnected
     *
     *  @param dev device
     *  @param intf interface number
     *  @param tptr pointer to the object to call the member function on
     *  @param mptr pointer to the member function to be called
     */
    template<typename T>
    inline void registerDriver(USBDeviceConnected * dev, uint8_t intf, T* tptr, void (T::*mptr)(void)) {
        int index = findDevice(dev);
        if ((index != -1) && (mptr != NULL) && (tptr != NULL)) {
            USB_DBG("register driver for dev: %p on intf: %d", dev, intf);
            deviceAttachedDriver[index][intf] = true;
            dev->onDisconnect(intf, tptr, mptr);
        }
    }

    /**
     * register a driver into the host associated with a callback function called when the device is disconnected
     *
     * @param dev device
     * @param intf interface number
     * @param fn callback called when the specified device has been disconnected
     */
    inline void registerDriver(USBDeviceConnected * dev, uint8_t intf, void (*fn)(void)) {
        int index = findDevice(dev);
        if ((index != -1) && (fn != NULL)) {
            USB_DBG("register driver for dev: %p on intf: %d", dev, intf);
            deviceAttachedDriver[index][intf] = true;
            dev->onDisconnect(intf, fn);
        }
    }

    /**
     * Instantiate to protect USB thread from accessing shared objects (USBConnectedDevices and Interfaces)
     */
    class Lock
    {
    public:
      Lock(USBHost* pHost);
      ~Lock();
    private:
      USBHost* m_pHost;
    };

    friend class USBHostHub;

protected:

    /**
    * Virtual method called when a transfer has been completed
    *
    * @param addr list of the TDs which have been completed
    */
    virtual void transferCompleted(volatile uint32_t addr);

    /**
    * Virtual method called when a device has been connected
    *
    * @param hub hub number of the device
    * @param port port number of the device
    * @param lowSpeed 1 if low speed, 0 otherwise
    * @param hub_parent reference on the parent hub
    */
    virtual void deviceConnected(int hub, int port, bool lowSpeed, USBHostHub * hub_parent = NULL);

    /**
    * Virtuel method called when a device has been disconnected
    *
    * @param hub hub number of the device
    * @param port port number of the device
    * @param addr list of the TDs which have been completed to dequeue freed TDs
    */
    virtual void deviceDisconnected(int hub, int port, USBHostHub * hub_parent, volatile uint32_t addr);


private:
    // singleton class -> constructor is private
    USBHost();
    static USBHost * instHost;
    uint16_t  lenReportDescr;

    // endpoints
    void unqueueEndpoint(USBEndpoint * ep) ;
    USBEndpoint  endpoints[MAX_ENDPOINT];
    USBEndpoint* volatile  control;

    USBEndpoint* volatile  headControlEndpoint;
    USBEndpoint* volatile  headBulkEndpoint;
    USBEndpoint* volatile  headInterruptEndpoint;

    USBEndpoint* volatile  tailControlEndpoint;
    USBEndpoint* volatile  tailBulkEndpoint;
    USBEndpoint* volatile  tailInterruptEndpoint;

    bool controlEndpointAllocated;

    // devices connected
    USBDeviceConnected devices[MAX_DEVICE_CONNECTED];
    bool  deviceInUse[MAX_DEVICE_CONNECTED];
    bool  deviceAttachedDriver[MAX_DEVICE_CONNECTED][MAX_INTF];
    bool  deviceReset[MAX_DEVICE_CONNECTED];
    bool  deviceInited[MAX_DEVICE_CONNECTED];

#if MAX_HUB_NB
    USBHostHub hubs[MAX_HUB_NB];
    bool hub_in_use[MAX_HUB_NB];
#endif

    // to store a setup packet
    uint8_t  setupPacket[8];

    typedef struct {
        uint8_t event_id;
        void * td_addr;
        uint8_t hub;
        uint8_t port;
        uint8_t lowSpeed;
        uint8_t td_state;
        void * hub_parent;
    } message_t;

    Thread usbThread;
    void usb_process();
    static void usb_process_static(void const * arg);
    Mail<message_t, 10> mail_usb_event;
    Mutex usb_mutex;
    Mutex td_mutex;

    // buffer for conf descriptor
    uint8_t data[415];

    /**
    * Add a transfer on the TD linked list associated to an ED
    *
    * @param ed the transfer is associated to this ed
    * @param buf pointer on a buffer where will be read/write data to send or receive
    * @param len transfer length
    *
    * @return status of the transfer
    */
    USB_TYPE addTransfer(USBEndpoint * ed, uint8_t * buf, uint32_t len) ;

    /**
    * Link the USBEndpoint to the linked list and attach an USBEndpoint this USBEndpoint to a device
    *
    * @param dev pointer on a USBDeviceConnected object
    * @param ep pointer on the USBEndpoint which will be added
    *
    * return true if successful
    */
    bool addEndpoint(USBDeviceConnected * dev, uint8_t intf_nb, USBEndpoint * ep) ;

    /**
    * Create an USBEndpoint descriptor. Warning: the USBEndpoint is not linked.
    *
    * @param type USBEndpoint type (CONTROL_ENDPOINT, BULK_ENDPOINT, INTERRUPT_ENDPOINT)
    * @param dir USBEndpoint direction (no meaning for CONTROL_ENDPOINT)
    * @param size USBEndpoint max packet size
    * @param addr USBEndpoint address
    *
    * @returns pointer on the USBEndpoint created
    */
    USBEndpoint * newEndpoint(ENDPOINT_TYPE type, ENDPOINT_DIRECTION dir, uint32_t size, uint8_t addr) ;

    /**
    * Request the device descriptor
    *
    * @param dev request the device descriptor on this device
    * @param buf buffer to store the device descriptor
    * @param max_len_buf maximum size of buf
    * @param len_dev_descr pointer to store the length of the packet transferred
    */
    USB_TYPE getDeviceDescriptor(USBDeviceConnected * dev, uint8_t * buf, uint16_t max_len_buf, uint16_t * len_dev_descr = NULL);

    /**
    * Request the configuration descriptor
    *
    * @param dev request the configuration descriptor on this device
    * @param buf buffer to store the configuration descriptor
    * @param max_len_buf maximum size of buf
    * @param len_conf_descr pointer to store the length of the packet transferred
    */
    USB_TYPE getConfigurationDescriptor(USBDeviceConnected * dev, uint8_t * buf, uint16_t max_len_buf, uint16_t * len_conf_descr = NULL);

    /**
    * Set the address of a specific device
    *
    * @param dev device to set the address
    * @param address address
    */
    USB_TYPE setAddress(USBDeviceConnected * dev, uint8_t address);

    /**
    * Set the configuration of a device
    *
    * @param dev device on which the specified configuration will be activated
    * @param conf configuration number to activate (usually 1)
    */
    USB_TYPE setConfiguration(USBDeviceConnected * dev, uint8_t conf);

    /**
    * Free a specific device
    *
    * @param dev device to be freed
    */
    void freeDevice(USBDeviceConnected * dev);

    USB_TYPE controlTransfer(   USBDeviceConnected * dev,
                                uint8_t requestType,
                                uint8_t request,
                                uint32_t value,
                                uint32_t index,
                                uint8_t * buf,
                                uint32_t len,
                                bool write);

    USB_TYPE generalTransfer(   USBDeviceConnected * dev,
                                USBEndpoint * ep,
                                uint8_t * buf,
                                uint32_t len,
                                bool blocking,
                                ENDPOINT_TYPE type,
                                bool write) ;

    void fillControlBuf(uint8_t requestType, uint8_t request, uint16_t value, uint16_t index, int len) ;
    void parseConfDescr(USBDeviceConnected * dev, uint8_t * conf_descr, uint32_t len, IUSBEnumerator* pEnumerator) ;
    int findDevice(USBDeviceConnected * dev) ;
    int findDevice(uint8_t hub, uint8_t port, USBHostHub * hub_parent = NULL) ;
    uint8_t numberDriverAttached(USBDeviceConnected * dev);

    /////////////////////////
    /// FOR DEBUG
    /////////////////////////
    void printList(ENDPOINT_TYPE type);

};

#endif
