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
#include "PeripheralNames.h"

#if DEVICE_ANALOGIN

#define ANALOGIN_MEDIAN_FILTER      1

#define ADC_RANGE    0xFFF

static const PinMap PinMap_ADC[] = {
    {P0_7 , ADC_0, 0},
    {P0_6 , ADC_1, 0},
    {P0_14, ADC_2, 0},
    {P0_23, ADC_3, 0},
    {P0_22, ADC_4, 0},
    {P0_21, ADC_5, 0},
    {P0_20, ADC_6, 0},
    {P0_19, ADC_7, 0},
    {P0_18, ADC_8, 0},
    {P0_17, ADC_9, 0},
    {P0_13, ADC_10,0},
    {P0_4 , ADC_11,0},
};

void analogin_init(analogin_t *obj, PinName pin)
{
    obj->adc = (ADCName)pinmap_peripheral(pin, PinMap_ADC);
    MBED_ASSERT(obj->adc != (ADCName)NC);

    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 6);
    // pin enable
    LPC_SWM->PINENABLE0 &= ~(1UL << (13 + obj->adc));
    // configure GPIO as input
    LPC_GPIO_PORT->DIR0 &= ~(1UL << (pin >> PIN_SHIFT));

    LPC_SYSCON->PDRUNCFG &= ~(1 << 4);
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 24);

    __IO LPC_ADC_Type *adc_reg = LPC_ADC;

    // determine the system clock divider for a 500kHz ADC clock during calibration
    uint32_t clkdiv = (SystemCoreClock / 500000) - 1;

    // perform a self-calibration
    adc_reg->CTRL = (1UL << 30) | (clkdiv & 0xFF);
    while ((adc_reg->CTRL & (1UL << 30)) != 0);
}

static inline uint32_t adc_read(analogin_t *obj)
{
    uint32_t channels;
    __IO LPC_ADC_Type *adc_reg = LPC_ADC;

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

static inline void order(uint32_t *a, uint32_t *b)
{
    if (*a > *b) {
        uint32_t t = *a;
        *a = *b;
        *b = t;
    }
}

static inline uint32_t adc_read_u32(analogin_t *obj)
{
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

uint16_t analogin_read_u16(analogin_t *obj)
{
    uint32_t value = adc_read_u32(obj);
    return (value << 4) | ((value >> 8) & 0x000F); // 12 bit
}

float analogin_read(analogin_t *obj)
{
    uint32_t value = adc_read_u32(obj);
    return (float)value * (1.0f / (float)ADC_RANGE);
}

#endif
