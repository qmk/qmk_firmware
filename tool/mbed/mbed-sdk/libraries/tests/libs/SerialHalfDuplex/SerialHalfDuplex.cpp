/* mbed Microcontroller Library - SerialHalfDuplex
 * Copyright (c) 2010-2011 ARM Limited. All rights reserved.
 */
#include "SerialHalfDuplex.h"

#if DEVICE_SERIAL

#include "pinmap.h"
#include "serial_api.h"

namespace mbed {

SerialHalfDuplex::SerialHalfDuplex(PinName tx, PinName rx)
    : Serial(tx, rx) {

    gpio_init(&gpio, tx, PIN_INPUT);
    gpio_mode(&gpio, PullNone); // no pull
}

// To transmit a byte in half duplex mode:
// 1. Disable interrupts, so we don't trigger on loopback byte
// 2. Set tx pin to UART out
// 3. Transmit byte as normal
// 4. Read back byte from looped back tx pin - this both confirms that the
//    transmit has occurred, and also clears the byte from the buffer.
// 5. Return pin to input mode
// 6. Re-enable interrupts
int SerialHalfDuplex::_putc(int c) {
    int retc;

    // TODO: We should not disable all interrupts
    __disable_irq();

    serial_pinout_tx(gpio.pin);

    Serial::_putc(c);
    retc = Serial::getc();       // reading also clears any interrupt

    pin_function(gpio.pin, 0);

    __enable_irq();

    return retc;
}

int SerialHalfDuplex::_getc(void) {
    return Serial::_getc();
}

} // End namespace

#endif
