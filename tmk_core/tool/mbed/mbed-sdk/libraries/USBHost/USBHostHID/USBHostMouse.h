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

#ifndef USBHOSTMOUSE_H
#define USBHOSTMOUSE_H

#include "USBHostConf.h"

#if USBHOST_MOUSE

#include "USBHost.h"

/**
 * A class to communicate a USB mouse
 */
class USBHostMouse : public IUSBEnumerator {
public:

    /**
    * Constructor
    */
    USBHostMouse();

    /**
     * Try to connect a mouse device
     *
     * @return true if connection was successful
     */
    bool connect();

    /**
    * Check if a mouse is connected
    *
    * @returns true if a mouse is connected
    */
    bool connected();

    /**
     * Attach a callback called when a mouse event is received
     *
     * @param ptr function pointer
     */
    inline void attachEvent(void (*ptr)(uint8_t buttons, int8_t x, int8_t y, int8_t z)) {
        if (ptr != NULL) {
            onUpdate = ptr;
        }
    }

    /**
     * Attach a callback called when the button state changes
     *
     * @param ptr function pointer
     */
    inline void attachButtonEvent(void (*ptr)(uint8_t buttons)) {
        if (ptr != NULL) {
            onButtonUpdate = ptr;
        }
    }

    /**
     * Attach a callback called when the X axis value changes
     *
     * @param ptr function pointer
     */
    inline void attachXEvent(void (*ptr)(int8_t x)) {
        if (ptr != NULL) {
            onXUpdate = ptr;
        }
    }

    /**
     * Attach a callback called when the Y axis value changes
     *
     * @param ptr function pointer
     */
    inline void attachYEvent(void (*ptr)(int8_t y)) {
        if (ptr != NULL) {
            onYUpdate = ptr;
        }
    }

    /**
     * Attach a callback called when the Z axis value changes (scrolling)
     *
     * @param ptr function pointer
     */
    inline void attachZEvent(void (*ptr)(int8_t z)) {
        if (ptr != NULL) {
            onZUpdate = ptr;
        }
    }

protected:
    //From IUSBEnumerator
    virtual void setVidPid(uint16_t vid, uint16_t pid);
    virtual bool parseInterface(uint8_t intf_nb, uint8_t intf_class, uint8_t intf_subclass, uint8_t intf_protocol); //Must return true if the interface should be parsed
    virtual bool useEndpoint(uint8_t intf_nb, ENDPOINT_TYPE type, ENDPOINT_DIRECTION dir); //Must return true if the endpoint will be used

private:
    USBHost * host;
    USBDeviceConnected * dev;
    USBEndpoint * int_in;
    uint8_t report[4];

    bool dev_connected;
    bool mouse_device_found;
    int mouse_intf;

    uint8_t buttons;
    int8_t x;
    int8_t y;
    int8_t z;

    void rxHandler();
    void (*onUpdate)(uint8_t buttons, int8_t x, int8_t y, int8_t z);
    void (*onButtonUpdate)(uint8_t buttons);
    void (*onXUpdate)(int8_t x);
    void (*onYUpdate)(int8_t y);
    void (*onZUpdate)(int8_t z);
    int report_id;
    void init();
};

#endif

#endif
