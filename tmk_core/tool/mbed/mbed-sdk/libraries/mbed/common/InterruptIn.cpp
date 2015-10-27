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
#include "InterruptIn.h"

#if DEVICE_INTERRUPTIN

namespace mbed {

InterruptIn::InterruptIn(PinName pin) : gpio(),
                                        gpio_irq(),
                                        _rise(),
                                        _fall() {
    gpio_irq_init(&gpio_irq, pin, (&InterruptIn::_irq_handler), (uint32_t)this);
    gpio_init_in(&gpio, pin);
}

InterruptIn::~InterruptIn() {
    gpio_irq_free(&gpio_irq);
}

int InterruptIn::read() {
    return gpio_read(&gpio);
}

void InterruptIn::mode(PinMode pull) {
    gpio_mode(&gpio, pull);
}

void InterruptIn::rise(void (*fptr)(void)) {
    if (fptr) {
        _rise.attach(fptr);
        gpio_irq_set(&gpio_irq, IRQ_RISE, 1);
    } else {
        gpio_irq_set(&gpio_irq, IRQ_RISE, 0);
    }
}

void InterruptIn::fall(void (*fptr)(void)) {
    if (fptr) {
        _fall.attach(fptr);
        gpio_irq_set(&gpio_irq, IRQ_FALL, 1);
    } else {
        gpio_irq_set(&gpio_irq, IRQ_FALL, 0);
    }
}

void InterruptIn::_irq_handler(uint32_t id, gpio_irq_event event) {
    InterruptIn *handler = (InterruptIn*)id;
    switch (event) {
        case IRQ_RISE: handler->_rise.call(); break;
        case IRQ_FALL: handler->_fall.call(); break;
        case IRQ_NONE: break;
    }
}

void InterruptIn::enable_irq() {
    gpio_irq_enable(&gpio_irq);
}

void InterruptIn::disable_irq() {
    gpio_irq_disable(&gpio_irq);
}

#ifdef MBED_OPERATORS
InterruptIn::operator int() {
    return read();
}
#endif

} // namespace mbed

#endif
