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
#include "PeripheralPins.h" // For the Peripheral to Pin Definitions found in the individual Target's Platform

#define TCR_CNT_EN       0x00000001
#define TCR_RESET        0x00000002

typedef struct {
    uint8_t timer;
    uint8_t mr;
} timer_mr;

static timer_mr pwm_timer_map[11] = {
    {0, 0}, {0, 1}, {0, 2},
    {1, 0}, {1, 1},
    {2, 0}, {2, 1}, {2, 2},
    {3, 0}, {3, 1}, {3, 2},
};

static LPC_CTxxBx_Type *Timers[4] = {
    LPC_CT16B0, LPC_CT16B1,
    LPC_CT32B0, LPC_CT32B1
};

void pwmout_init(pwmout_t* obj, PinName pin) {
    // determine the channel
    PWMName pwm = (PWMName)pinmap_peripheral(pin, PinMap_PWM);
    MBED_ASSERT(pwm != (PWMName)NC);

    obj->pwm = pwm;
    
    // Timer registers
    timer_mr tid = pwm_timer_map[pwm];
    LPC_CTxxBx_Type *timer = Timers[tid.timer];
    
    // Disable timer
    timer->TCR = 0;
    
    // Power the correspondent timer
    LPC_SYSCON->SYSAHBCLKCTRL |= 1 << (tid.timer + 7);
    
    /* Enable PWM function */
    timer->PWMC = (1 << 3)|(1 << 2)|(1 << 1)|(1 << 0);
    
    /* Reset Functionality on MR3 controlling the PWM period */
    timer->MCR = 1 << 10;
    
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
    
    timer_mr tid = pwm_timer_map[obj->pwm];
    LPC_CTxxBx_Type *timer = Timers[tid.timer];
    uint32_t t_off = timer->MR3 - (uint32_t)((float)(timer->MR3) * value);
    
    timer->MR[tid.mr] = t_off;
}

float pwmout_read(pwmout_t* obj) {
    timer_mr tid = pwm_timer_map[obj->pwm];
    LPC_CTxxBx_Type *timer = Timers[tid.timer];
    
    float v = (float)(timer->MR3 - timer->MR[tid.mr]) / (float)(timer->MR3);
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
    int i = 0;
    uint32_t period_ticks = (uint32_t)(((uint64_t)SystemCoreClock * (uint64_t)us) / (uint64_t)1000000);
    
    timer_mr tid = pwm_timer_map[obj->pwm];
    LPC_CTxxBx_Type *timer = Timers[tid.timer];
    uint32_t old_period_ticks = timer->MR3;

    // for 16bit timer, set prescaler to avoid overflow
    if (timer == LPC_CT16B0 || timer == LPC_CT16B1) {
        uint16_t high_period_ticks = period_ticks >> 16;
        timer->PR = high_period_ticks;
        period_ticks /= (high_period_ticks + 1);
    }
    
    timer->TCR = TCR_RESET;
    timer->MR3 = period_ticks;
    
    // Scale the pulse width to preserve the duty ratio
    if (old_period_ticks > 0) {
        for (i=0; i<3; i++) {
            uint32_t t_off = period_ticks - (uint32_t)(((uint64_t)timer->MR[i] * (uint64_t)period_ticks) / (uint64_t)old_period_ticks);
            timer->MR[i] = t_off;
        }
    }
    timer->TCR = TCR_CNT_EN;
}

void pwmout_pulsewidth(pwmout_t* obj, float seconds) {
    pwmout_pulsewidth_us(obj, seconds * 1000000.0f);
}

void pwmout_pulsewidth_ms(pwmout_t* obj, int ms) {
    pwmout_pulsewidth_us(obj, ms * 1000);
}

void pwmout_pulsewidth_us(pwmout_t* obj, int us) {
    timer_mr tid = pwm_timer_map[obj->pwm];
    LPC_CTxxBx_Type *timer = Timers[tid.timer];
    uint32_t t_on = (uint32_t)(((uint64_t)SystemCoreClock * (uint64_t)us) / (uint64_t)1000000 / (timer->PR + 1));
    
    timer->TCR = TCR_RESET;
    if (t_on > timer->MR3) {
        pwmout_period_us(obj, us);
        t_on = (uint32_t)(((uint64_t)SystemCoreClock * (uint64_t)us) / (uint64_t)1000000 / (timer->PR + 1));
    }
    uint32_t t_off = timer->MR3 - t_on;
    timer->MR[tid.mr] = t_off;
    timer->TCR = TCR_CNT_EN;
}
