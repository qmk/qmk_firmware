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
#include "analogout_api.h"

#if DEVICE_ANALOGOUT

#include "cmsis.h"
#include "pinmap.h"
#include "mbed_error.h"
#include "PeripheralPins.h"
#include "fsl_clock_manager.h"

#define RANGE_12BIT     0xFFF

void analogout_init(dac_t *obj, PinName pin) {
    obj->dac = (DACName)pinmap_peripheral(pin, PinMap_DAC);
    if (obj->dac == (DACName)NC) {
        error("DAC pin mapping failed");
    }

    SIM_HAL_EnableDacClock(SIM_BASE, 0);

    DAC0->DAT[obj->dac].DATH = 0;
    DAC0->DAT[obj->dac].DATL = 0;

    DAC0->C1 = DAC_C1_DACBFMD(2);     // One-Time Scan Mode

    DAC0->C0 = DAC_C0_DACEN_MASK      // Enable
             | DAC_C0_DACSWTRG_MASK   // Software Trigger
             | DAC_C0_DACRFS_MASK;    // VDDA selected

    analogout_write_u16(obj, 0);
}

void analogout_free(dac_t *obj) {}

static inline void dac_write(dac_t *obj, int value) {
    DAC0->DAT[obj->dac].DATL = (uint8_t)( value       & 0xFF);
    DAC0->DAT[obj->dac].DATH = (uint8_t)((value >> 8) & 0xFF);
}

static inline int dac_read(dac_t *obj) {
    return ((DAC0->DAT[obj->dac].DATH << 8) | DAC0->DAT[obj->dac].DATL);
}

void analogout_write(dac_t *obj, float value) {
    if (value < 0.0f) {
        dac_write(obj, 0);
    } else if (value > 1.0f) {
        dac_write(obj, RANGE_12BIT);
    } else {
        dac_write(obj, value * (float)RANGE_12BIT);
    }
}

void analogout_write_u16(dac_t *obj, uint16_t value) {
    dac_write(obj, value >> 4); // 12-bit
}

float analogout_read(dac_t *obj) {
    uint32_t value = dac_read(obj);
    return (float)value * (1.0f / (float)RANGE_12BIT);
}

uint16_t analogout_read_u16(dac_t *obj) {
    uint32_t value = dac_read(obj); // 12-bit
    return (value << 4) | ((value >> 8) & 0x003F);
}

#endif
