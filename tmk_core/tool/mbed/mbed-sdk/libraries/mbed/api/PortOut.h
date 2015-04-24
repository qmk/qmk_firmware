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
#ifndef MBED_PORTOUT_H
#define MBED_PORTOUT_H

#include "platform.h"

#if DEVICE_PORTOUT

#include "port_api.h"

namespace mbed {
/** A multiple pin digital out
 *
 * Example:
 * @code
 * // Toggle all four LEDs
 *
 * #include "mbed.h"
 *
 * // LED1 = P1.18  LED2 = P1.20  LED3 = P1.21  LED4 = P1.23
 * #define LED_MASK 0x00B40000
 *
 * PortOut ledport(Port1, LED_MASK);
 *
 * int main() {
 *     while(1) {
 *         ledport = LED_MASK;
 *         wait(1);
 *         ledport = 0;
 *         wait(1);
 *     }
 * }
 * @endcode
 */
class PortOut {
public:

    /** Create an PortOut, connected to the specified port
     *
     *  @param port Port to connect to (Port0-Port5)
     *  @param mask A bitmask to identify which bits in the port should be included (0 - ignore)
     */
    PortOut(PortName port, int mask = 0xFFFFFFFF) {
        port_init(&_port, port, mask, PIN_OUTPUT);
    }

    /** Write the value to the output port
     *
     *  @param value An integer specifying a bit to write for every corresponding PortOut pin
     */
    void write(int value) {
        port_write(&_port, value);
    }

    /** Read the value currently output on the port
     *
     *  @returns
     *    An integer with each bit corresponding to associated PortOut pin setting
     */
    int read() {
        return port_read(&_port);
    }

    /** A shorthand for write()
     */
    PortOut& operator= (int value) {
        write(value);
        return *this;
    }

    PortOut& operator= (PortOut& rhs) {
        write(rhs.read());
        return *this;
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
