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

#if DEVICE_ANALOGIN

#include "cmsis.h"
#include "pinmap.h"
#include "PeripheralNames.h"
#include "fsl_adc_hal.h"
#include "fsl_clock_manager.h"
#include "PeripheralPins.h"
#include "fsl_device_registers.h"

#define MAX_FADC 6000000

void analogin_init(analogin_t *obj, PinName pin) {
    obj->adc = (ADCName)pinmap_peripheral(pin, PinMap_ADC);
    MBED_ASSERT(obj->adc != (ADCName)NC);

    uint32_t instance = obj->adc >> ADC_INSTANCE_SHIFT;
    uint32_t adc_addrs[] = ADC_BASE_ADDRS;

    CLOCK_SYS_EnableAdcClock(instance);

    uint32_t bus_clock;
    CLOCK_SYS_GetFreq(kBusClock, &bus_clock);
    uint32_t clkdiv;
    for (clkdiv = 0; clkdiv < 4; clkdiv++) {
        if ((bus_clock >> clkdiv) <= MAX_FADC)
            break;
    }
    if (clkdiv == 4) {
        clkdiv = 0x3; //Set max div
    }
    /* adc is enabled/triggered when reading. */
    ADC_HAL_Init(adc_addrs[instance]);
    ADC_HAL_SetClkSrcMode(adc_addrs[instance], kAdcClkSrcOfBusClk);
    ADC_HAL_SetClkDividerMode(adc_addrs[instance], (adc_clk_divider_mode_t)(clkdiv & 0x3));
    ADC_HAL_SetRefVoltSrcMode(adc_addrs[instance], kAdcRefVoltSrcOfVref);
    ADC_HAL_SetResolutionMode(adc_addrs[instance], kAdcResolutionBitOfSingleEndAs16);
    ADC_HAL_SetContinuousConvCmd(adc_addrs[instance], false);
    ADC_HAL_SetHwTriggerCmd(adc_addrs[instance], false); /* sw trigger */
    ADC_HAL_SetHwAverageCmd(adc_addrs[instance], true);
    ADC_HAL_SetHwAverageMode(adc_addrs[instance], kAdcHwAverageCountOf4);
    ADC_HAL_SetChnMuxMode(adc_addrs[instance], kAdcChnMuxOfB); /* only B channels are avail */

    pinmap_pinout(pin, PinMap_ADC);
}

uint16_t analogin_read_u16(analogin_t *obj) {
    uint32_t instance = obj->adc >> ADC_INSTANCE_SHIFT;
    uint32_t adc_addrs[] = ADC_BASE_ADDRS;
    /* sw trigger (SC1A) */
    ADC_HAL_ConfigChn(adc_addrs[instance], 0, false, false, obj->adc & 0xF);
    while (!ADC_HAL_GetChnConvCompletedCmd(adc_addrs[instance], 0));
    return ADC_HAL_GetChnConvValueRAW(adc_addrs[instance], 0);
}

float analogin_read(analogin_t *obj) {
    uint16_t value = analogin_read_u16(obj);
    return (float)value * (1.0f / (float)0xFFFF);
}

#endif
