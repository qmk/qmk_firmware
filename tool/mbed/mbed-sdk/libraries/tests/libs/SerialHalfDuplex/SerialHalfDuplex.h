/* mbed Microcontroller Library - SerialHalfDuplex
 * Copyright (c) 2010-2011 ARM Limited. All rights reserved.
 */
#ifndef MBED_SERIALHALFDUPLEX_H
#define MBED_SERIALHALFDUPLEX_H

#include "platform.h"

#if DEVICE_SERIAL

#include "Serial.h"
#include "gpio_api.h"

namespace mbed {

/** A serial port (UART) for communication with other devices using
 * Half-Duplex, allowing transmit and receive on a single
 * shared transmit and receive line. Only one end should be transmitting
 * at a time.
 *
 * Both the tx and rx pin should be defined, and wired together.
 * This is in addition to them being wired to the other serial
 * device to allow both read and write functions to operate.
 *
 *  For Simplex and Full-Duplex Serial communication, see Serial()
 *
 *  Example:
 * @code
 * // Send a byte to a second HalfDuplex device, and read the response
 *
 * #include "mbed.h"
 *
 * // p9 and p10 should be wired together to form "a"
 * // p28 and p27 should be wired together to form "b"
 * // p9/p10 should be wired to p28/p27 as the Half Duplex connection
 *
 * SerialHalfDuplex a(p9, p10);
 * SerialHalfDuplex b(p28, p27);
 *
 * void b_rx() { // second device response
 *     b.putc(b.getc() + 4);
 * }
 *
 * int main() {
 *     b.attach(&b_rx);
 *     for (int c = 'A'; c < 'Z'; c++) {
 *         a.putc(c);
 *         printf("sent [%c]\n", c);
 *         wait(0.5);   // b should respond
 *         if (a.readable()) {
 *             printf("received [%c]\n", a.getc());
 *         }
 *     }
 * }
 * @endcode
 */
class SerialHalfDuplex : public Serial {

public:
    /** Create a half-duplex serial port, connected to the specified transmit
     * and receive pins.
     *
     * These pins should be wired together, as well as to the target device
     *
     *  @param tx Transmit pin
     *  @param rx Receive pin
     */
    SerialHalfDuplex(PinName tx, PinName rx);

protected:
    gpio_object gpio;

    virtual int _putc(int c);
    virtual int _getc(void);

}; // End class SerialHalfDuplex

} // End namespace

#endif

#endif
