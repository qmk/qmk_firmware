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
#include "pwmout_api.h"

#if DEVICE_PWMOUT

#include "cmsis.h"
#include "pinmap.h"
#include "fsl_ftm_hal.h"
#include "fsl_mcg_hal.h"
#include "fsl_clock_manager.h"
#include "PeripheralPins.h"

static float pwm_clock_mhz;

void pwmout_init(pwmout_t* obj, PinName pin) {
    PWMName pwm = (PWMName)pinmap_peripheral(pin, PinMap_PWM);
    MBED_ASSERT(pwm != (PWMName)NC);

    obj->pwm_name = pwm;

    uint32_t pwm_base_clock;
    CLOCK_SYS_GetFreq(kBusClock, &pwm_base_clock);
    float clkval = (float)pwm_base_clock / 1000000.0f;
    uint32_t clkdiv = 0;
    while (clkval > 1) {
        clkdiv++;
        clkval /= 2.0f;
        if (clkdiv == 7) {
            break;
        }
    }

    pwm_clock_mhz = clkval;
    uint32_t channel = pwm & 0xF;
    uint32_t instance = pwm >> TPM_SHIFT;
    uint32_t ftm_addrs[] = FTM_BASE_ADDRS;
    CLOCK_SYS_EnableFtmClock(instance);

    FTM_HAL_SetTofFreq(ftm_addrs[instance], 3);
    FTM_HAL_SetClockSource(ftm_addrs[instance], kClock_source_FTM_SystemClk);
    FTM_HAL_SetClockPs(ftm_addrs[instance], (ftm_clock_ps_t)clkdiv);
    FTM_HAL_SetCounter(ftm_addrs[instance], 0);
    // default to 20ms: standard for servos, and fine for e.g. brightness control
    pwmout_period_ms(obj, 20);
    pwmout_write    (obj, 0);
    ftm_pwm_param_t config = {
        .mode = kFtmEdgeAlignedPWM,
        .edgeMode = kFtmHighTrue
    };
    FTM_HAL_EnablePwmMode(ftm_addrs[instance], &config, channel);

    // Wire pinout
    pinmap_pinout(pin, PinMap_PWM);
}

void pwmout_free(pwmout_t* obj) {
}

void pwmout_write(pwmout_t* obj, float value) {
    uint32_t instance = obj->pwm_name >> TPM_SHIFT;
    if (value < 0.0f) {
        value = 0.0f;
    } else if (value > 1.0f) {
        value = 1.0f;
    }
    uint32_t ftm_addrs[] = FTM_BASE_ADDRS;
    uint16_t mod = FTM_HAL_GetMod(ftm_addrs[instance]);
    uint32_t new_count = (uint32_t)((float)(mod) * value);
    // Stop FTM clock to ensure instant update of MOD register
    FTM_HAL_SetClockSource(ftm_addrs[instance], kClock_source_FTM_None);
    FTM_HAL_SetChnCountVal(ftm_addrs[instance], obj->pwm_name & 0xF, new_count);
    FTM_HAL_SetCounter(ftm_addrs[instance], 0);
    FTM_HAL_SetClockSource(ftm_addrs[instance], kClock_source_FTM_SystemClk);
}

float pwmout_read(pwmout_t* obj) {
    uint32_t ftm_addrs[] = FTM_BASE_ADDRS;
    uint16_t count = FTM_HAL_GetChnCountVal(ftm_addrs[obj->pwm_name >> TPM_SHIFT], obj->pwm_name & 0xF, 0);
    uint16_t mod = FTM_HAL_GetMod(ftm_addrs[obj->pwm_name >> TPM_SHIFT]);
    if (mod == 0)
        return 0.0;
    float v = (float)(count) / (float)(mod);
    return (v > 1.0f) ? (1.0f) : (v);
}

void pwmout_period(pwmout_t* obj, float seconds) {
    pwmout_period_us(obj, seconds * 1000000.0f);
}

void pwmout_period_ms(pwmout_t* obj, int ms) {
    pwmout_period_us(obj, ms * 1000);
}

// Set the PWM period, keeping the duty cycle the same.
void pwmout_period_us(pwmout_t* obj, int us) {
    uint32_t instance = obj->pwm_name >> TPM_SHIFT;
    uint32_t ftm_addrs[] = FTM_BASE_ADDRS;
    float dc = pwmout_read(obj);
    // Stop FTM clock to ensure instant update of MOD register
    FTM_HAL_SetClockSource(ftm_addrs[instance], kClock_source_FTM_None);
    FTM_HAL_SetMod(ftm_addrs[instance], (uint32_t)(pwm_clock_mhz * (float)us) - 1);
    pwmout_write(obj, dc);
    FTM_HAL_SetClockSource(ftm_addrs[instance], kClock_source_FTM_SystemClk);
}

void pwmout_pulsewidth(pwmout_t* obj, float seconds) {
    pwmout_pulsewidth_us(obj, seconds * 1000000.0f);
}

void pwmout_pulsewidth_ms(pwmout_t* obj, int ms) {
    pwmout_pulsewidth_us(obj, ms * 1000);
}

void pwmout_pulsewidth_us(pwmout_t* obj, int us) {
    uint32_t ftm_addrs[] = FTM_BASE_ADDRS;
    uint32_t value = (uint32_t)(pwm_clock_mhz * (float)us);
    FTM_HAL_SetChnCountVal(ftm_addrs[obj->pwm_name >> TPM_SHIFT], obj->pwm_name & 0xF, value);
}

#endif
