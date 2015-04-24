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
 *
 * Ported to NXP LPC43XX by Micromint USA <support@micromint.com>
 */
#include "mbed_assert.h"
#include "pwmout_api.h"
#include "cmsis.h"
#include "pinmap.h"
#include "mbed_error.h"

// PWM implementation for the LPC43xx using State Configurable Timer (SCT)
//   * PWM_0 to PWM_15 on mbed use CTOUT_0 to CTOUT_15 outputs on LPC43xx
//   * Event 0 is PWM period, events 1 to PWM_EVENT_MAX are PWM channels
//   * Default is unified 32-bit timer, but could be configured to use
//     a 16-bit timer so a timer is available for other SCT functions

// configuration options
#define PWM_FREQ_BASE   1000000                 // Base frequency 1 MHz = 1000000
#define PWM_MODE        1                       // 0 = 32-bit, 1 = 16-bit low, 2 = 16-bit high

// macros
#define PWM_SETCOUNT(x) (x - 1)                 // set count value
#define PWM_GETCOUNT(x) (x + 1)                 // get count value
#if (PWM_MODE == 0) // unified 32-bit counter, events 1 to 15
  #define PWM_EVENT_MAX (CONFIG_SCT_nEV - 1)    // Max PWM channels
  #define PWM_CONFIG    SCT_CONFIG_32BIT_COUNTER // default config
  #define PWM_CTRL      &LPC_SCT->CTRL_U        // control register
  #define PWM_HALT      SCT_CTRL_HALT_L         // halt counter
  #define PWM_CLEAR     SCT_CTRL_CLRCTR_L       // clock clear
  #define PWM_PRE(x)    SCT_CTRL_PRE_L(x)       // clock prescale
  #define PWM_EVT_MASK  (1 << 12)               // event control mask
  #define PWM_LIMIT     &LPC_SCT->LIMIT_L       // limit register
  #define PWM_MATCH(x)  &LPC_SCT->MATCH[x].U    // match register
  #define PWM_MR(x)     &LPC_SCT->MATCHREL[x].U // 32-bit match reload register
#elif (PWM_MODE == 1) // 16-bit low counter, events 1 to 7
  #define PWM_EVENT_MAX (CONFIG_SCT_nEV/2 - 1)  // Max PWM channels
  #define PWM_CONFIG    SCT_CONFIG_16BIT_COUNTER // default config
  #define PWM_CTRL      &LPC_SCT->CTRL_L        // control register
  #define PWM_HALT      SCT_CTRL_HALT_L         // halt counter
  #define PWM_CLEAR     SCT_CTRL_CLRCTR_L       // clock clear
  #define PWM_PRE(x)    SCT_CTRL_PRE_L(x)       // clock prescale
  #define PWM_EVT_MASK  (1 << 12)               // event control mask
  #define PWM_LIMIT     &LPC_SCT->LIMIT_L       // limit register
  #define PWM_MATCH(x)  &LPC_SCT->MATCH[x].L    // match register
  #define PWM_MR(x)     &LPC_SCT->MATCHREL[x].L // 16-bit match reload register
#elif (PWM_MODE == 2) // 16-bit high counter, events 1 to 7
  // [TODO] use events 8 to 15 on mode 2
  #define PWM_EVENT_MAX (CONFIG_SCT_nEV/2 - 1)  // Max PWM channels
  #define PWM_CONFIG    SCT_CONFIG_16BIT_COUNTER // default config
  #define PWM_CTRL      &LPC_SCT->CTRL_H        // control register
  #define PWM_HALT      SCT_CTRL_HALT_L         // halt counter
  #define PWM_CLEAR     SCT_CTRL_CLRCTR_L       // clock clear
  #define PWM_PRE(x)    SCT_CTRL_PRE_L(x)       // clock prescale
  #define PWM_EVT_MASK  ((1 << 4) | (1 << 12))  // event control mask
  #define PWM_LIMIT     &LPC_SCT->LIMIT_H       // limit register
  #define PWM_MATCH(x)  &LPC_SCT->MATCH[x].H    // match register
  #define PWM_MR(x)     &LPC_SCT->MATCHREL[x].H // 16-bit match reload register
#else
  #error "PWM mode not implemented"
#endif
#define PWM_MR0         PWM_MR(0)               // MR register 0 is for period

static uint8_t event = 0;

//  PORT ID, PWM ID, Pin function
static const PinMap PinMap_PWM[] = {
    {P1_1,  PWM_7,  (SCU_PINIO_FAST | 1)},
    {P1_2,  PWM_6,  (SCU_PINIO_FAST | 1)},
    {P1_3,  PWM_8,  (SCU_PINIO_FAST | 1)},
    {P1_4,  PWM_9,  (SCU_PINIO_FAST | 1)},
    {P1_5,  PWM_10, (SCU_PINIO_FAST | 1)},
    {P1_7,  PWM_13, (SCU_PINIO_FAST | 2)},
    {P1_8,  PWM_12, (SCU_PINIO_FAST | 2)},
    {P1_9,  PWM_11, (SCU_PINIO_FAST | 2)},
    {P1_10, PWM_14, (SCU_PINIO_FAST | 2)},
    {P1_11, PWM_15, (SCU_PINIO_FAST | 2)},
    {P2_7,  PWM_1,  (SCU_PINIO_FAST | 1)},
    {P2_8,  PWM_0,  (SCU_PINIO_FAST | 1)},
    {P2_9,  PWM_3,  (SCU_PINIO_FAST | 1)},
    {P2_10, PWM_2,  (SCU_PINIO_FAST | 1)},
    {P2_11, PWM_5,  (SCU_PINIO_FAST | 1)},
    {P2_12, PWM_4,  (SCU_PINIO_FAST | 1)},
    {P4_1,  PWM_1,  (SCU_PINIO_FAST | 1)},
    {P4_2,  PWM_0,  (SCU_PINIO_FAST | 1)},
    {P4_3,  PWM_3,  (SCU_PINIO_FAST | 1)},
    {P4_4,  PWM_2,  (SCU_PINIO_FAST | 1)},
    {P4_5,  PWM_5,  (SCU_PINIO_FAST | 1)},
    {P4_6,  PWM_4,  (SCU_PINIO_FAST | 1)},
    {P6_5,  PWM_6,  (SCU_PINIO_FAST | 1)},
    {P6_12, PWM_7,  (SCU_PINIO_FAST | 1)},
    {P7_0,  PWM_14, (SCU_PINIO_FAST | 1)},
    {P7_1,  PWM_15, (SCU_PINIO_FAST | 1)},
    {P7_4,  PWM_13, (SCU_PINIO_FAST | 1)},
    {P7_5,  PWM_12, (SCU_PINIO_FAST | 1)},
    {P7_6,  PWM_11, (SCU_PINIO_FAST | 1)},
    {P7_7,  PWM_8,  (SCU_PINIO_FAST | 1)},
    {PA_4,  PWM_9,  (SCU_PINIO_FAST | 1)},
    {PB_0,  PWM_10, (SCU_PINIO_FAST | 1)},
    {PB_1,  PWM_6,  (SCU_PINIO_FAST | 5)},
    {PB_2,  PWM_7,  (SCU_PINIO_FAST | 5)},
    {PB_3,  PWM_8,  (SCU_PINIO_FAST | 5)},
    {PD_0,  PWM_15, (SCU_PINIO_FAST | 1)},
    {PD_2,  PWM_7,  (SCU_PINIO_FAST | 1)},
    {PD_3,  PWM_6,  (SCU_PINIO_FAST | 1)},
    {PD_4,  PWM_8,  (SCU_PINIO_FAST | 1)},
    {PD_5,  PWM_9,  (SCU_PINIO_FAST | 1)},
    {PD_6,  PWM_10, (SCU_PINIO_FAST | 1)},
    {PD_9,  PWM_13, (SCU_PINIO_FAST | 1)},
    {PD_11, PWM_14, (SCU_PINIO_FAST | 6)},
    {PD_12, PWM_10, (SCU_PINIO_FAST | 6)},
    {PD_13, PWM_13, (SCU_PINIO_FAST | 6)},
    {PD_14, PWM_11, (SCU_PINIO_FAST | 6)},
    {PD_15, PWM_8,  (SCU_PINIO_FAST | 6)},
    {PD_16, PWM_12, (SCU_PINIO_FAST | 6)},
    {PE_5,  PWM_3,  (SCU_PINIO_FAST | 1)},
    {PE_6,  PWM_2,  (SCU_PINIO_FAST | 1)},
    {PE_7,  PWM_5,  (SCU_PINIO_FAST | 1)},
    {PE_8,  PWM_4,  (SCU_PINIO_FAST | 1)},
    {PE_11, PWM_12, (SCU_PINIO_FAST | 1)},
    {PE_12, PWM_11, (SCU_PINIO_FAST | 1)},
    {PE_13, PWM_14, (SCU_PINIO_FAST | 1)},
    {PE_15, PWM_0,  (SCU_PINIO_FAST | 1)},
    {PF_9,  PWM_1,  (SCU_PINIO_FAST | 2)},
    {NC,    NC, 0}
};

static unsigned int pwm_clock_mhz;

static void _pwmout_dev_init() {
    uint32_t i;

    // set SCT clock and config
    LPC_CCU1->CLKCCU[CLK_MX_SCT].CFG = (1 << 0); // enable SCT clock in CCU1
    LPC_SCT->CONFIG |= PWM_CONFIG; // set config options
    *PWM_CTRL |= PWM_HALT; // set HALT bit to stop counter
    // clear counter and set prescaler for desired freq
    *PWM_CTRL |= PWM_CLEAR | PWM_PRE(SystemCoreClock / PWM_FREQ_BASE - 1); 
    pwm_clock_mhz = PWM_FREQ_BASE / 1000000;

    // configure SCT events
    for (i = 0; i < PWM_EVENT_MAX; i++) {
        *PWM_MATCH(i) = 0; // match register
        *PWM_MR(i) = 0; // match reload register
        LPC_SCT->EVENT[i].STATE = 0xFFFFFFFF; // event happens in all states
        LPC_SCT->EVENT[i].CTRL  = (i << 0) | PWM_EVT_MASK; // match condition only
    }
    *PWM_LIMIT = (1 << 0) ; // set event 0 as limit
    // initialize period to 20ms: standard for servos, and fine for e.g. brightness control
    *PWM_MR0 = PWM_SETCOUNT((uint32_t)(((20 * PWM_FREQ_BASE) / 1000000) * 1000));

    // initialize SCT outputs
    for (i = 0; i < CONFIG_SCT_nOU; i++) {
        LPC_SCT->OUT[i].SET = (1 << 0); // event 0 will set SCTOUT_xx
        LPC_SCT->OUT[i].CLR = 0; // set clear event when duty cycle
    }
    LPC_SCT->OUTPUT = 0; // default outputs to clear

    *PWM_CTRL &= ~PWM_HALT; // clear HALT bit to start counter
}

void pwmout_init(pwmout_t* obj, PinName pin) {
    // determine the channel
    PWMName pwm = (PWMName)pinmap_peripheral(pin, PinMap_PWM);
    MBED_ASSERT((pwm != (PWMName)NC) && (event < PWM_EVENT_MAX));

    // init SCT clock and outputs on first PWM init
    if (event == 0) {
        _pwmout_dev_init();
    }
    // init PWM object
    event++;
    obj->pwm = pwm; // pwm output
    obj->mr = event; // index of match reload register

    // initial duty cycle is 0
    pwmout_write(obj, 0);
    
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
    
    // set new pulse width
    uint32_t us = (uint32_t)((float)PWM_GETCOUNT(*PWM_MR0) * value) * pwm_clock_mhz;
    pwmout_pulsewidth_us(obj, us);
}

float pwmout_read(pwmout_t* obj) {
    float v = (float)PWM_GETCOUNT(*PWM_MR(obj->mr)) / (float)PWM_GETCOUNT(*PWM_MR0);
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
    uint32_t old_ticks = PWM_GETCOUNT(*PWM_MR0);
    uint32_t i, v;

    // set new period
    *PWM_MR0 = PWM_SETCOUNT(ticks);

    // Scale pulse widths to preserve the duty ratio
    for (i = 1; i < PWM_EVENT_MAX; i++) {
        v = PWM_GETCOUNT(*PWM_MR(i));
        if (v > 1) {
            v = (v * ticks) / old_ticks;
            *PWM_MR(i) = PWM_SETCOUNT(v);
        }
    }
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
    //MBED_ASSERT(PWM_GETCOUNT(*PWM_MR0) >= v);

    if (v > 0) {
        // set new match register value and enable SCT output
        *PWM_MR(obj->mr) = PWM_SETCOUNT(v);
        LPC_SCT->OUT[obj->pwm].CLR = (1 << obj->mr);  // on event will clear PWM_XX
    } else {
        // set match to zero and disable SCT output
        *PWM_MR(obj->mr) = 0;
        LPC_SCT->OUT[obj->pwm].CLR = 0;
    }
}
