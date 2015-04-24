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
#include "analogout_api.h"
#include "cmsis.h"
#include "pinmap.h"

void analogout_init(dac_t *obj, PinName pin) {
    MBED_ASSERT(pin == P0_12);
    
    LPC_SYSCON->SYSAHBCLKCTRL0 |= (1 << 29);
    LPC_SYSCON->PDRUNCFG &= ~(1 << 12);
    LPC_IOCON->PIO0_12 = 0;
    LPC_SWM->PINENABLE0 &= ~(1 << 24);
    LPC_DAC->CTRL = 0;
    
    analogout_write_u16(obj, 0);
}

void analogout_free(dac_t *obj)
{
    LPC_SYSCON->SYSAHBCLKCTRL0 &= ~(1 << 29);
    LPC_SWM->PINENABLE0 |= (1 << 24);
}

static inline void dac_write(int value) {
    value &= 0xFFF; // 12-bit
    
    // Set the DAC output
    LPC_DAC->VAL = (value << 4);
}

static inline int dac_read() {
    return ((LPC_DAC->VAL >> 4) & 0xFFF);
}

void analogout_write(dac_t *obj, float value) {
    if (value < 0.0f) {
        dac_write(0);
    } else if (value > 1.0f) {
        dac_write(0xFFF);
    } else {
        dac_write((uint32_t)(value * (float)0xFFF));
    }
}

void analogout_write_u16(dac_t *obj, uint16_t value) {
    dac_write(value);
}

float analogout_read(dac_t *obj) {
    uint32_t value = dac_read();
    return (float)value * (1.0f / (float)0xFFF);
}

uint16_t analogout_read_u16(dac_t *obj) {
    return (uint16_t)dac_read();
}
