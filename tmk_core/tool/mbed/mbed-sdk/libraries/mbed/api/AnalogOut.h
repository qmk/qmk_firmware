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
#ifndef MBED_ANALOGOUT_H
#define MBED_ANALOGOUT_H

#include "platform.h"

#if DEVICE_ANALOGOUT

#include "analogout_api.h"

namespace mbed {

/** An analog output, used for setting the voltage on a pin
 *
 * Example:
 * @code
 * // Make a sawtooth output
 *
 * #include "mbed.h"
 *
 * AnalogOut tri(p18);
 * int main() {
 *     while(1) {
 *         tri = tri + 0.01;
 *         wait_us(1);
 *         if(tri == 1) {
 *             tri = 0;
 *         }
 *     }
 * }
 * @endcode
 */
class AnalogOut {

public:

    /** Create an AnalogOut connected to the specified pin
     *
     *  @param AnalogOut pin to connect to (18)
     */
    AnalogOut(PinName pin) {
        analogout_init(&_dac, pin);
    }

    /** Set the output voltage, specified as a percentage (float)
     *
     *  @param value A floating-point value representing the output voltage,
     *    specified as a percentage. The value should lie between
     *    0.0f (representing 0v / 0%) and 1.0f (representing 3.3v / 100%).
     *    Values outside this range will be saturated to 0.0f or 1.0f.
     */
    void write(float value) {
        analogout_write(&_dac, value);
    }

    /** Set the output voltage, represented as an unsigned short in the range [0x0, 0xFFFF]
     *
     *  @param value 16-bit unsigned short representing the output voltage,
     *            normalised to a 16-bit value (0x0000 = 0v, 0xFFFF = 3.3v)
     */
    void write_u16(unsigned short value) {
        analogout_write_u16(&_dac, value);
    }

    /** Return the current output voltage setting, measured as a percentage (float)
     *
     *  @returns
     *    A floating-point value representing the current voltage being output on the pin,
     *    measured as a percentage. The returned value will lie between
     *    0.0f (representing 0v / 0%) and 1.0f (representing 3.3v / 100%).
     *
     *  @note
     *    This value may not match exactly the value set by a previous write().
     */
    float read() {
        return analogout_read(&_dac);
    }

#ifdef MBED_OPERATORS
    /** An operator shorthand for write()
     */
    AnalogOut& operator= (float percent) {
        write(percent);
        return *this;
    }

    AnalogOut& operator= (AnalogOut& rhs) {
        write(rhs.read());
        return *this;
    }

    /** An operator shorthand for read()
     */
    operator float() {
        return read();
    }
#endif

protected:
    dac_t _dac;
};

} // namespace mbed

#endif

#endif
