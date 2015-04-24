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

static const PinMap PinMap_DAC[] = {
    {P0_26, DAC_0, 2},
    {NC   , NC   , 0}
};

void analogout_init(dac_t *obj, PinName pin) {
    obj->dac = (DACName)pinmap_peripheral(pin, PinMap_DAC);
    MBED_ASSERT(obj->dac != (DACName)NC);
    
    // power is on by default, set DAC clk divider is /4
    LPC_SC->PCLKSEL0 &= ~(0x3 << 22);
    
    // map out (must be done before accessing registers)
    pinmap_pinout(pin, PinMap_DAC);
    
    analogout_write_u16(obj, 0);
}

void analogout_free(dac_t *obj) {}

static inline void dac_write(int value) {
    value &= 0x3FF; // 10-bit
    
    // Set the DAC output
    LPC_DAC->DACR = (0 << 16)       // bias = 0
                  | (value << 6);
}

static inline int dac_read() {
    return (LPC_DAC->DACR >> 6) & 0x3FF;
}

void analogout_write(dac_t *obj, float value) {
    if (value < 0.0f) {
        dac_write(0);
    } else if (value > 1.0f) {
        dac_write(0x3FF);
    } else {
        dac_write(value * (float)0x3FF);
    }
}

void analogout_write_u16(dac_t *obj, uint16_t value) {
    dac_write(value >> 6); // 10-bit
}

float analogout_read(dac_t *obj) {
    uint32_t value = dac_read();
    return (float)value * (1.0f / (float)0x3FF);
}

uint16_t analogout_read_u16(dac_t *obj) {
    uint32_t value = dac_read(); // 10-bit
    return (value << 6) | ((value >> 4) & 0x003F);
}
