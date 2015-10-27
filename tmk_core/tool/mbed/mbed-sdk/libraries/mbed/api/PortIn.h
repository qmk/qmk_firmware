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
#ifndef MBED_PORTIN_H
#define MBED_PORTIN_H

#include "platform.h"

#if DEVICE_PORTIN

#include "port_api.h"

namespace mbed {

/** A multiple pin digital input
 *
 *  Example:
 * @code
 * // Switch on an LED if any of mbed pins 21-26 is high
 *
 * #include "mbed.h"
 *
 * PortIn     p(Port2, 0x0000003F);   // p21-p26
 * DigitalOut ind(LED4);
 *
 * int main() {
 *     while(1) {
 *         int pins = p.read();
 *         if(pins) {
 *             ind = 1;
 *         } else {
 *             ind = 0;
 *         }
 *     }
 * }
 * @endcode
 */
class PortIn {
public:

    /** Create an PortIn, connected to the specified port
     *
     *  @param port Port to connect to (Port0-Port5)
     *  @param mask A bitmask to identify which bits in the port should be included (0 - ignore)
        */
    PortIn(PortName port, int mask = 0xFFFFFFFF) {
        port_init(&_port, port, mask, PIN_INPUT);
    }

    /** Read the value currently output on the port
     *
     *  @returns
     *    An integer with each bit corresponding to associated port pin setting
     */
    int read() {
        return port_read(&_port);
    }

    /** Set the input pin mode
     *
     *  @param mode PullUp, PullDown, PullNone, OpenDrain
     */
    void mode(PinMode mode) {
        port_mode(&_port, mode);
    }

    /** A shorthand for read()
     */
    operator int() {
        return read();
    }

private:
    port_t _port;
};

} // namespace mbed

#endif

#endif
