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
#ifndef MBED_RAW_SERIAL_H
#define MBED_RAW_SERIAL_H

#include "platform.h"

#if DEVICE_SERIAL

#include "SerialBase.h"
#include "serial_api.h"

namespace mbed {

/** A serial port (UART) for communication with other serial devices
 * This is a variation of the Serial class that doesn't use streams,
 * thus making it safe to use in interrupt handlers with the RTOS.
 *
 * Can be used for Full Duplex communication, or Simplex by specifying
 * one pin as NC (Not Connected)
 *
 * Example:
 * @code
 * // Send a char to the PC
 *
 * #include "mbed.h"
 *
 * RawSerial pc(USBTX, USBRX);
 *
 * int main() {
 *     pc.putc('A');
 * }
 * @endcode
 */
class RawSerial: public SerialBase {

public:
    /** Create a RawSerial port, connected to the specified transmit and receive pins
     *
     *  @param tx Transmit pin
     *  @param rx Receive pin
     *
     *  @note
     *    Either tx or rx may be specified as NC if unused
     */
    RawSerial(PinName tx, PinName rx);

    /** Write a char to the serial port
     *
     * @param c The char to write
     *
     * @returns The written char or -1 if an error occured
     */
    int putc(int c);

    /** Read a char from the serial port
     *
     * @returns The char read from the serial port
     */
    int getc();

    /** Write a string to the serial port
     *
     * @param str The string to write
     *
     * @returns 0 if the write succeeds, EOF for error
     */
    int puts(const char *str);

    int printf(const char *format, ...);
};

} // namespace mbed

#endif

#endif
