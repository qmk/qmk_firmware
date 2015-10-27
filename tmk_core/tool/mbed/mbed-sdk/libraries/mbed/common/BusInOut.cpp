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
#include "BusInOut.h"
#include "mbed_assert.h"

namespace mbed {

BusInOut::BusInOut(PinName p0, PinName p1, PinName p2, PinName p3, PinName p4, PinName p5, PinName p6, PinName p7, PinName p8, PinName p9, PinName p10, PinName p11, PinName p12, PinName p13, PinName p14, PinName p15) {
    PinName pins[16] = {p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15};

    _nc_mask = 0;
    for (int i=0; i<16; i++) {
        _pin[i] = (pins[i] != NC) ? new DigitalInOut(pins[i]) : 0;
        if (pins[i] != NC) {
            _nc_mask |= (1 << i);
        }
    }
}

BusInOut::BusInOut(PinName pins[16]) {
    _nc_mask = 0;
    for (int i=0; i<16; i++) {
        _pin[i] = (pins[i] != NC) ? new DigitalInOut(pins[i]) : 0;
        if (pins[i] != NC) {
            _nc_mask |= (1 << i);
        }
    }
}

BusInOut::~BusInOut() {
    for (int i=0; i<16; i++) {
        if (_pin[i] != 0) {
            delete _pin[i];
        }
    }
}

void BusInOut::write(int value) {
    for (int i=0; i<16; i++) {
        if (_pin[i] != 0) {
            _pin[i]->write((value >> i) & 1);
        }
    }
}

int BusInOut::read() {
    int v = 0;
    for (int i=0; i<16; i++) {
        if (_pin[i] != 0) {
            v |= _pin[i]->read() << i;
        }
    }
    return v;
}

void BusInOut::output() {
    for (int i=0; i<16; i++) {
        if (_pin[i] != 0) {
            _pin[i]->output();
        }
    }
}

void BusInOut::input() {
    for (int i=0; i<16; i++) {
        if (_pin[i] != 0) {
            _pin[i]->input();
        }
    }
}

void BusInOut::mode(PinMode pull) {
    for (int i=0; i<16; i++) {
        if (_pin[i] != 0) {
            _pin[i]->mode(pull);
        }
    }
}

#ifdef MBED_OPERATORS
BusInOut& BusInOut::operator= (int v) {
    write(v);
    return *this;
}

BusInOut& BusInOut::operator= (BusInOut& rhs) {
    write(rhs.read());
    return *this;
}

DigitalInOut& BusInOut::operator[] (int index) {
    MBED_ASSERT(index >= 0 && index <= 16);
    MBED_ASSERT(_pin[index]);
    return *_pin[index];
}

BusInOut::operator int() {
    return read();
}
#endif

} // namespace mbed
