/* mbed Microcontroller Library
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
#include "Ethernet.h"

#if DEVICE_ETHERNET

#include "ethernet_api.h"

namespace mbed {

Ethernet::Ethernet() {
    ethernet_init();
}

Ethernet::~Ethernet() {
    ethernet_free();
}

int Ethernet::write(const char *data, int size) {
    return ethernet_write(data, size);
}

int Ethernet::send() {
    return ethernet_send();
}

int Ethernet::receive() {
    return ethernet_receive();
}

int Ethernet::read(char *data, int size) {
    return ethernet_read(data, size);
}

void Ethernet::address(char *mac) {
    return ethernet_address(mac);
}

int Ethernet::link() {
    return ethernet_link();
}

void Ethernet::set_link(Mode mode) {
    int speed = -1;
    int duplex = 0;

    switch(mode) {
        case AutoNegotiate : speed = -1; duplex = 0; break;
        case HalfDuplex10  : speed = 0;  duplex = 0; break;
        case FullDuplex10  : speed = 0;  duplex = 1; break;
        case HalfDuplex100 : speed = 1;  duplex = 0; break;
        case FullDuplex100 : speed = 1;  duplex = 1; break;
    }

    ethernet_set_link(speed, duplex);
}

} // namespace mbed

#endif
