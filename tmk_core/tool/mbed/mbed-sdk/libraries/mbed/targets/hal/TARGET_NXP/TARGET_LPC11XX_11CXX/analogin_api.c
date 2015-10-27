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

static const PinMap PinMap_ADC[] = {
    {P0_11, ADC0_0, 2},
    {P1_0 , ADC0_1, 2},
    {P1_1 , ADC0_2, 2},
    {P1_2 , ADC0_3, 2},
    // {P1_3 , ADC0_4, 2}, -- should be mapped to SWDIO only
    {P1_4 , ADC0_5, 1},
    {P1_10, ADC0_6, 1},
    {P1_11, ADC0_7, 1},
    {NC   , NC    , 0}
};

#define ANALOGIN_MEDIAN_FILTER      1

#define ADC_10BIT_RANGE             0x3FF
#define ADC_12BIT_RANGE             0xFFF

static inline int div_round_up(int x, int y) {
  return (x + (y - 1)) / y;
}

#define ADC_RANGE    ADC_10BIT_RANGE

void analogin_init(analogin_t *obj, PinName pin) {
    obj->adc = (ADCName)pinmap_peripheral(pin, PinMap_ADC);
    MBED_ASSERT(obj->adc != (uint32_t)NC);
    
    // Power up ADC
    LPC_SYSCON->PDRUNCFG &= ~ (1 << 4);
    LPC_SYSCON->SYSAHBCLKCTRL |= ((uint32_t)1 << 13);

    uint32_t offset = (uint32_t)pin & 0xff;
    __IO uint32_t *reg = (__IO uint32_t*)(LPC_IOCON_BASE + offset);

    // set pin to ADC mode
    *reg &= ~(1 << 7); // set ADMODE = 0 (analog mode)

    uint32_t PCLK = SystemCoreClock;
    uint32_t MAX_ADC_CLK = 4500000;
    uint32_t clkdiv = div_round_up(PCLK, MAX_ADC_CLK) - 1;

    LPC_ADC->CR = (0 << 0)      // no channels selected
                | (clkdiv << 8) // max of 4.5MHz
                | (0 << 16)     // BURST = 0, software controlled
                | ( 0 << 17 );  // CLKS = 0, not applicable
    
    pinmap_pinout(pin, PinMap_ADC);
}

static inline uint32_t adc_read(analogin_t *obj) {
    // Select the appropriate channel and start conversion
    LPC_ADC->CR &= ~0xFF;
    LPC_ADC->CR |= 1 << (int)obj->adc;
    LPC_ADC->CR |= 1 << 24;
    
    // Repeatedly get the sample data until DONE bit
    unsigned int data;
    do {
        data = LPC_ADC->GDR;
    } while ((data & ((unsigned int)1 << 31)) == 0);
    
    // Stop conversion
    LPC_ADC->CR &= ~(1 << 24);
    
    return (data >> 6) & ADC_RANGE; // 10 bit
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
    
    return (value << 6) | ((value >> 4) & 0x003F); // 10 bit
}

float analogin_read(analogin_t *obj) {
    uint32_t value = adc_read_u32(obj);
    return (float)value * (1.0f / (float)ADC_RANGE);
}
