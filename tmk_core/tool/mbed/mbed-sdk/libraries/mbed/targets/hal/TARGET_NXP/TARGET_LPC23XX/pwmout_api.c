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

#define TCR_CNT_EN       0x00000001
#define TCR_RESET        0x00000002

//  PORT ID, PWM ID, Pin function
static const PinMap PinMap_PWM[] = {
    {P1_18, PWM_1, 2},
    {P1_20, PWM_2, 2},
    {P1_21, PWM_3, 2},
    {P1_23, PWM_4, 2},
    {P1_24, PWM_5, 2},
    {P1_26, PWM_6, 2},
    {P2_0 , PWM_1, 1},
    {P2_1 , PWM_2, 1},
    {P2_2 , PWM_3, 1},
    {P2_3 , PWM_4, 1},
    {P2_4 , PWM_5, 1},
    {P2_5 , PWM_6, 1},
    {P3_25, PWM_2, 3},
    {P3_26, PWM_3, 3},
    {NC, NC, 0}
};

__IO uint32_t *PWM_MATCH[] = {
    &(LPC_PWM1->MR0),
    &(LPC_PWM1->MR1),
    &(LPC_PWM1->MR2),
    &(LPC_PWM1->MR3),
    &(LPC_PWM1->MR4),
    &(LPC_PWM1->MR5),
    &(LPC_PWM1->MR6)
};

#define TCR_PWM_EN       0x00000008

static unsigned int pwm_clock_mhz;

void pwmout_init(pwmout_t* obj, PinName pin) {
    // determine the channel
    PWMName pwm = (PWMName)pinmap_peripheral(pin, PinMap_PWM);
    MBED_ASSERT(pwm != (PWMName)NC);

    obj->pwm = pwm;
    obj->MR = PWM_MATCH[pwm];
    
    // ensure the power is on
    LPC_SC->PCONP |= 1 << 6;
    
    // ensure clock to /4
    LPC_SC->PCLKSEL0 &= ~(0x3 << 12);     // pclk = /4
    LPC_PWM1->PR = 0;                     // no pre-scale
    
    // ensure single PWM mode
    LPC_PWM1->MCR = 1 << 1; // reset TC on match 0
    
    // enable the specific PWM output
    LPC_PWM1->PCR |= 1 << (8 + pwm);
    
    pwm_clock_mhz = SystemCoreClock / 4000000;
    
    // default to 20ms: standard for servos, and fine for e.g. brightness control
    pwmout_period_ms(obj, 20);
    pwmout_write    (obj, 0);
    
    // Wire pinout
    pinmap_pinout(pin, PinMap_PWM);
}

void pwmout_free(pwmout_t* obj) {
    // [TODO]
}

void pwmout_write(pwmout_t* obj, float value) {
    if (value < 0.0f) {
        value = 0.0;
    } else if (value > 1.0f) {
        value = 1.0;
    }
    
    // set channel match to percentage
    uint32_t v = (uint32_t)((float)(LPC_PWM1->MR0) * value);
    
    // workaround for PWM1[1] - Never make it equal MR0, else we get 1 cycle dropout
    if (v == LPC_PWM1->MR0) {
        v++;
    }
    
    *obj->MR = v;
    
    // accept on next period start
    LPC_PWM1->LER |= 1 << obj->pwm;
}

float pwmout_read(pwmout_t* obj) {
    float v = (float)(*obj->MR) / (float)(LPC_PWM1->MR0);
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
    // calculate number of ticks
    uint32_t ticks = pwm_clock_mhz * us;
    
    // set reset
    LPC_PWM1->TCR = TCR_RESET;
    
    // set the global match register
    LPC_PWM1->MR0 = ticks;
    
    // Scale the pulse width to preserve the duty ratio
    if (LPC_PWM1->MR0 > 0) {
        *obj->MR = (*obj->MR * ticks) / LPC_PWM1->MR0;
    }
    
    // set the channel latch to update value at next period start
    LPC_PWM1->LER |= 1 << 0;
    
    // enable counter and pwm, clear reset
    LPC_PWM1->TCR = TCR_CNT_EN | TCR_PWM_EN;
}

void pwmout_pulsewidth(pwmout_t* obj, float seconds) {
    pwmout_pulsewidth_us(obj, seconds * 1000000.0f);
}

void pwmout_pulsewidth_ms(pwmout_t* obj, int ms) {
    pwmout_pulsewidth_us(obj, ms * 1000);
}

void pwmout_pulsewidth_us(pwmout_t* obj, int us) {
    // calculate number of ticks
    uint32_t v = pwm_clock_mhz * us;
    
    // workaround for PWM1[1] - Never make it equal MR0, else we get 1 cycle dropout
    if (v == LPC_PWM1->MR0) {
        v++;
    }
    
    // set the match register value
    *obj->MR = v;
    
    // set the channel latch to update value at next period start
    LPC_PWM1->LER |= 1 << obj->pwm;
}
