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
#include "mbed_error.h"

static LPC_SCT0_Type *SCTs[4] = {
    (LPC_SCT0_Type*)LPC_SCT0,
    (LPC_SCT0_Type*)LPC_SCT1,
    (LPC_SCT0_Type*)LPC_SCT2,
    (LPC_SCT0_Type*)LPC_SCT3,
};

// bit flags for used SCTs
static unsigned char sct_used = 0;
static int get_available_sct(void) {
    int i;
    for (i=0; i<4; i++) {
        if ((sct_used & (1 << i)) == 0)
            return i;
    }
    return -1;
}

void pwmout_init(pwmout_t* obj, PinName pin) {
    MBED_ASSERT(pin != (uint32_t)NC);

    int sct_n = get_available_sct();
    if (sct_n == -1) {
        error("No available SCT");
    }
    
    sct_used |= (1 << sct_n);
    obj->pwm =  SCTs[sct_n];
    obj->pwm_ch = sct_n;

    LPC_SCT0_Type* pwm = obj->pwm;

    // Enable the SCT clock
    LPC_SYSCON->SYSAHBCLKCTRL1 |= (1 << (obj->pwm_ch + 2));

    // Clear peripheral reset the SCT:
    LPC_SYSCON->PRESETCTRL1 |=  (1 << (obj->pwm_ch + 2));
    LPC_SYSCON->PRESETCTRL1 &= ~(1 << (obj->pwm_ch + 2));
    
    switch(obj->pwm_ch) {
        case 0:
            // SCT0_OUT0
            LPC_SWM->PINASSIGN[7] &= ~0x0000FF00;
            LPC_SWM->PINASSIGN[7] |= (pin << 8);
            break;
        case 1:
            // SCT1_OUT0
            LPC_SWM->PINASSIGN[8] &= ~0x000000FF;
            LPC_SWM->PINASSIGN[8] |= (pin);
            break;
        case 2:
            // SCT2_OUT0
            LPC_SWM->PINASSIGN[8] &= ~0xFF000000;
            LPC_SWM->PINASSIGN[8] |= (pin << 24);
            break;
        case 3:
            // SCT3_OUT0
            LPC_SWM->PINASSIGN[9] &= ~0x00FF0000;
            LPC_SWM->PINASSIGN[9] |= (pin << 16);
            break;
        default:
            break;
    }
    
    // Unified 32-bit counter, autolimit
    pwm->CONFIG |= ((0x3 << 17) | 0x01);
    
    // halt and clear the counter
    pwm->CTRL |= (1 << 2) | (1 << 3);
    
    // System Clock -> us_ticker (1)MHz
    pwm->CTRL &= ~(0x7F << 5);
    pwm->CTRL |= (((SystemCoreClock/1000000 - 1) & 0x7F) << 5);
    
    // Match reload register
    pwm->MATCHREL0 = 20000; // 20ms
    pwm->MATCHREL1 = (pwm->MATCHREL0 / 4); // 50% duty
    
    pwm->OUT0_SET = (1 << 0); // event 0
    pwm->OUT0_CLR = (1 << 1); // event 1

    pwm->EV0_CTRL  = (1 << 12);
    pwm->EV0_STATE = 0xFFFFFFFF;
    pwm->EV1_CTRL  = (1 << 12) | (1 << 0);
    pwm->EV1_STATE = 0xFFFFFFFF;

    // unhalt the counter:
    //    - clearing bit 2 of the CTRL register
    pwm->CTRL &= ~(1 << 2);

    // default to 20ms: standard for servos, and fine for e.g. brightness control
    pwmout_period_ms(obj, 20);
    pwmout_write    (obj, 0);
}

void pwmout_free(pwmout_t* obj) {
    // Disable the SCT clock
    LPC_SYSCON->SYSAHBCLKCTRL1 &= ~(1 << (obj->pwm_ch + 2));
    sct_used &= ~(1 << obj->pwm_ch);
}

void pwmout_write(pwmout_t* obj, float value) {
    LPC_SCT0_Type* pwm = obj->pwm;
    if (value < 0.0f) {
        value = 0.0;
    } else if (value > 1.0f) {
        value = 1.0;
    }
    uint32_t t_on = (uint32_t)((float)(pwm->MATCHREL0) * value);
    pwm->MATCHREL1 = t_on;
}

float pwmout_read(pwmout_t* obj) {
    uint32_t t_off = obj->pwm->MATCHREL0;
    uint32_t t_on  = obj->pwm->MATCHREL1;
    float v = (float)t_on/(float)t_off;
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
    LPC_SCT0_Type* pwm = obj->pwm;
    uint32_t t_off = pwm->MATCHREL0;
    uint32_t t_on  = pwm->MATCHREL1;
    float v = (float)t_on/(float)t_off;
    pwm->MATCHREL0 = (uint32_t)us;
    pwm->MATCHREL1 = (uint32_t)((float)us * (float)v);
}

void pwmout_pulsewidth(pwmout_t* obj, float seconds) {
    pwmout_pulsewidth_us(obj, seconds * 1000000.0f);
}

void pwmout_pulsewidth_ms(pwmout_t* obj, int ms) {
    pwmout_pulsewidth_us(obj, ms * 1000);
}

void pwmout_pulsewidth_us(pwmout_t* obj, int us) {
    obj->pwm->MATCHREL1 = (uint32_t)us;
}

