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

#define ANALOGIN_MEDIAN_FILTER      1

#define ADC_10BIT_RANGE             0x3FF
#define ADC_12BIT_RANGE             0xFFF

#define ADC_RANGE    ADC_12BIT_RANGE

static const PinMap PinMap_ADC[] = {
    {P0_8 , ADC0_0, 0},
    {P0_7 , ADC0_1, 0},
    {P0_6 , ADC0_2, 0},
    {P0_5 , ADC0_3, 0},
    {P0_4 , ADC0_4, 0},
    {P0_3 , ADC0_5, 0},
    {P0_2 , ADC0_6, 0},
    {P0_1 , ADC0_7, 0},
    {P1_0 , ADC0_8, 0},
    {P0_31, ADC0_9, 0},
    {P0_0 , ADC0_10,0},
    {P0_30, ADC0_11,0},
    {P1_1 , ADC1_0, 0},
    {P0_9 , ADC1_1, 0},
    {P0_10, ADC1_2, 0},
    {P0_11, ADC1_3, 0},
    {P1_2 , ADC1_4, 0},
    {P1_3 , ADC1_5, 0},
    {P0_13, ADC1_6, 0},
    {P0_14, ADC1_7, 0},
    {P0_15, ADC1_8, 0},
    {P0_16, ADC1_9, 0},
    {P1_4 , ADC1_10,0},
    {P1_5 , ADC1_11,0},
};

void analogin_init(analogin_t *obj, PinName pin) {
    obj->adc = (ADCName)pinmap_peripheral(pin, PinMap_ADC);
    MBED_ASSERT(obj->adc != (ADCName)NC);

    uint32_t port = (pin >> 5);
    // enable clock for GPIOx
    LPC_SYSCON->SYSAHBCLKCTRL0 |= (1UL << (14 + port));
    // pin enable
    LPC_SWM->PINENABLE0 &= ~(1UL << obj->adc);
    // configure GPIO as input
    LPC_GPIO_PORT->DIR[port] &= ~(1UL << (pin & 0x1F));
    
    // power up ADC
    if (obj->adc < ADC1_0)
    {
        // ADC0
        LPC_SYSCON->PDRUNCFG &= ~(1 << 10);
        LPC_SYSCON->SYSAHBCLKCTRL0 |= (1 << 27);
    }
    else {
        // ADC1
        LPC_SYSCON->PDRUNCFG &= ~(1 << 11);
        LPC_SYSCON->SYSAHBCLKCTRL0 |= (1 << 28);
    }

    // select IRC as asynchronous clock, divided by 1
    LPC_SYSCON->ADCASYNCCLKSEL  = 0;
    LPC_SYSCON->ADCASYNCCLKDIV  = 1;

    __IO LPC_ADC0_Type *adc_reg = (obj->adc < ADC1_0) ? (__IO LPC_ADC0_Type*)(LPC_ADC0) : (__IO LPC_ADC0_Type*)(LPC_ADC1);

    // determine the system clock divider for a 500kHz ADC clock during calibration
    uint32_t clkdiv = (SystemCoreClock / 500000) - 1;
    
    // perform a self-calibration
    adc_reg->CTRL = (1UL << 30) | (clkdiv & 0xFF);
    while ((adc_reg->CTRL & (1UL << 30)) != 0);

    // switch to asynchronous mode
    adc_reg->CTRL = (1UL << 8);
}

static inline uint32_t adc_read(analogin_t *obj) {
    uint32_t channels;

    __IO LPC_ADC0_Type *adc_reg = (obj->adc < ADC1_0) ? (__IO LPC_ADC0_Type*)(LPC_ADC0) : (__IO LPC_ADC0_Type*)(LPC_ADC1);

    if (obj->adc >= ADC1_0)
        channels = ((obj->adc - ADC1_0) & 0x1F);
    else
        channels = (obj->adc & 0x1F);

    // select channel
    adc_reg->SEQA_CTRL &= ~(0xFFF);
    adc_reg->SEQA_CTRL |= (1UL << channels);

    // start conversion and sequence enable
    adc_reg->SEQA_CTRL |= ((1UL << 26) | (1UL << 31));
    
    // Repeatedly get the sample data until DONE bit
    volatile uint32_t data;
    do {
        data = adc_reg->SEQA_GDAT;
    } while ((data & (1UL << 31)) == 0);
    
    // Stop conversion
    adc_reg->SEQA_CTRL &= ~(1UL << 31);
    
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
