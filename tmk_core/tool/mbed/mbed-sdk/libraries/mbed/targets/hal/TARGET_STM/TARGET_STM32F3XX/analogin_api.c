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
#include "wait_api.h"

#if DEVICE_ANALOGIN

#include "cmsis.h"
#include "pinmap.h"

static const PinMap PinMap_ADC[] = {
    {PA_0,  ADC_1, STM_PIN_DATA(GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, 0xFF)}, // ADC_IN1
    {PA_1,  ADC_1, STM_PIN_DATA(GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, 0xFF)}, // ADC_IN2
    {PA_2,  ADC_1, STM_PIN_DATA(GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, 0xFF)}, // ADC_IN3
    {PA_3,  ADC_1, STM_PIN_DATA(GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, 0xFF)}, // ADC_IN4
    {PA_4,  ADC_1, STM_PIN_DATA(GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, 0xFF)}, // ADC_IN5
    {PC_0,  ADC_1, STM_PIN_DATA(GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, 0xFF)}, // ADC_IN6
    {PC_1,  ADC_1, STM_PIN_DATA(GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, 0xFF)}, // ADC_IN7
    {PC_2,  ADC_1, STM_PIN_DATA(GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, 0xFF)}, // ADC_IN8
    {PC_3,  ADC_1, STM_PIN_DATA(GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, 0xFF)}, // ADC_IN9
    {PA_6,  ADC_1, STM_PIN_DATA(GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, 0xFF)}, // ADC_IN10
    {PB_0,  ADC_1, STM_PIN_DATA(GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, 0xFF)}, // ADC_IN11
    {PB_1,  ADC_1, STM_PIN_DATA(GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, 0xFF)}, // ADC_IN12
    {PB_13, ADC_1, STM_PIN_DATA(GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, 0xFF)}, // ADC_IN13
    {PB_11, ADC_1, STM_PIN_DATA(GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, 0xFF)}, // ADC_IN14
    {PA_7,  ADC_1, STM_PIN_DATA(GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, 0xFF)}, // ADC_IN15
    {NC,    NC,    0}
};

int adc_inited = 0;

void analogin_init(analogin_t *obj, PinName pin) {

    ADC_TypeDef     *adc;
    ADC_InitTypeDef ADC_InitStructure;
    ADC_CommonInitTypeDef ADC_CommonInitStructure;

    // Get the peripheral name from the pin and assign it to the object
    obj->adc = (ADCName)pinmap_peripheral(pin, PinMap_ADC);
    MBED_ASSERT(obj->adc == (ADCName)NC);

    // Configure GPIO
    pinmap_pinout(pin, PinMap_ADC);

    // Save pin number for the read function
    obj->pin = pin;

    // The ADC initialization is done once
    if (adc_inited == 0) {
        adc_inited = 1;

        // Get ADC registers structure address
        adc = (ADC_TypeDef *)(obj->adc);

        // Enable ADC clock
        RCC_ADCCLKConfig(RCC_ADC12PLLCLK_Div1);
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC12, ENABLE);

        // Calibration
        ADC_VoltageRegulatorCmd(adc, ENABLE);
        wait_us(10);
        ADC_SelectCalibrationMode(adc, ADC_CalibrationMode_Single);
        ADC_StartCalibration(adc);
        while (ADC_GetCalibrationStatus(adc) != RESET) {}

        // Configure ADC
        ADC_CommonInitStructure.ADC_Mode             = ADC_Mode_Independent;
        ADC_CommonInitStructure.ADC_Clock            = ADC_Clock_AsynClkMode;
        ADC_CommonInitStructure.ADC_DMAAccessMode    = ADC_DMAAccessMode_Disabled;
        ADC_CommonInitStructure.ADC_DMAMode          = ADC_DMAMode_OneShot;
        ADC_CommonInitStructure.ADC_TwoSamplingDelay = 0;
        ADC_CommonInit(adc, &ADC_CommonInitStructure);

        ADC_InitStructure.ADC_ContinuousConvMode    = ADC_ContinuousConvMode_Disable;
        ADC_InitStructure.ADC_Resolution            = ADC_Resolution_12b;
        ADC_InitStructure.ADC_ExternalTrigConvEvent = ADC_ExternalTrigConvEvent_0;
        ADC_InitStructure.ADC_ExternalTrigEventEdge = ADC_ExternalTrigEventEdge_None;
        ADC_InitStructure.ADC_DataAlign             = ADC_DataAlign_Right;
        ADC_InitStructure.ADC_OverrunMode           = ADC_OverrunMode_Disable;
        ADC_InitStructure.ADC_AutoInjMode           = ADC_AutoInjec_Disable;
        ADC_InitStructure.ADC_NbrOfRegChannel       = 1;
        ADC_Init(adc, &ADC_InitStructure);

        // Enable ADC
        ADC_Cmd(adc, ENABLE);

        while (!ADC_GetFlagStatus(adc, ADC_FLAG_RDY)) {}
    }
}

static inline uint16_t adc_read(analogin_t *obj) {
    // Get ADC registers structure address
    ADC_TypeDef *adc = (ADC_TypeDef *)(obj->adc);
    uint8_t channel = 0;

    // Configure ADC channel
    switch (obj->pin) {
        case PA_0:
            channel = ADC_Channel_1;
            break;
        case PA_1:
            channel = ADC_Channel_2;
            break;
        case PA_2:
            channel = ADC_Channel_3;
            break;
        case PA_3:
            channel = ADC_Channel_4;
            break;
        case PA_4:
            channel = ADC_Channel_5;
            break;
        case PC_0:
            channel = ADC_Channel_6;
            break;
        case PC_1:
            channel = ADC_Channel_7;
            break;
        case PC_2:
            channel = ADC_Channel_8;
            break;
        case PC_3:
            channel = ADC_Channel_9;
            break;
        case PA_6:
            channel = ADC_Channel_10;
            break;
        case PB_0:
            channel = ADC_Channel_11;
            break;
        case PB_1:
            channel = ADC_Channel_12;
            break;
        case PB_13:
            channel = ADC_Channel_13;
            break;
        case PB_11:
            channel = ADC_Channel_14;
            break;
        case PA_7:
            channel = ADC_Channel_15;
            break;
        default:
            return 0;
    }

    ADC_RegularChannelConfig(adc, channel, 1, ADC_SampleTime_7Cycles5);

    ADC_StartConversion(adc); // Start conversion

    while (ADC_GetFlagStatus(adc, ADC_FLAG_EOC) == RESET); // Wait end of conversion

    return (ADC_GetConversionValue(adc)); // Get conversion value
}

uint16_t analogin_read_u16(analogin_t *obj) {
    return (adc_read(obj));
}

float analogin_read(analogin_t *obj) {
    uint16_t value = adc_read(obj);
    return (float)value * (1.0f / (float)0xFFF); // 12 bits range
}

#endif
