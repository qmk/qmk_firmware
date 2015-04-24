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
#include "SPI.h"

#if DEVICE_SPI

namespace mbed {

SPI::SPI(PinName mosi, PinName miso, PinName sclk, PinName _unused) :
        _spi(),
        _bits(8),
        _mode(0),
        _hz(1000000) {
    spi_init(&_spi, mosi, miso, sclk, NC);
    spi_format(&_spi, _bits, _mode, 0);
    spi_frequency(&_spi, _hz);
}

void SPI::format(int bits, int mode) {
    _bits = bits;
    _mode = mode;
    SPI::_owner = NULL; // Not that elegant, but works. rmeyer
    aquire();
}

void SPI::frequency(int hz) {
    _hz = hz;
    SPI::_owner = NULL; // Not that elegant, but works. rmeyer
    aquire();
}

SPI* SPI::_owner = NULL;

// ignore the fact there are multiple physical spis, and always update if it wasnt us last
void SPI::aquire() {
     if (_owner != this) {
        spi_format(&_spi, _bits, _mode, 0);
        spi_frequency(&_spi, _hz);
        _owner = this;
    }
}

int SPI::write(int value) {
    aquire();
    return spi_master_write(&_spi, value);
}

} // namespace mbed

#endif
