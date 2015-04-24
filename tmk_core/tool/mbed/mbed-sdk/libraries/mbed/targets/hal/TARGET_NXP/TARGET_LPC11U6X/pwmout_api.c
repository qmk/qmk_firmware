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

#include "pwmout_api.h"
#include "cmsis.h"
#include "pinmap.h"
#include "mbed_error.h"

#if DEVICE_PWMOUT

#define SCT_CHANNELS 2

static const PinMap PinMap_PWM[] = {
    {P1_19, SCT0_0, 2},
    {P2_2 , SCT0_1, 3},
    {P2_7 , SCT0_2, 2},
    {P1_13, SCT0_3, 2},
    {P2_16, SCT1_0, 1},
    {P2_17, SCT1_1, 1},
    {P2_18, SCT1_2, 1},
    {P2_19, SCT1_3, 1},
    {NC   , NC    ,0}
};


static LPC_SCT0_Type *SCTs[SCT_CHANNELS] = {
    (LPC_SCT0_Type*)LPC_SCT0,
    (LPC_SCT0_Type*)LPC_SCT1,

};

// bit flags for used SCTs
static unsigned char sct_used = 0;

static int get_available_sct(void) {
    int i;
    for (i=0; i<SCT_CHANNELS; i++) {
        if ((sct_used & (1 << i)) == 0)
            return i;
    }
    return -1;
}

void pwmout_init(pwmout_t* obj, PinName pin) {
    // determine the SPI to use
    PWMName pwm_mapped = (PWMName)pinmap_peripheral(pin, PinMap_PWM);
    if (pwm_mapped == (PWMName)NC) {
        error("PwmOut pin mapping failed");
    }
    int sct_n = get_available_sct();
    if (sct_n == -1) {
        error("No available SCT");
    }

    sct_used |= (1 << sct_n);
    obj->pwm =  SCTs[sct_n];
    obj->pwm_ch = sct_n;

    // Enable the SCT clock
    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 31);

    // Clear peripheral reset the SCT:
    LPC_SYSCON->PRESETCTRL |=  (1 << (obj->pwm_ch + 9));
    pinmap_pinout(pin, PinMap_PWM);
    LPC_SCT0_Type* pwm = obj->pwm;
    
    // Unified 32-bit counter, autolimit
    pwm->CONFIG |= ((0x3 << 17) | 0x01);
    
    // halt and clear the counter
    pwm->CTRL |= (1 << 2) | (1 << 3);
    
    // System Clock -> us_ticker (1)MHz
    pwm->CTRL &= ~(0x7F << 5);
    pwm->CTRL |= (((SystemCoreClock/1000000 - 1) & 0x7F) << 5);
    
    switch(pwm_mapped) {
        case SCT0_0:
        case SCT1_0:
            pwm->OUT0_SET = (1 << 0); // event 0
            pwm->OUT0_CLR = (1 << 1); // event 1
            break;
        case SCT0_1:
        case SCT1_1:
            pwm->OUT1_SET = (1 << 0); // event 0
            pwm->OUT1_CLR = (1 << 1); // event 1
            break;
        case SCT0_2:
        case SCT1_2:
            pwm->OUT2_SET = (1 << 0); // event 0
            pwm->OUT2_CLR = (1 << 1); // event 1
            break;
        case SCT0_3:
        case SCT1_3:
            pwm->OUT3_SET = (1 << 0); // event 0
            pwm->OUT3_CLR = (1 << 1); // event 1
            break;
        default:
            break;
    }
    // Event 0 : MATCH and MATCHSEL=0
    pwm->EV0_CTRL  = (1 << 12);
    pwm->EV0_STATE = 0xFFFFFFFF;
    // Event 1 : MATCH and MATCHSEL=1
    pwm->EV1_CTRL  = (1 << 12) | (1 << 0);
    pwm->EV1_STATE = 0xFFFFFFFF;
    
    // Match reload register
    pwm->MATCHREL0 = 20000; // 20ms
    pwm->MATCHREL1 = (pwm->MATCHREL0 / 4); // 50% duty
    
    // unhalt the counter:
    //    - clearing bit 2 of the CTRL register
    pwm->CTRL &= ~(1 << 2);

    // default to 20ms: standard for servos, and fine for e.g. brightness control
    pwmout_period_ms(obj, 20);
    pwmout_write    (obj, 0);
}

void pwmout_free(pwmout_t* obj) {
    sct_used &= ~(1 << obj->pwm_ch);
    if (sct_used == 0) {
        // Disable the SCT clock
        LPC_SYSCON->SYSAHBCLKCTRL &= ~(1UL << 31);
    }
}

void pwmout_write(pwmout_t* obj, float value) {
    if (value < 0.0f) {
        value = 0.0;
    } else if (value > 1.0f) {
        value = 1.0;
    }
    uint32_t t_on = (uint32_t)((float)(obj->pwm->MATCHREL0) * value);
    obj->pwm->MATCHREL1 = t_on;
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
    uint32_t t_off = obj->pwm->MATCHREL0;
    uint32_t t_on  = obj->pwm->MATCHREL1;
    float v = (float)t_on/(float)t_off;
    obj->pwm->MATCHREL0 = (uint32_t)us;
    obj->pwm->MATCHREL1 = (uint32_t)((float)us * (float)v);
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

#endif
