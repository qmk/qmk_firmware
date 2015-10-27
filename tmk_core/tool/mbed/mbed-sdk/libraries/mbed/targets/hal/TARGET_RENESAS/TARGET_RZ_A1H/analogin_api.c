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
#include "analogin_api.h"

#include "cmsis.h"
#include "pinmap.h"

#include "adc_iodefine.h"
#include "cpg_iodefine.h"

#define ANALOGIN_MEDIAN_FILTER      0

static const PinMap PinMap_ADC[] = {
    {P1_8,  AN0, 1},
    {P1_9,  AN1, 1},
    {P1_10, AN2, 1},
    {P1_11, AN3, 1},
    {P1_12, AN3, 1},
    {P1_13, AN5, 1},
    {P1_14, AN5, 1},
    {P1_15, AN7, 1},
    {NC,    NC,  0}
};

static volatile uint16_t *ADCDR[] = {
    &ADCADDRA,
    &ADCADDRB,
    &ADCADDRC,
    &ADCADDRD,
    &ADCADDRE,
    &ADCADDRF,
    &ADCADDRG,
    &ADCADDRH,
};

void analogin_init(analogin_t *obj, PinName pin) {
    obj->adc = (ADCName)pinmap_peripheral(pin, PinMap_ADC);
    MBED_ASSERT(obj->adc != (ADCName)NC);

    CPGSTBCR3 &= ~(1 << 1);
    CPGSTBCR6 &= ~(1 << 7);

    // 15: ADF 14: ADIE 13: ADST, [12:9] TRGS..0 
    //    [8:6] CKS 010 :: 340tclk 
    //    [5:3] MDS 000 :: single mode 
    //    [2:0] CH  000 :: AN0 
    ADCADCSR = 0x0080; 

    pinmap_pinout(pin, PinMap_ADC);
}

static inline uint32_t adc_read(analogin_t *obj) {
    volatile uint16_t data;

    // Select the appropriate channel and start conversion
    ADCADCSR &= 0xfff8;
    ADCADCSR |= (1 << 13 | (obj->adc & 0x7));

    // Wait end of conversion
    do {
        data = ADCADCSR;
    } while (((data & (1 << 15)) == 0) || ((data & (1 << 13)) != 0));

    // clear flag
    ADCADCSR &= ~(1 << 15);

    return ((*(ADCDR[obj->adc])) >> 4) & 0x0FFF;   // 12 bits range
}

#if ANALOGIN_MEDIAN_FILTER
static inline void order(uint32_t *a, uint32_t *b) {
    if (*a > *b) {
        uint32_t t = *a;
        *a = *b;
        *b = t;
    }
}
#endif

static inline uint32_t adc_read_u32(analogin_t *obj) {
    uint32_t value;
#if ANALOGIN_MEDIAN_FILTER
    uint32_t v1 = adc_read(obj);
    uint32_t v2 = adc_read(obj);
    uint32_t v3 = adc_read(obj);
    order(&v1, &v2);
    order(&v2, &v3);
    order(&v1, &v2);
    value = v2;
#else
    value = adc_read(obj);
#endif
    return value;
}

uint16_t analogin_read_u16(analogin_t *obj) {
    uint32_t value = adc_read_u32(obj);

    return (value << 4) | ((value >> 8) & 0x000F); // 12-bit to 16-bit conversion
}

float analogin_read(analogin_t *obj) {
    uint32_t value = adc_read_u32(obj);

    return (float)value * (1.0f / (float)0x0FFF);  // 12 bits range
}
