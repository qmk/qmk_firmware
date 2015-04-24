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
#include "analogout_api.h"

#if DEVICE_ANALOGOUT

#include "cmsis.h"
#include "pinmap.h"
#include "mbed_error.h"
#include "PeripheralPins.h"

#define DAC_RANGE (0xFFF) // 12 bits

static DAC_HandleTypeDef DacHandle;

// These variables are used for the "free" function
static int pa4_used = 0;
static int pa5_used = 0;

void analogout_init(dac_t *obj, PinName pin)
{
    DAC_ChannelConfTypeDef sConfig;

    // Get the peripheral name from the pin and assign it to the object
    obj->dac = (DACName)pinmap_peripheral(pin, PinMap_DAC);
    MBED_ASSERT(obj->dac != (DACName)NC);

    // Configure GPIO
    pinmap_pinout(pin, PinMap_DAC);

    // Save the pin for future use
    obj->pin = pin;

    // Enable DAC clock
    if (obj->dac == DAC_1) {
        __DAC1_CLK_ENABLE();
    }
#if defined(__DAC2_FORCE_RESET)
    if (obj->dac == DAC_2) {
        __DAC2_CLK_ENABLE();
    }
#endif

    // Configure DAC
    DacHandle.Instance = (DAC_TypeDef *)(obj->dac);

    sConfig.DAC_Trigger      = DAC_TRIGGER_NONE;
    sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_DISABLE;

    if (pin == PA_4) {
        HAL_DAC_ConfigChannel(&DacHandle, &sConfig, DAC_CHANNEL_1);
        pa4_used = 1;
    }

#if defined(DAC_CHANNEL_2)
    if (pin == PA_5) {
        HAL_DAC_ConfigChannel(&DacHandle, &sConfig, DAC_CHANNEL_2);
        pa5_used = 1;
    }
#endif

    if (pin == PA_6) {
        HAL_DAC_ConfigChannel(&DacHandle, &sConfig, DAC_CHANNEL_1);
    }

    analogout_write_u16(obj, 0);
}

void analogout_free(dac_t *obj)
{
    // Reset DAC and disable clock
    if (obj->pin == PA_4) pa4_used = 0;
    if (obj->pin == PA_5) pa5_used = 0;

    if ((pa4_used == 0) && (pa5_used == 0)) {
        __DAC1_FORCE_RESET();
        __DAC1_RELEASE_RESET();
        __DAC1_CLK_DISABLE();
    }

#if defined(__DAC2_FORCE_RESET)
    if (obj->pin == PA_6) {
        __DAC2_FORCE_RESET();
        __DAC2_RELEASE_RESET();
        __DAC2_CLK_DISABLE();
    }
#endif

    // Configure GPIO
    pin_function(obj->pin, STM_PIN_DATA(STM_MODE_INPUT, GPIO_NOPULL, 0));
}

static inline void dac_write(dac_t *obj, uint16_t value)
{
    if ((obj->pin == PA_4) || (obj->pin == PA_6)) {
        HAL_DAC_SetValue(&DacHandle, DAC_CHANNEL_1, DAC_ALIGN_12B_R, value);
        HAL_DAC_Start(&DacHandle, DAC_CHANNEL_1);
    }

#if defined(DAC_CHANNEL_2)
    if (obj->pin == PA_5) {
        HAL_DAC_SetValue(&DacHandle, DAC_CHANNEL_2, DAC_ALIGN_12B_R, value);
        HAL_DAC_Start(&DacHandle, DAC_CHANNEL_2);
    }
#endif
}

static inline int dac_read(dac_t *obj)
{
    if ((obj->pin == PA_4) || (obj->pin == PA_6)) {
        return (int)HAL_DAC_GetValue(&DacHandle, DAC_CHANNEL_1);
#if defined(DAC_CHANNEL_2)
    } else if (obj->pin == PA_5) {
        return (int)HAL_DAC_GetValue(&DacHandle, DAC_CHANNEL_2);
#endif
    } else {
        return 0;
    }
}

void analogout_write(dac_t *obj, float value)
{
    if (value < 0.0f) {
        dac_write(obj, 0); // Min value
    } else if (value > 1.0f) {
        dac_write(obj, (uint16_t)DAC_RANGE); // Max value
    } else {
        dac_write(obj, (uint16_t)(value * (float)DAC_RANGE));
    }
}

void analogout_write_u16(dac_t *obj, uint16_t value)
{
    if (value > (uint16_t)DAC_RANGE) {
        dac_write(obj, (uint16_t)DAC_RANGE); // Max value
    } else {
        dac_write(obj, value);
    }
}

float analogout_read(dac_t *obj)
{
    uint32_t value = dac_read(obj);
    return (float)((float)value * (1.0f / (float)DAC_RANGE));
}

uint16_t analogout_read_u16(dac_t *obj)
{
    return (uint16_t)dac_read(obj);
}

#endif // DEVICE_ANALOGOUT
