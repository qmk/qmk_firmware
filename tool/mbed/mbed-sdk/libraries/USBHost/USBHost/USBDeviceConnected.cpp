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

#include "USBDeviceConnected.h"
#include "dbg.h"

USBDeviceConnected::USBDeviceConnected() {
    init();
}

void USBDeviceConnected::init() {
    hub_nb = 0;
    port = 0;
    vid = 0;
    pid = 0;
    nb_interf = 0;
    enumerated = false;
    activeAddr = false;
    sizeControlEndpoint = 8;
    device_class = 0;
    device_subclass = 0;
    proto = 0;
    speed = false;
    for (int i = 0; i < MAX_INTF; i++) {
        memset((void *)&intf[i], 0, sizeof(INTERFACE));
        intf[i].in_use = false;
        for (int j = 0; j < MAX_ENDPOINT_PER_INTERFACE; j++) {
            intf[i].ep[j] = NULL;
            strcpy(intf[i].name, "Unknown");
        }
    }
    hub_parent = NULL;
    hub = NULL;
    nb_interf = 0;
}

INTERFACE * USBDeviceConnected::getInterface(uint8_t index) {
    if (index >= MAX_INTF)
        return NULL;

    if (intf[index].in_use)
        return &intf[index];

    return NULL;
}

bool USBDeviceConnected::addInterface(uint8_t intf_nb, uint8_t intf_class, uint8_t intf_subclass, uint8_t intf_protocol) {
    if ((intf_nb >= MAX_INTF) || (intf[intf_nb].in_use)) {
        return false;
    }
    intf[intf_nb].in_use = true;
    intf[intf_nb].intf_class = intf_class;
    intf[intf_nb].intf_subclass = intf_subclass;
    intf[intf_nb].intf_protocol = intf_protocol;
    intf[intf_nb].nb_endpoint = 0;
    return true;
}

bool USBDeviceConnected::addEndpoint(uint8_t intf_nb, USBEndpoint * ept) {
    if ((intf_nb >= MAX_INTF) || (intf[intf_nb].in_use == false) || (intf[intf_nb].nb_endpoint >= MAX_ENDPOINT_PER_INTERFACE)) {
        return false;
    }
    intf[intf_nb].nb_endpoint++;

    for (int i = 0; i < MAX_ENDPOINT_PER_INTERFACE; i++) {
        if (intf[intf_nb].ep[i] == NULL) {
            intf[intf_nb].ep[i] = ept;
            return true;
        }
    }
    return false;
}

void USBDeviceConnected::init(uint8_t hub_, uint8_t port_, bool lowSpeed_) {
    USB_DBG("init dev: %p", this);
    init();
    hub_nb = hub_;
    port = port_;
    speed = lowSpeed_;
}

void USBDeviceConnected::disconnect() {
    for(int i = 0; i < MAX_INTF; i++) {
        intf[i].detach.call();
    }
    init();
}


USBEndpoint * USBDeviceConnected::getEndpoint(uint8_t intf_nb, ENDPOINT_TYPE type, ENDPOINT_DIRECTION dir, uint8_t index) {
    if (intf_nb >= MAX_INTF) {
        return NULL;
    }
    for (int i = 0; i < MAX_ENDPOINT_PER_INTERFACE; i++) {
        if ((intf[intf_nb].ep[i]->getType() == type) && (intf[intf_nb].ep[i]->getDir() == dir)) {
            if(index) {
                index--;
            } else {
                return intf[intf_nb].ep[i];
            }
        }
    }
    return NULL;
}

USBEndpoint * USBDeviceConnected::getEndpoint(uint8_t intf_nb, uint8_t index) {
    if ((intf_nb >= MAX_INTF) || (index >= MAX_ENDPOINT_PER_INTERFACE)) {
        return NULL;
    }
    return intf[intf_nb].ep[index];
}
