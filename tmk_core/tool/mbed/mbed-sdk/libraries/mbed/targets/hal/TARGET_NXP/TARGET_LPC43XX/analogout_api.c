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
#include "analogout_api.h"

#include "cmsis.h"
#include "pinmap.h"
#include "mbed_error.h"
#include "gpio_api.h"

static const PinMap PinMap_DAC[] = {
#ifdef TARGET_LPC4337
    {P4_3, DAC_0, 0},
#else
    {P4_4, DAC_0, 0},
#endif
    {NC,   NC,    0}
};

void analogout_init(dac_t *obj, PinName pin) {
    obj->dac = (DACName)pinmap_peripheral(pin, PinMap_DAC);
    MBED_ASSERT(obj->dac != (DACName)NC);

    // Reset pin function to GPIO
    gpio_set(pin);
    // Select DAC on analog function select register in SCU
    LPC_SCU->ENAIO[2] |= 1; // Sets pin as DAC

    // Set bias=0 for maximum DAC update rate (1 MHz)
    LPC_DAC->CR &= ~DAC_BIAS_EN;
    // Enable DAC and DMA
    LPC_DAC->CTRL |= DAC_DMA_ENA;
	
    analogout_write_u16(obj, 0);
}

void analogout_free(dac_t *obj) {}

static inline void dac_write(int value) {
    
    // Set the DAC output
    LPC_DAC->CR = DAC_SET(value);
}

static inline int dac_read() {
    return (DAC_GET(LPC_DAC->CR));
}

void analogout_write(dac_t *obj, float value) {
    if (value < 0.0f) {
        dac_write(0);
    } else if (value > 1.0f) {
        dac_write(DAC_RANGE);
    } else {
        dac_write(value * (float)DAC_RANGE);
    }
}

void analogout_write_u16(dac_t *obj, uint16_t value) {
    dac_write(value >> 6); // 10-bit
}

float analogout_read(dac_t *obj) {
    uint32_t value = dac_read();
    return (float)value * (1.0f / (float)DAC_RANGE);
}

uint16_t analogout_read_u16(dac_t *obj) {
    uint32_t value = dac_read(); // 10-bit
    return (value << 6) | ((value >> 4) & 0x003F);
}
