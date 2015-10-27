/* mbed Microcontroller Library
 * Copyright (c) 2006-2015 ARM Limited
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
#include "mbed_assert.h"
#include "pinmap.h"

void pin_function(PinName pin, int function) {
    MBED_ASSERT(pin != (PinName)NC);

    uint32_t port_n = (uint32_t)pin >> PORT_SHIFT;
    uint32_t pin_n  = (uint32_t)(pin & 0x7C) >> 2;

    SIM->SCGC5 |= 1 << (SIM_SCGC5_PORTA_SHIFT + port_n);
    __IO uint32_t* pin_pcr = &(((PORT_Type *)(PORTA_BASE + 0x1000 * port_n)))->PCR[pin_n];

    // pin mux bits: [10:8] -> 11100000000 = (0x700)
    *pin_pcr = (*pin_pcr & ~0x700) | (function << 8);
}

void pin_mode(PinName pin, PinMode mode) {
    MBED_ASSERT(pin != (PinName)NC);
    __IO uint32_t* pin_pcr = (__IO uint32_t*)(PORTA_BASE + pin);

    // pin pullup bits: [1:0] -> 11 = (0x3)
    *pin_pcr = (*pin_pcr & ~0x3) | mode;
}
