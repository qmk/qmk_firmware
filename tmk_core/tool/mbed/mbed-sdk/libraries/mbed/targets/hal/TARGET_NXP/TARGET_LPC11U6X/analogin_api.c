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
#include "mbed_error.h"

#if DEVICE_ANALOGIN

#define ANALOGIN_MEDIAN_FILTER      1

#define ADC_10BIT_RANGE             0x3FF
#define ADC_12BIT_RANGE             0xFFF
#define PDRUN_VALID_BITS            0x000025FFL
#define PDRUN_RESERVED_ONE          0x0000C800L

#define ADC_RANGE                   ADC_12BIT_RANGE

static const PinMap PinMap_ADC[] = {
    {P1_9 , ADC_0, 3},
    {P0_23, ADC_1, 1},
    {P0_16, ADC_2, 1},
    {P0_15, ADC_3, 3},
    {P1_22, ADC_4, 3},
    {P1_3 , ADC_5, 4},
    {P0_14, ADC_6, 2},
    {P0_13, ADC_7, 2},
    {P0_12, ADC_8, 2},
    {P0_11, ADC_9, 2},
    {P1_29, ADC_10,4},
    {P0_22, ADC_11,1},
    {NC   , NC    ,0}
};


void analogin_init(analogin_t *obj, PinName pin) {
    volatile uint32_t tmp;
    obj->adc = (ADCName)pinmap_peripheral(pin, PinMap_ADC);
    MBED_ASSERT(obj->adc != (ADCName)NC);

    pinmap_pinout(pin, PinMap_ADC);

    __IO uint32_t *reg = (__IO uint32_t*)(LPC_IOCON_BASE + (pin & 0x1FF));
    // set pin to ADC mode
    *reg &= ~(1 << 7); // set ADMODE = 0 (analog mode)

    // ADC Powered
    tmp = (LPC_SYSCON->PDRUNCFG & PDRUN_VALID_BITS);
    tmp &= ~((1 << 4) & PDRUN_VALID_BITS);
    LPC_SYSCON->PDRUNCFG = (tmp | PDRUN_RESERVED_ONE);

    // Enable clock for ADC
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 13);

    // Determine the clock divider for a 500kHz ADC clock during calibration
    uint32_t clkdiv = (SystemCoreClock / 500000) - 1;
    
    // Perform a self-calibration
    LPC_ADC->CTRL = (1UL << 30) | (clkdiv & 0xFF);
    while ((LPC_ADC->CTRL & (1UL << 30)) != 0);

    // Sampling clock: SystemClock divided by 1
    LPC_ADC->CTRL = 0;
}

static inline uint32_t adc_read(analogin_t *obj) {

    // select channel
    LPC_ADC->SEQA_CTRL &= ~(0xFFF);
    LPC_ADC->SEQA_CTRL |= (1UL << obj->adc);

    // start conversion, sequence enable with async mode
    LPC_ADC->SEQA_CTRL |= ((1UL << 26) | (1UL << 31) | (1UL << 19));
    
    // Repeatedly get the sample data until DONE bit
    volatile uint32_t data;
    do {
        data = LPC_ADC->SEQA_GDAT;
    } while ((data & (1UL << 31)) == 0);
    data = LPC_ADC->DAT[obj->adc];
    
    // Stop conversion
    LPC_ADC->SEQA_CTRL &= ~(1UL << 31);
    
    return ((data >> 4) & ADC_RANGE);
}

static inline void order(uint32_t *a, uint32_t *b) {
    if (*a > *b) {
        uint32_t t = *a;
        *a = *b;
        *b = t;
    }
}

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
    return (value << 4) | ((value >> 8) & 0x000F); // 12 bit
}

float analogin_read(analogin_t *obj) {
    uint32_t value = adc_read_u32(obj);
    return (float)value * (1.0f / (float)ADC_RANGE);
}

#endif
