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
#include "mbed_assert.h"
#include "pinmap.h"
#include "mbed_error.h"

__IO uint32_t* IOCON_REGISTERS[18] = {
        &LPC_IOCON->PIO0_0 , &LPC_IOCON->PIO0_1 , &LPC_IOCON->PIO0_2 ,
        &LPC_IOCON->PIO0_3 , &LPC_IOCON->PIO0_4 , &LPC_IOCON->PIO0_5 ,
        &LPC_IOCON->PIO0_6 , &LPC_IOCON->PIO0_7 , &LPC_IOCON->PIO0_8 ,
        &LPC_IOCON->PIO0_9 , &LPC_IOCON->PIO0_10, &LPC_IOCON->PIO0_11,
        &LPC_IOCON->PIO0_12, &LPC_IOCON->PIO0_13, &LPC_IOCON->PIO0_14,
        &LPC_IOCON->PIO0_15, &LPC_IOCON->PIO0_16, &LPC_IOCON->PIO0_17,
};

void pin_function(PinName pin, int function) {
    
}

void pin_mode(PinName pin, PinMode mode) {
    MBED_ASSERT(pin != (PinName)NC);

    if ((pin == 10) || (pin == 11)) {
        // True open-drain pins can be configured for different I2C-bus speeds
        return;
    }
    
    __IO uint32_t *reg = IOCON_REGISTERS[pin];
    
    if (mode == OpenDrain) {
        *reg |= (1 << 10);
    } else {
        uint32_t tmp = *reg;
        tmp &= ~(0x3 << 3);
        tmp |= (mode & 0x3) << 3;
        *reg = tmp;
    }
}
