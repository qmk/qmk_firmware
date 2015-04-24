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
    {P1_2,  PWM0_1, 3},
    {P1_3,  PWM0_2, 3},
    {P1_5,  PWM0_3, 3},
    {P1_6,  PWM0_4, 3},
    {P1_7,  PWM0_5, 3},
    {P1_11, PWM0_6, 3},
    {P1_18, PWM1_1, 2},
    {P1_20, PWM1_2, 2},
    {P1_21, PWM1_3, 2},
    {P1_23, PWM1_4, 2},
    {P1_24, PWM1_5, 2},
    {P1_26, PWM1_6, 2},
    {P2_0,  PWM1_1, 1},
    {P2_1,  PWM1_2, 1},
    {P2_2,  PWM1_3, 1},
    {P2_3,  PWM1_4, 1},
    {P2_4,  PWM1_5, 1},
    {P2_5,  PWM1_6, 1},
    {P3_16, PWM0_1, 2},
    {P3_17, PWM0_2, 2},
    {P3_18, PWM0_3, 2},
    {P3_19, PWM0_4, 2},
    {P3_20, PWM0_5, 2},
    {P3_21, PWM0_6, 2},
    {P3_24, PWM1_1, 2},
    {P3_25, PWM1_2, 2},
    {P3_26, PWM1_3, 2},
    {P3_27, PWM1_4, 2},
    {P3_28, PWM1_5, 2},
    {P3_29, PWM1_6, 2},
    {NC, NC, 0}
};

static const uint32_t PWM_mr_offset[7] = {
    0x18, 0x1C, 0x20, 0x24, 0x40, 0x44, 0x48
};

#define TCR_PWM_EN       0x00000008
static unsigned int pwm_clock_mhz;

void pwmout_init(pwmout_t* obj, PinName pin) {
    // determine the channel
    PWMName pwm = (PWMName)pinmap_peripheral(pin, PinMap_PWM);
    MBED_ASSERT(pwm != (PWMName)NC);

    obj->channel = pwm;
    obj->pwm = LPC_PWM0;
    
    if (obj->channel > 6) { // PWM1 is used if pwm > 6
      obj->channel -= 6;
      obj->pwm = LPC_PWM1;
    }
    
    obj->MR = (__IO uint32_t *)((uint32_t)obj->pwm + PWM_mr_offset[obj->channel]);
    
    // ensure the power is on
    if (obj->pwm == LPC_PWM0) {
        LPC_SC->PCONP |= 1 << 5;
    } else {
        LPC_SC->PCONP |= 1 << 6;
    }
    
    obj->pwm->PR = 0;                     // no pre-scale
    
    // ensure single PWM mode
    obj->pwm->MCR = 1 << 1; // reset TC on match 0
    
    // enable the specific PWM output
    obj->pwm->PCR |= 1 << (8 + obj->channel);
    
    pwm_clock_mhz = PeripheralClock / 1000000;
    
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
    uint32_t v = (uint32_t)((float)(obj->pwm->MR0) * value);
    
    // workaround for PWM1[1] - Never make it equal MR0, else we get 1 cycle dropout
    if (v == obj->pwm->MR0) {
        v++;
    }
    
    *obj->MR = v;
    
    // accept on next period start
    obj->pwm->LER |= 1 << obj->channel;
}

float pwmout_read(pwmout_t* obj) {
    float v = (float)(*obj->MR) / (float)(obj->pwm->MR0);
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
    obj->pwm->TCR = TCR_RESET;
    
    // set the global match register
    obj->pwm->MR0 = ticks;
    
    // Scale the pulse width to preserve the duty ratio
    if (obj->pwm->MR0 > 0) {
        *obj->MR = (*obj->MR * ticks) / obj->pwm->MR0;
    }
    
    // set the channel latch to update value at next period start
    obj->pwm->LER |= 1 << 0;
    
    // enable counter and pwm, clear reset
    obj->pwm->TCR = TCR_CNT_EN | TCR_PWM_EN;
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
    if (v == obj->pwm->MR0) {
        v++;
    }
    
    // set the match register value
    *obj->MR = v;
    
    // set the channel latch to update value at next period start
    obj->pwm->LER |= 1 << obj->channel;
}
