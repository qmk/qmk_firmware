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

#include "USBHostHub.h"

#if MAX_HUB_NB

#include "USBHost.h"
#include "dbg.h"

#define GET_STATUS 0x00
#define CLEAR_FEATURE 0x01
#define GET_STATE 0x02
#define SET_FEATURE 0x03
#define GET_DESCRIPTOR 0x06

#define PORT_CONNECTION_FEATURE     (0x00)
#define PORT_ENABLE_FEATURE         (0x01)
#define PORT_RESET_FEATURE          (0x04)
#define PORT_POWER_FEATURE          (0x08)

#define C_PORT_CONNECTION_FEATURE     (16)
#define C_PORT_ENABLE_FEATURE         (17)
#define C_PORT_RESET_FEATURE          (20)

#define PORT_CONNECTION   (1 << 0)
#define PORT_ENABLE       (1 << 1)
#define PORT_SUSPEND      (1 << 2)
#define PORT_OVER_CURRENT (1 << 3)
#define PORT_RESET        (1 << 4)
#define PORT_POWER        (1 << 8)
#define PORT_LOW_SPEED    (1 << 9)

#define C_PORT_CONNECTION   (1 << 16)
#define C_PORT_ENABLE       (1 << 17)
#define C_PORT_SUSPEND      (1 << 18)
#define C_PORT_OVER_CURRENT (1 << 19)
#define C_PORT_RESET        (1 << 20)

USBHostHub::USBHostHub() {
    host = NULL;
    init();
}

void USBHostHub::init() {
    dev_connected = false;
    dev = NULL;
    int_in = NULL;
    dev_connected = false;
    hub_intf = -1;
    hub_device_found = false;
    nb_port = 0;
    hub_characteristics = 0;

    for (int i = 0; i < MAX_HUB_PORT; i++) {
        device_children[i] = NULL;
    }
}

void USBHostHub::setHost(USBHost * host_) {
    host = host_;
}

bool USBHostHub::connected()
{
    return dev_connected;
}

bool USBHostHub::connect(USBDeviceConnected * dev)
{
    if (dev_connected) {
        return true;
    }

    if(host->enumerate(dev, this)) {
        init();
        return false;
    }

    if (hub_device_found) {
        this->dev = dev;

        int_in = dev->getEndpoint(hub_intf, INTERRUPT_ENDPOINT, IN);

        if (!int_in) {
            init();
            return false;
        }

        USB_INFO("New HUB: VID:%04x PID:%04x [dev: %p - intf: %d]", dev->getVid(), dev->getPid(), dev, hub_intf);
        dev->setName("Hub", hub_intf);
        host->registerDriver(dev, hub_intf, this, &USBHostHub::disconnect);

        int_in->attach(this, &USBHostHub::rxHandler);

        // get HUB descriptor
        host->controlRead(  dev,
                            USB_DEVICE_TO_HOST | USB_REQUEST_TYPE_CLASS,
                            GET_DESCRIPTOR,
                            0x29 << 8, 0, buf, sizeof(HubDescriptor));
        nb_port = buf[2];
        hub_characteristics = buf[3];

        USB_DBG("Hub has %d port", nb_port);

        for (uint8_t j = 1; j <= nb_port; j++) {
            setPortFeature(PORT_POWER_FEATURE, j);
        }
        wait_ms(buf[5]*2);

        host->interruptRead(dev, int_in, buf, 1, false);
        dev_connected = true;
        return true;
    }

    return false;
}

void USBHostHub::disconnect() {
    init();
}

/*virtual*/ void USBHostHub::setVidPid(uint16_t vid, uint16_t pid)
{
    // we don't check VID/PID for MSD driver
}

/*virtual*/ bool USBHostHub::parseInterface(uint8_t intf_nb, uint8_t intf_class, uint8_t intf_subclass, uint8_t intf_protocol) //Must return true if the interface should be parsed
{
    if ((hub_intf == -1) &&
        (intf_class == HUB_CLASS) &&
        (intf_subclass == 0) &&
        (intf_protocol == 0)) {
        hub_intf = intf_nb;
        return true;
    }
    return false;
}

/*virtual*/ bool USBHostHub::useEndpoint(uint8_t intf_nb, ENDPOINT_TYPE type, ENDPOINT_DIRECTION dir) //Must return true if the endpoint will be used
{
    if (intf_nb == hub_intf) {
        if ((type == INTERRUPT_ENDPOINT) && (dir == IN)) {
            hub_device_found = true;
            return true;
        }
    }
    return false;
}

void USBHostHub::deviceConnected(USBDeviceConnected * dev) {
    device_children[dev->getPort() - 1] = dev;
}

void USBHostHub::deviceDisconnected(USBDeviceConnected * dev) {
    device_children[dev->getPort() - 1] = NULL;
}

void USBHostHub::hubDisconnected() {
    for (uint8_t i = 0; i < MAX_HUB_PORT; i++) {
        if (device_children[i] != NULL) {
            host->freeDevice(device_children[i]);
        }
    }
}

void USBHostHub::rxHandler() {
    uint32_t status;
    if (int_in) {
        if (int_in->getState() == USB_TYPE_IDLE) {
            for (int port = 1; port <= nb_port; port++) {
                status = getPortStatus(port);
                USB_DBG("[hub handler hub: %d] status port %d [hub: %p]: 0x%X", dev->getHub(), port, dev, status);

                // if connection status has changed
                if (status & C_PORT_CONNECTION) {
                    if (status & PORT_CONNECTION) {
                        USB_DBG("[hub handler hub: %d - port: %d] new device connected", dev->getHub(), port);
                        host->deviceConnected(dev->getHub() + 1, port, status & PORT_LOW_SPEED, this);
                    } else {
                        USB_DBG("[hub handler hub: %d - port: %d] device disconnected", dev->getHub(), port);
                        host->deviceDisconnected(dev->getHub() + 1, port, this, 0);
                    }

                    clearPortFeature(C_PORT_CONNECTION_FEATURE, port);
                }

                if (status & C_PORT_RESET) {
                    clearPortFeature(C_PORT_RESET_FEATURE, port);
                }

                if (status & C_PORT_ENABLE) {
                    clearPortFeature(C_PORT_ENABLE_FEATURE, port);
                }

                if ((status & PORT_OVER_CURRENT)) {
                    USB_ERR("OVER CURRENT DETECTED\r\n");
                    clearPortFeature(PORT_OVER_CURRENT, port);
                    host->deviceDisconnected(dev->getHub() + 1, port, this, 0);
                }
            }
        }
        host->interruptRead(dev, int_in, buf, 1, false);
    }
}

void USBHostHub::portReset(uint8_t port) {
    // reset port
    uint32_t status;
    USB_DBG("reset port %d on hub: %p [this: %p]", port, dev, this)
    setPortFeature(PORT_RESET_FEATURE, port);
#if defined(TARGET_RZ_A1H)
    Thread::wait(50);   // Reset release waiting for Hi-Speed check.
#endif
    while(1) {
        status = getPortStatus(port);
        if (status & (PORT_ENABLE | PORT_RESET))
            break;
        if (status & PORT_OVER_CURRENT) {
            USB_ERR("OVER CURRENT DETECTED\r\n");
            clearPortFeature(PORT_OVER_CURRENT, port);
            host->deviceDisconnected(dev->getHub() + 1, port, this, 0);
            break;
        }
        Thread::wait(10);
    }
}

void USBHostHub::setPortFeature(uint32_t feature, uint8_t port) {
    host->controlWrite( dev,
                        USB_HOST_TO_DEVICE | USB_REQUEST_TYPE_CLASS | USB_RECIPIENT_INTERFACE | USB_RECIPIENT_ENDPOINT,
                        SET_FEATURE,
                        feature,
                        port,
                        NULL,
                        0);
}

void USBHostHub::clearPortFeature(uint32_t feature, uint8_t port) {
    host->controlWrite( dev,
                        USB_HOST_TO_DEVICE | USB_REQUEST_TYPE_CLASS | USB_RECIPIENT_INTERFACE | USB_RECIPIENT_ENDPOINT,
                        CLEAR_FEATURE,
                        feature,
                        port,
                        NULL,
                        0);
}

uint32_t USBHostHub::getPortStatus(uint8_t port) {
    uint32_t st;
    host->controlRead(  dev,
                        USB_DEVICE_TO_HOST | USB_REQUEST_TYPE_CLASS | USB_RECIPIENT_INTERFACE | USB_RECIPIENT_ENDPOINT,
                        GET_STATUS,
                        0,
                        port,
                        (uint8_t *)&st,
                        4);
    return st;
}

#endif
