/* mbed Microcontroller Library
 * Copyright (c) 2014, STMicroelectronics
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "mbed_assert.h"
#include "analogin_api.h"

#if DEVICE_ANALOGIN

#include "wait_api.h"
#include "cmsis.h"
#include "pinmap.h"
#include "PeripheralPins.h"

ADC_HandleTypeDef AdcHandle;

int adc_inited = 0;

void analogin_init(analogin_t *obj, PinName pin)
{
    RCC_PeriphCLKInitTypeDef  PeriphClkInit;

    // Get the peripheral name from the pin and assign it to the object
    obj->adc = (ADCName)pinmap_peripheral(pin, PinMap_ADC);
    MBED_ASSERT(obj->adc != (ADCName)NC);

    // Configure GPIO
    pinmap_pinout(pin, PinMap_ADC);

    // Save pin number for the read function
    obj->pin = pin;

    // The ADC initialization is done once
    if (adc_inited == 0) {
        adc_inited = 1;

        // Enable ADC clock
        __HAL_RCC_ADC1_CLK_ENABLE();

        // Configure ADC clock prescaler
        // Caution: On STM32F1, ADC clock frequency max is 14 MHz (refer to device datasheet).
        // Therefore, ADC clock prescaler must be configured in function
        // of ADC clock source frequency to remain below this maximum frequency.
        // with 8 MHz external xtal: PCLK2 = 72 MHz --> ADC clock = 72/6 = 12 MHz
        // with internal clock     : PCLK2 = 64 MHz --> ADC clock = 64/6 = 10.67 MHz
        PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
        PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
        HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

        // Configure ADC
        AdcHandle.Instance = (ADC_TypeDef *)(obj->adc);
        AdcHandle.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
        AdcHandle.Init.ScanConvMode          = DISABLE;
        AdcHandle.Init.ContinuousConvMode    = DISABLE;
        AdcHandle.Init.NbrOfConversion       = 1;
        AdcHandle.Init.DiscontinuousConvMode = DISABLE;
        AdcHandle.Init.NbrOfDiscConversion   = 0;
        AdcHandle.Init.ExternalTrigConv      = ADC_EXTERNALTRIGCONV_T1_CC1;
        HAL_ADC_Init(&AdcHandle);
    }
}

static inline uint16_t adc_read(analogin_t *obj)
{
    ADC_ChannelConfTypeDef sConfig;

    AdcHandle.Instance = (ADC_TypeDef *)(obj->adc);

    // Configure ADC channel
    sConfig.Rank         = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_7CYCLES_5;

    switch (obj->pin) {
        case PA_0:
            sConfig.Channel = ADC_CHANNEL_0;
            break;
        case PA_1:
            sConfig.Channel = ADC_CHANNEL_1;
            break;
        case PA_2:
            sConfig.Channel = ADC_CHANNEL_2;
            break;
        case PA_3:
            sConfig.Channel = ADC_CHANNEL_3;
            break;
        case PA_4:
            sConfig.Channel = ADC_CHANNEL_4;
            break;
        case PA_5:
            sConfig.Channel = ADC_CHANNEL_5;
            break;
        case PA_6:
            sConfig.Channel = ADC_CHANNEL_6;
            break;
        case PA_7:
            sConfig.Channel = ADC_CHANNEL_7;
            break;
        case PB_0:
            sConfig.Channel = ADC_CHANNEL_8;
            break;
        case PB_1:
            sConfig.Channel = ADC_CHANNEL_9;
            break;
        case PC_0:
            sConfig.Channel = ADC_CHANNEL_10;
            break;
        case PC_1:
            sConfig.Channel = ADC_CHANNEL_11;
            break;
        case PC_2:
            sConfig.Channel = ADC_CHANNEL_12;
            break;
        case PC_3:
            sConfig.Channel = ADC_CHANNEL_13;
            break;
        case PC_4:
            sConfig.Channel = ADC_CHANNEL_14;
            break;
        case PC_5:
            sConfig.Channel = ADC_CHANNEL_15;
            break;
        default:
            return 0;
    }

    HAL_ADC_ConfigChannel(&AdcHandle, &sConfig);

    HAL_ADC_Start(&AdcHandle); // Start conversion

    // Wait end of conversion and get value
    if (HAL_ADC_PollForConversion(&AdcHandle, 10) == HAL_OK) {
        return (HAL_ADC_GetValue(&AdcHandle));
    } else {
        return 0;
    }
}

uint16_t analogin_read_u16(analogin_t *obj)
{
    uint16_t value = adc_read(obj);
    // 12-bit to 16-bit conversion
    value = ((value << 4) & (uint16_t)0xFFF0) | ((value >> 8) & (uint16_t)0x000F);
    return value;
}

float analogin_read(analogin_t *obj)
{
    uint16_t value = adc_read(obj);
    return (float)value * (1.0f / (float)0xFFF); // 12 bits range
}

#endif
