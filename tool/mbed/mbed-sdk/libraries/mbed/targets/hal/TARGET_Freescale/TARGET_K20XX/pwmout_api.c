/* mbed Microcontroller Library
 * Copyright (c) 2006-2015 ARM Limited
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

#include "cmsis.h"
#include "pinmap.h"
#include "PeripheralPins.h"

static float pwm_clock = 0;

void pwmout_init(pwmout_t* obj, PinName pin) {
    // determine the channel
    PWMName pwm = (PWMName)pinmap_peripheral(pin, PinMap_PWM);
    MBED_ASSERT(pwm != (PWMName)NC);

    uint32_t clkdiv = 0;
    float clkval = SystemCoreClock / 1000000.0f;

    while (clkval > 1) {
        clkdiv++;
        clkval /= 2.0;
        if (clkdiv == 7)
            break;
    }

    pwm_clock = clkval;
    unsigned int ftm_n = (pwm >> TPM_SHIFT);
    unsigned int ch_n = (pwm & 0xFF);

    SIM->SCGC6 |= 1 << (SIM_SCGC6_FTM0_SHIFT + ftm_n);

    FTM_Type *ftm = (FTM_Type *)(FTM0_BASE + 0x1000 * ftm_n);
    ftm->CONF |= FTM_CONF_BDMMODE(3);
    ftm->SC = FTM_SC_CLKS(1) | FTM_SC_PS(clkdiv); // (clock)MHz / clkdiv ~= (0.75)MHz
    ftm->CONTROLS[ch_n].CnSC = (FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK); /* No Interrupts; High True pulses on Edge Aligned PWM */
    ftm->MODE = FTM_MODE_FTMEN_MASK;
    ftm->SYNC = FTM_SYNC_CNTMIN_MASK;
    ftm->SYNCONF = FTM_SYNCONF_SYNCMODE_MASK | FTM_SYNCONF_SWSOC_MASK | FTM_SYNCONF_SWWRBUF_MASK;
    
    //Without SYNCEN set CnV does not seem to update
    ftm->COMBINE = FTM_COMBINE_SYNCEN0_MASK | FTM_COMBINE_SYNCEN1_MASK | FTM_COMBINE_SYNCEN2_MASK | FTM_COMBINE_SYNCEN3_MASK;

    obj->CnV = &ftm->CONTROLS[ch_n].CnV;
    obj->MOD = &ftm->MOD;
    obj->SYNC = &ftm->SYNC;

    // default to 20ms: standard for servos, and fine for e.g. brightness control
    pwmout_period_ms(obj, 20);
    pwmout_write(obj, 0.0);
    
    // Wire pinout
    pinmap_pinout(pin, PinMap_PWM);
}

void pwmout_free(pwmout_t* obj) {}

void pwmout_write(pwmout_t* obj, float value) {
    if (value < 0.0) {
        value = 0.0;
    } else if (value > 1.0) {
        value = 1.0;
    }
    
    while(*obj->SYNC & FTM_SYNC_SWSYNC_MASK);
    *obj->CnV = (uint32_t)((float)(*obj->MOD + 1) * value);
    *obj->SYNC |= FTM_SYNC_SWSYNC_MASK;    
}

float pwmout_read(pwmout_t* obj) {
    while(*obj->SYNC & FTM_SYNC_SWSYNC_MASK);
    float v = (float)(*obj->CnV) / (float)(*obj->MOD + 1);
    return (v > 1.0) ? (1.0) : (v);
}

void pwmout_period(pwmout_t* obj, float seconds) {
    pwmout_period_us(obj, seconds * 1000000.0f);
}

void pwmout_period_ms(pwmout_t* obj, int ms) {
    pwmout_period_us(obj, ms * 1000);
}

// Set the PWM period, keeping the duty cycle the same.
void pwmout_period_us(pwmout_t* obj, int us) {
    float dc = pwmout_read(obj);
    *obj->MOD = (uint32_t)(pwm_clock * (float)us) - 1;
    *obj->SYNC |= FTM_SYNC_SWSYNC_MASK;
    pwmout_write(obj, dc);
}

void pwmout_pulsewidth(pwmout_t* obj, float seconds) {
    pwmout_pulsewidth_us(obj, seconds * 1000000.0f);
}

void pwmout_pulsewidth_ms(pwmout_t* obj, int ms) {
    pwmout_pulsewidth_us(obj, ms * 1000);
}

void pwmout_pulsewidth_us(pwmout_t* obj, int us) {
    *obj->CnV = (uint32_t)(pwm_clock * (float)us);
    *obj->SYNC |= FTM_SYNC_SWSYNC_MASK;
}
