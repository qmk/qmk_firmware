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
#include "RZ_A1_Init.h"
#include "cpg_iodefine.h"
#include "pwm_iodefine.h"

//  PORT ID, PWM ID, Pin function
static const PinMap PinMap_PWM[] = {
    {P4_4     , PWM0_PIN , 4},
    {P3_2     , PWM1_PIN , 7},
    {P4_6     , PWM2_PIN , 4},
    {P4_7     , PWM3_PIN , 4},
    {P8_14    , PWM4_PIN , 6},
    {P8_15    , PWM5_PIN , 6},
    {P8_13    , PWM6_PIN , 6},
    {P8_11    , PWM7_PIN , 6},
    {P8_8     , PWM8_PIN , 6},
    {P10_0    , PWM9_PIN , 3},
    {P8_12    , PWM10_PIN, 6},
    {P8_9     , PWM11_PIN, 6},
    {P8_10    , PWM12_PIN, 6},
    {P4_5     , PWM13_PIN, 4},
    {NC, NC, 0}
};

static PWMType PORT[] = {
     PWM2E,          // PWM0_PIN
     PWM2C,          // PWM1_PIN
     PWM2G,          // PWM2_PIN
     PWM2H,          // PWM3_PIN
     PWM1G,          // PWM4_PIN
     PWM1H,          // PWM5_PIN
     PWM1F,          // PWM6_PIN
     PWM1D,          // PWM7_PIN
     PWM1A,          // PWM8_PIN
     PWM2A,          // PWM9_PIN
     PWM1E,          // PWM10_PIN
     PWM1B,          // PWM11_PIN
     PWM1C,          // PWM12_PIN
     PWM2F,          // PWM13_PIN
};

static __IO uint16_t *PWM_MATCH[] = {
    &PWMPWBFR_2E,    // PWM0_PIN
    &PWMPWBFR_2C,    // PWM1_PIN
    &PWMPWBFR_2G,    // PWM2_PIN
    &PWMPWBFR_2G,    // PWM3_PIN
    &PWMPWBFR_1G,    // PWM4_PIN
    &PWMPWBFR_1G,    // PWM5_PIN
    &PWMPWBFR_1E,    // PWM6_PIN
    &PWMPWBFR_1C,    // PWM7_PIN
    &PWMPWBFR_1A,    // PWM8_PIN
    &PWMPWBFR_2A,    // PWM9_PIN
    &PWMPWBFR_1E,    // PWM10_PIN
    &PWMPWBFR_1A,    // PWM11_PIN
    &PWMPWBFR_1C,    // PWM12_PIN
    &PWMPWBFR_2E,    // PWM13_PIN
};

static uint16_t init_period_ch1 = 0;
static uint16_t init_period_ch2 = 0;
static int32_t  period_ch1 = 1;
static int32_t  period_ch2 = 1;

void pwmout_init(pwmout_t* obj, PinName pin) {
    // determine the channel
    PWMName pwm = (PWMName)pinmap_peripheral(pin, PinMap_PWM);
    MBED_ASSERT(pwm != (PWMName)NC);

    // power on
    CPGSTBCR3 &= ~(1<<0);

    obj->pwm = pwm;
    if (((uint32_t)PORT[obj->pwm] & 0x00000010) != 0) {
        obj->ch  = 2;
        PWMPWPR_2_BYTE_L = 0x00;
    } else {
        obj->ch  = 1;
        PWMPWPR_1_BYTE_L = 0x00;
    }

    // Wire pinout
    pinmap_pinout(pin, PinMap_PWM);

    // default to 491us: standard for servos, and fine for e.g. brightness control
    pwmout_write(obj, 0);
    if ((obj->ch == 2) && (init_period_ch2 == 0)) {
        pwmout_period_us(obj, 491);
        init_period_ch2 = 1;
    }
    if ((obj->ch == 1) && (init_period_ch1 == 0)) {
        pwmout_period_us(obj, 491);
        init_period_ch1 = 1;
    }
}

void pwmout_free(pwmout_t* obj) {
    pwmout_write(obj, 0);
}

void pwmout_write(pwmout_t* obj, float value) {
    uint32_t wk_cycle;
    uint16_t v;

    if (value < 0.0f) {
        value = 0.0f;
    } else if (value > 1.0f) {
        value = 1.0f;
    } else {
        // Do Nothing
    }

    if (obj->ch == 2) {
        wk_cycle = PWMPWCYR_2 & 0x03ff;
    } else {
        wk_cycle = PWMPWCYR_1 & 0x03ff;
    }

    // set channel match to percentage
    v = (uint16_t)((float)wk_cycle * value);
    *PWM_MATCH[obj->pwm] = (v | ((PORT[obj->pwm] & 1) << 12));
}

float pwmout_read(pwmout_t* obj) {
    uint32_t wk_cycle;
    float value;

    if (obj->ch == 2) {
        wk_cycle = PWMPWCYR_2 & 0x03ff;
    } else {
        wk_cycle = PWMPWCYR_1 & 0x03ff;
    }
    value = ((float)(*PWM_MATCH[obj->pwm] & 0x03ff) / (float)wk_cycle);

    return (value > 1.0f) ? (1.0f) : (value);
}

void pwmout_period(pwmout_t* obj, float seconds) {
    pwmout_period_us(obj, seconds * 1000000.0f);
}

void pwmout_period_ms(pwmout_t* obj, int ms) {
    pwmout_period_us(obj, ms * 1000);
}

static void set_duty_again(__IO uint16_t *p_pwmpbfr, uint16_t last_cycle, uint16_t new_cycle){
    uint16_t wk_pwmpbfr;
    float    value;
    uint16_t v;

    wk_pwmpbfr = *p_pwmpbfr;
    value      = ((float)(wk_pwmpbfr & 0x03ff) / (float)last_cycle);
    v          = (uint16_t)((float)new_cycle * value);
    *p_pwmpbfr = (v | (wk_pwmpbfr & 0x1000));
}

// Set the PWM period, keeping the duty cycle the same.
void pwmout_period_us(pwmout_t* obj, int us) {
    uint32_t pclk_base;
    uint32_t wk_cycle;
    uint16_t wk_last_cycle;
    uint32_t wk_cks = 0;

    if (us > 491) {
        us = 491;
    } else if (us < 1) {
        us = 1;
    } else {
        // Do Nothing
    }

    if (RZ_A1_IsClockMode0() == false) {
        pclk_base = (uint32_t)CM1_RENESAS_RZ_A1_P0_CLK / 10000;
    } else {
        pclk_base = (uint32_t)CM0_RENESAS_RZ_A1_P0_CLK / 10000;
    }

    wk_cycle = pclk_base * us;
    while (wk_cycle >= 102350) {
        wk_cycle >>= 1;
        wk_cks++;
    }
    wk_cycle = (wk_cycle + 50) / 100;

    if (obj->ch == 2) {
        wk_last_cycle    = PWMPWCYR_2 & 0x03ff;
        PWMPWCR_2_BYTE_L = 0xc0 | wk_cks;
        PWMPWCYR_2       = (uint16_t)wk_cycle;

        // Set duty again
        set_duty_again(&PWMPWBFR_2A, wk_last_cycle, wk_cycle);
        set_duty_again(&PWMPWBFR_2C, wk_last_cycle, wk_cycle);
        set_duty_again(&PWMPWBFR_2E, wk_last_cycle, wk_cycle);
        set_duty_again(&PWMPWBFR_2G, wk_last_cycle, wk_cycle);

        // Counter Start
        PWMPWCR_2_BYTE_L |= 0x08;

        // Save for future use
        period_ch2 = us;
    } else {
        wk_last_cycle    = PWMPWCYR_1 & 0x03ff;
        PWMPWCR_1_BYTE_L = 0xc0 | wk_cks;
        PWMPWCYR_1       = (uint16_t)wk_cycle;

        // Set duty again
        set_duty_again(&PWMPWBFR_1A, wk_last_cycle, wk_cycle);
        set_duty_again(&PWMPWBFR_1C, wk_last_cycle, wk_cycle);
        set_duty_again(&PWMPWBFR_1E, wk_last_cycle, wk_cycle);
        set_duty_again(&PWMPWBFR_1G, wk_last_cycle, wk_cycle);

        // Counter Start
        PWMPWCR_1_BYTE_L |= 0x08;

        // Save for future use
        period_ch1 = us;
    }
}

void pwmout_pulsewidth(pwmout_t* obj, float seconds) {
    pwmout_pulsewidth_us(obj, seconds * 1000000.0f);
}

void pwmout_pulsewidth_ms(pwmout_t* obj, int ms) {
    pwmout_pulsewidth_us(obj, ms * 1000);
}

void pwmout_pulsewidth_us(pwmout_t* obj, int us) {
    float value = 0;

    if (obj->ch == 2) {
        if (period_ch2 != 0) {
            value = (float)us / (float)period_ch2;
        }
    } else {
        if (period_ch1 != 0) {
            value = (float)us / (float)period_ch1;
        }
    }

    pwmout_write(obj, value);
}
