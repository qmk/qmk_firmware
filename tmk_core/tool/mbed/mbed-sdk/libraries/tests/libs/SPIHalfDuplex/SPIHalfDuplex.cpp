/* mbed Microcontroller Library - SPIHalfDuplex
 * Copyright (c) 2010-2011 ARM Limited. All rights reserved.
 */
#include "SPIHalfDuplex.h"

#if DEVICE_SPI

#include "spi_api.h"
#include "pinmap.h"

#define GPIO_MODE 0
#define SPI_MODE  2

namespace mbed {

SPIHalfDuplex::SPIHalfDuplex(PinName mosi, PinName miso, PinName sclk) : SPI(mosi, miso, sclk) {
    _mosi = mosi;
    _miso = miso;
    _sbits = _bits;
}

void SPIHalfDuplex::slave_format(int sbits) {
    _sbits = sbits;
}

int SPIHalfDuplex::write(int value) {
    int t_bits = _bits;
    pin_function(_mosi, SPI_MODE);
    int ret_val = SPI::write(value);
    if (ret_val != value) {
        return -1;
    }
    format(_sbits, _mode);
    pin_function(_mosi, GPIO_MODE);
    ret_val = SPI::write(0x55);
    format(t_bits, _mode);
    pin_function(_mosi, SPI_MODE);
    return ret_val;
}

} // end namespace mbed

#endif
