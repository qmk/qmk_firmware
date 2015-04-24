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
 *
 * Ported to NXP LPC43XX by Micromint USA <support@micromint.com>
 */
#include "mbed_assert.h"
#include "pinmap.h"
#include "mbed_error.h"

void pin_function(PinName pin, int function) {
    MBED_ASSERT(pin != (PinName)NC);

    __IO uint32_t *reg = (__IO uint32_t*) MBED_SCU_REG(pin);

    // Set pin function
    *reg = function;
}

void pin_mode(PinName pin, PinMode mode) {
    MBED_ASSERT(pin != (PinName)NC); // && (mode != OpenDrain));

    __IO uint32_t *reg = (__IO uint32_t*) MBED_SCU_REG(pin);
    uint32_t tmp = *reg;
    
    // pin mode bits: [4:3] -> 11000 = (0x3 << 3)
    tmp &= ~(0x3 << 3);
    tmp |= (mode & 0x3) << 3;

    *reg = tmp;
}
