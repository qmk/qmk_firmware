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
#include "analogout_api.h"

#if DEVICE_ANALOGOUT

#include "cmsis.h"
#include "pinmap.h"
#include "mbed_error.h"
#include "stm32f4xx_hal.h"
#include "PeripheralPins.h"

#define RANGE_12BIT (0xFFF)

DAC_HandleTypeDef    DacHandle;
static DAC_ChannelConfTypeDef sConfig;

void analogout_init(dac_t *obj, PinName pin)
{
    uint32_t channel ;
    HAL_StatusTypeDef status;

    // Get the peripheral name (DAC_1, ...) from the pin and assign it to the object
    obj->dac = (DACName)pinmap_peripheral(pin, PinMap_DAC);
    // Get the functions (dac channel) from the pin and assign it to the object
    uint32_t function = pinmap_function(pin, PinMap_DAC);
    MBED_ASSERT(function != (uint32_t)NC);
    // Save the channel for the write and read functions
    obj->channel = STM_PIN_CHANNEL(function);

    if (obj->dac == (DACName)NC) {
        error("DAC pin mapping failed");
    }

    // Configure GPIO
    pinmap_pinout(pin, PinMap_DAC);

    __GPIOA_CLK_ENABLE();

    __DAC_CLK_ENABLE();

    DacHandle.Instance = DAC;

    status = HAL_DAC_Init(&DacHandle);
    if ( status != HAL_OK ) {
        error("HAL_DAC_Init failed");
    }

    sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
    sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;

    if (obj->channel == 1) {
        channel = DAC_CHANNEL_1; 
    } else {
        channel = DAC_CHANNEL_2;
    }

    if (HAL_DAC_ConfigChannel(&DacHandle, &sConfig, channel) != HAL_OK) {
        error("HAL_DAC_ConfigChannel failed");
    }

    if (HAL_DAC_Start(&DacHandle, channel) != HAL_OK) {
        error("HAL_DAC_Start failed");
    }

    if (HAL_DAC_SetValue(&DacHandle, channel, DAC_ALIGN_12B_R, 0x000) != HAL_OK) {
        error("HAL_DAC_SetValue failed");
    }

}

void analogout_free(dac_t *obj)
{
}

static inline void dac_write(dac_t *obj, uint16_t value)
{
    HAL_StatusTypeDef status = HAL_ERROR;

    if (obj->channel == 1) {
        status = HAL_DAC_SetValue(&DacHandle, DAC_CHANNEL_1, DAC_ALIGN_12B_R, value);
    } else if (obj->channel == 2) {
        status = HAL_DAC_SetValue(&DacHandle, DAC_CHANNEL_2, DAC_ALIGN_12B_R, value);
    }

    if ( status != HAL_OK ) {
        error("DAC pin mapping failed");
    }
}

static inline int dac_read(dac_t *obj)
{
    if (obj->channel == 1) {
        return (int)HAL_DAC_GetValue(&DacHandle, DAC_CHANNEL_1);
    } else if (obj->channel == 2) {
        return (int)HAL_DAC_GetValue(&DacHandle, DAC_CHANNEL_2);
    }
	return 0;	/* Just silented warning */
}

void analogout_write(dac_t *obj, float value)
{
    if (value < 0.0f) {
        dac_write(obj, 0); // Min value
    } else if (value > 1.0f) {
        dac_write(obj, (uint16_t)RANGE_12BIT); // Max value
    } else {
        dac_write(obj, (uint16_t)(value * (float)RANGE_12BIT));
    }
}

void analogout_write_u16(dac_t *obj, uint16_t value)
{
    if (value > (uint16_t)RANGE_12BIT) {
        value = (uint16_t)RANGE_12BIT; // Max value
    }

    dac_write(obj, value);
}

float analogout_read(dac_t *obj)
{

    uint32_t value = dac_read(obj);
    return (float)value * (1.0f / (float)RANGE_12BIT);
}

uint16_t analogout_read_u16(dac_t *obj)
{
    return (uint16_t)dac_read(obj);
}

#endif // DEVICE_ANALOGOUT
