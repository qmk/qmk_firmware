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

// Ported from LPC824 and adapted.

#if DEVICE_PWMOUT

#define PWM_IRQn     SCT_IRQn

// Bit flags for used SCT Outputs
static unsigned char sct_used = 0;
static int sct_inited = 0;

// Find available output channel
// Max number of PWM outputs is 4 on LPC812
static int get_available_sct() {
   int i;
       
// Find available output channel 0..3
// Also need one Match register per channel
    for (i = 0; i < CONFIG_SCT_nOU; i++) {
//    for (i = 0; i < 4; i++) {
        if ((sct_used & (1 << i)) == 0)
            return i;
    }
    return -1;
}

// Any Port pin may be used for PWM.
// Max number of PWM outputs is 4
void pwmout_init(pwmout_t* obj, PinName pin) {
    MBED_ASSERT(pin != (uint32_t)NC);

    int sct_n = get_available_sct();
    if (sct_n == -1) {
        error("No available SCT Output");
    }

    sct_used |= (1 << sct_n);

    obj->pwm =  (LPC_SCT_TypeDef*)LPC_SCT;
    obj->pwm_ch = sct_n;

    LPC_SCT_TypeDef* pwm = obj->pwm;

    // Init SCT on first use
    if (! sct_inited) {
      sct_inited = 1;

      // Enable the SCT clock
      LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 8);

      // Clear peripheral reset the SCT:
      LPC_SYSCON->PRESETCTRL |=  (1 << 8);

      // Two 16-bit counters, autolimit (ie reset on Match_0)
      //pwm->CONFIG &= ~(0x1);
      //pwm->CONFIG |= (1 << 17);
      pwm->CONFIG |= ((0x3 << 17) | 0x01);

      // halt and clear the counter
      pwm->CTRL_U |= (1 << 2) | (1 << 3);

      // System Clock (30 Mhz) -> Prescaler -> us_ticker (1 MHz)
      pwm->CTRL_U &= ~(0x7F << 5);
      pwm->CTRL_U |= (((SystemCoreClock/1000000 - 1) & 0x7F) << 5);

      pwm->EVENT[0].CTRL  = (1 << 12) | 0;                     // Event_0 on Match_0
      pwm->EVENT[0].STATE = 0xFFFFFFFF;                        // All states
    
      // unhalt the counter:
      //    - clearing bit 2 of the CTRL register
      pwm->CTRL_U &= ~(1 << 2);
      
      // Not using IRQs 
      //NVIC_SetVector(PWM_IRQn, (uint32_t)pwm_irq_handler);
      //NVIC_EnableIRQ(PWM_IRQn);    
    }

    // LPC81x has only one SCT and 4 Outputs
    // LPC82x has only one SCT and 6 Outputs
    // LPC1549 has 4 SCTs and 16 Outputs    
    switch(sct_n) {
        case 0:
            // SCTx_OUT0
            LPC_SWM->PINASSIGN[6] &= ~0xFF000000;
            LPC_SWM->PINASSIGN[6] |= (pin << 24);
            break;
        case 1:
            // SCTx_OUT1
            LPC_SWM->PINASSIGN[7] &= ~0x000000FF;
            LPC_SWM->PINASSIGN[7] |= (pin);
            break;
        case 2:
            // SCTx_OUT2
            LPC_SWM->PINASSIGN[7] &= ~0x0000FF00;
            LPC_SWM->PINASSIGN[7] |= (pin << 8);
            break;
        case 3:
            // SCTx_OUT3
            LPC_SWM->PINASSIGN[7] &= ~0x00FF0000;
            LPC_SWM->PINASSIGN[7] |= (pin << 16);
            break;
        default:
            break;
    }

    pwm->EVENT[sct_n + 1].CTRL  = (1 << 12) | (sct_n + 1);  // Event_n on Match_n
    pwm->EVENT[sct_n + 1].STATE = 0xFFFFFFFF;               // All states

    pwm->OUT[sct_n].SET = (1 << 0);                         // All PWM channels are SET on Event_0
    pwm->OUT[sct_n].CLR = (1 << (sct_n + 1));               // PWM ch is CLRed on Event_(ch+1)
   
    // default to 20ms: standard for servos, and fine for e.g. brightness control
    pwmout_period_ms(obj, 20);   // 20ms period
    pwmout_write    (obj, 0.0);  //  0ms pulsewidth, dutycycle 0
}

void pwmout_free(pwmout_t* obj) {
    // PWM channel is now free
    sct_used &= ~(1 << obj->pwm_ch);
    
    // Disable the SCT clock when all channels free
    if (sct_used == 0) {  
      LPC_SYSCON->SYSAHBCLKCTRL &= ~(1 << 8);
      sct_inited = 0;
    };  
}

// Set new dutycycle (0.0 .. 1.0)
void pwmout_write(pwmout_t* obj, float value) {
    //value is new dutycycle
    if (value < 0.0f) {
        value = 0.0;
    } else if (value > 1.0f) {
        value = 1.0;
    }
     
    // Match_0 is PWM period. Compute new endtime of pulse for current channel
    uint32_t t_off = (uint32_t)((float)(obj->pwm->MATCHREL[0].U) * value);
    obj->pwm->MATCHREL[(obj->pwm_ch) + 1].U = t_off; // New endtime
}

// Get dutycycle (0.0 .. 1.0)
float pwmout_read(pwmout_t* obj) {
    uint32_t t_period = obj->pwm->MATCHREL[0].U;

    //Sanity check
    if (t_period == 0) {
     return 0.0;
    };
     
    uint32_t t_off  = obj->pwm->MATCHREL[(obj->pwm_ch) + 1].U;
    float v = (float)t_off/(float)t_period;
    //Sanity check    
    return (v > 1.0f) ? (1.0f) : (v);
}

// Set the PWM period, keeping the duty cycle the same (for this channel only!).
void pwmout_period(pwmout_t* obj, float seconds){
    pwmout_period_us(obj, seconds * 1000000.0f);
}

// Set the PWM period, keeping the duty cycle the same (for this channel only!).
void pwmout_period_ms(pwmout_t* obj, int ms) {
    pwmout_period_us(obj, ms * 1000);
}

// Set the PWM period, keeping the duty cycle the same (for this channel only!).
void pwmout_period_us(pwmout_t* obj, int us) {
    
    uint32_t t_period = obj->pwm->MATCHREL[0].U;  // Current PWM period
    obj->pwm->MATCHREL[0].U = (uint32_t)us;       // New PWM period

    //Keep the dutycycle for the new PWM period
    //Should really do this for all active channels!!
    //This problem exists in all mbed libs.

    //Sanity check
    if (t_period == 0) {
      return;
//      obj->pwm->MATCHREL[(obj->pwm_ch) + 1].L = 0; // New endtime for this channel     
    }
    else {    
      uint32_t t_off  = obj->pwm->MATCHREL[(obj->pwm_ch) + 1].U;
      float v = (float)t_off/(float)t_period;
      obj->pwm->MATCHREL[(obj->pwm_ch) + 1].U = (uint32_t)((float)us * (float)v); // New endtime for this channel
    }   
}


//Set pulsewidth
void pwmout_pulsewidth(pwmout_t* obj, float seconds) {
    pwmout_pulsewidth_us(obj, seconds * 1000000.0f);
}

//Set pulsewidth
void pwmout_pulsewidth_ms(pwmout_t* obj, int ms){
    pwmout_pulsewidth_us(obj, ms * 1000);
}

//Set pulsewidth
void pwmout_pulsewidth_us(pwmout_t* obj, int us) {

//Should add Sanity check to make sure pulsewidth < period!
    obj->pwm->MATCHREL[(obj->pwm_ch) + 1].U = (uint32_t)us; // New endtime for this channel
}

#endif
