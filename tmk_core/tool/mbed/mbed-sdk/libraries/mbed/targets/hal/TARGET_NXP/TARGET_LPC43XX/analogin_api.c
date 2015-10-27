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
#include "analogin_api.h"
#include "cmsis.h"
#include "pinmap.h"
#include "mbed_error.h"
#include "gpio_api.h"

#define ANALOGIN_MEDIAN_FILTER      1

static inline int div_round_up(int x, int y) {
  return (x + (y - 1)) / y;
}

static const PinMap PinMap_ADC[] = {
    {P4_3,  ADC0_0, 0},
    {P4_1,  ADC0_1, 0},
    {PF_8,  ADC0_2, 0},
    {P7_5,  ADC0_3, 0},
    {P7_4,  ADC0_4, 0},
    {PF_10, ADC0_5, 0},
    {PB_6,  ADC0_6, 0},
    {PC_3,  ADC1_0, 0},
    {PC_0,  ADC1_1, 0},
    {PF_9,  ADC1_2, 0},
    {PF_6,  ADC1_3, 0},
    {PF_5,  ADC1_4, 0},
    {PF_11, ADC1_5, 0},
    {P7_7,  ADC1_6, 0},
    {PF_7,  ADC1_7, 0},
    {NC,    NC,     0   }
};

void analogin_init(analogin_t *obj, PinName pin) {
    ADCName name;

    name = (ADCName)pinmap_peripheral(pin, PinMap_ADC);
    MBED_ASSERT(obj->adc != (LPC_ADC_T *)NC);

    // Set ADC register, number and channel
    obj->num = (name >> ADC0_7) ? 1 : 0;
    obj->ch = name % (ADC0_7 + 1);
    obj->adc = (LPC_ADC_T *) (obj->num > 0) ? LPC_ADC1 : LPC_ADC0;

    // Reset pin function to GPIO
    gpio_set(pin);
    // Select ADC on analog function select register in SCU
    LPC_SCU->ENAIO[obj->num] |= (1 << obj->ch);
    
    // Calculate minimum clock divider
    //  clkdiv = divider - 1
    uint32_t PCLK = SystemCoreClock;
    uint32_t adcRate = 400000;
    uint32_t clkdiv = div_round_up(PCLK, adcRate) - 1;
    
    // Set the generic software-controlled ADC settings
    obj->adc->CR = (0 << 0)      // SEL: 0 = no channels selected
                  | (clkdiv << 8) // CLKDIV:
                  | (0 << 16)     // BURST: 0 = software control
                  | (1 << 21)     // PDN: 1 = operational
                  | (0 << 24)     // START: 0 = no start
                  | (0 << 27);    // EDGE: not applicable
}

static inline uint32_t adc_read(analogin_t *obj) {
    uint32_t temp;
    uint8_t channel = obj->ch;
    LPC_ADC_T *pADC = obj->adc;

    // Select the appropriate channel and start conversion
    pADC->CR |= ADC_CR_CH_SEL(channel);
    temp = pADC->CR & ~ADC_CR_START_MASK;
    pADC->CR = temp | (ADC_CR_START_MODE_SEL(ADC_START_NOW));

    // Wait for DONE bit and read data
    while (!(pADC->STAT & ADC_CR_CH_SEL(channel)));
    temp = pADC->DR[channel];

    // Deselect channel and return result
    pADC->CR &= ~ADC_CR_START_MASK;
    pADC->CR &= ~ADC_CR_CH_SEL(channel);
    return ADC_DR_RESULT(temp);
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
