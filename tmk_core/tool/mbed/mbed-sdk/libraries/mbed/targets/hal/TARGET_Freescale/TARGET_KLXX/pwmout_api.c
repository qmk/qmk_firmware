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

#include "cmsis.h"
#include "pinmap.h"
#include "clk_freqs.h"
#include "PeripheralPins.h"

static float pwm_clock;

void pwmout_init(pwmout_t* obj, PinName pin) {
    // determine the channel
    PWMName pwm = (PWMName)pinmap_peripheral(pin, PinMap_PWM);
    MBED_ASSERT(pwm != (PWMName)NC);

    uint32_t clkdiv = 0;
    float clkval;

#if defined(TARGET_KL43Z)
    if (mcgirc_frequency()) {
        SIM->SOPT2 |= SIM_SOPT2_TPMSRC(3); // Clock source: MCGIRCLK
        clkval = mcgirc_frequency() / 1000000.0f;
    } else {
        SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1); // Clock source: IRC48M
        clkval = CPU_INT_IRC_CLK_HZ / 1000000.0f;
    }
#else
    if (mcgpllfll_frequency()) {
        SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1); // Clock source: MCGFLLCLK or MCGPLLCLK
        clkval = mcgpllfll_frequency() / 1000000.0f;
    } else {
        SIM->SOPT2 |= SIM_SOPT2_TPMSRC(2); // Clock source: ExtOsc
        clkval = extosc_frequency() / 1000000.0f;
    }
#endif
    while (clkval > 1) {
        clkdiv++;
        clkval /= 2.0;
        if (clkdiv == 7)
            break;
    }
    
    pwm_clock = clkval;
    unsigned int port  = (unsigned int)pin >> PORT_SHIFT;
    unsigned int tpm_n = (pwm >> TPM_SHIFT);
    unsigned int ch_n  = (pwm & 0xFF);

    SIM->SCGC5 |= 1 << (SIM_SCGC5_PORTA_SHIFT + port);
    SIM->SCGC6 |= 1 << (SIM_SCGC6_TPM0_SHIFT + tpm_n);

    TPM_Type *tpm = (TPM_Type *)(TPM0_BASE + 0x1000 * tpm_n);
    tpm->SC = TPM_SC_CMOD(1) | TPM_SC_PS(clkdiv); // (clock)MHz / clkdiv ~= (0.75)MHz
    tpm->CONTROLS[ch_n].CnSC = (TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK); /* No Interrupts; High True pulses on Edge Aligned PWM */

    obj->CnV = &tpm->CONTROLS[ch_n].CnV;
    obj->MOD = &tpm->MOD;
    obj->CNT = &tpm->CNT;

    // default to 20ms: standard for servos, and fine for e.g. brightness control
    pwmout_period_ms(obj, 20);
    pwmout_write    (obj, 0);

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

    *obj->CnV = (uint32_t)((float)(*obj->MOD + 1) * value);
    *obj->CNT = 0;
}

float pwmout_read(pwmout_t* obj) {
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
}
