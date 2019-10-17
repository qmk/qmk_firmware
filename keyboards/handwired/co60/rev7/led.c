/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "hal.h"
#include "led_custom.h"
#include "rev7.h"
#include "printf.h"

static void breathing_callback(PWMDriver *pwmp);

static PWMConfig pwmCFG = {
  0xFFFF,                              /* PWM clock frequency  */
  256,                              /* PWM period (in ticks) 1S (1/10kHz=0.1mS 0.1ms*10000 ticks=1S) */
  NULL,                               /* No Callback */
  {
      {PWM_OUTPUT_DISABLED, NULL},
      {PWM_OUTPUT_DISABLED, NULL},
      {PWM_OUTPUT_ACTIVE_HIGH, NULL}, /* Enable Channel 3 */
      {PWM_OUTPUT_DISABLED, NULL}
  },
  0,                                  /* HW dependent part.*/
  0
};

static PWMConfig pwmCFG_breathing = {
  0xFFFF,                              /* 10kHz PWM clock frequency  */
  256,                              /* PWM period (in ticks) 1S (1/10kHz=0.1mS 0.1ms*10000 ticks=1S) */
  breathing_callback,                               /* Breathing Callback */
  {
      {PWM_OUTPUT_DISABLED, NULL},
      {PWM_OUTPUT_DISABLED, NULL},
      {PWM_OUTPUT_ACTIVE_HIGH, NULL}, /* Enable Channel 3 */
      {PWM_OUTPUT_DISABLED, NULL}
  },
  0,                                  /* HW dependent part.*/
  0
};

// See http://jared.geek.nz/2013/feb/linear-led-pwm
static uint16_t cie_lightness(uint16_t v) {
  if (v <= 5243) // if below 8% of max
    return v / 9; // same as dividing by 900%
  else {
    uint32_t y = (((uint32_t) v + 10486) << 8) / (10486 + 0xFFFFUL); // add 16% of max and compare
    // to get a useful result with integer division, we shift left in the expression above
    // and revert what we've done again after squaring.
    y = y * y * y >> 8;
    if (y > 0xFFFFUL) // prevent overflow
      return 0xFFFFU;
    else
      return (uint16_t) y;
  }
}


void backlight_init_ports(void) {
  palSetPadMode(GPIOB, 8, PAL_MODE_ALTERNATE(2));
  pwmStart(&PWMD4, &pwmCFG);
  if(kb_backlight_config.enable){
    if(kb_backlight_config.breathing){
      breathing_enable();
    } else{
      backlight_set(kb_backlight_config.level);
    }
  } else {
    backlight_set(0);
  }
}

void backlight_set(uint8_t level) {
  uint32_t duty = (uint32_t)(cie_lightness(0xFFFF * (uint32_t) level / BACKLIGHT_LEVELS));
  if (level == 0) {
      // Turn backlight off
      // Disable channel 3 on PWM4
      pwmDisableChannel(&PWMD4, 2);
  } else {
    // Turn backlight on
    if(!is_breathing()){
      // Enable channel 3 on PWM4
      pwmEnableChannel(&PWMD4, 2, PWM_FRACTION_TO_WIDTH(&PWMD4,0xFFFF,duty));
    }
  }
}


uint8_t backlight_tick = 0;

void backlight_task(void) {
}

#define BREATHING_NO_HALT  0
#define BREATHING_HALT_OFF 1
#define BREATHING_HALT_ON  2
#define BREATHING_STEPS 128

static uint8_t breathing_period = BREATHING_PERIOD;
static uint8_t breathing_halt = BREATHING_NO_HALT;
static uint16_t breathing_counter = 0;

bool is_breathing(void) {
    return PWMD4.config == &pwmCFG_breathing;
}

#define breathing_min() do {breathing_counter = 0;} while (0)
#define breathing_max() do {breathing_counter = breathing_period * 256 / 2;} while (0)


void breathing_interrupt_enable(void){
    pwmStop(&PWMD4);
    pwmStart(&PWMD4, &pwmCFG_breathing);
    chSysLockFromISR();
    pwmEnablePeriodicNotification(&PWMD4);
    pwmEnableChannelI(
      &PWMD4,
      2,
      PWM_FRACTION_TO_WIDTH(
        &PWMD4,
        0xFFFF,
        0xFFFF
      )
    );
    chSysUnlockFromISR();
}

void breathing_interrupt_disable(void){
    pwmStop(&PWMD4);
    pwmStart(&PWMD4, &pwmCFG);
}

void breathing_enable(void)
{
  breathing_counter = 0;
  breathing_halt = BREATHING_NO_HALT;
  breathing_interrupt_enable();
}

void breathing_pulse(void)
{
    if (kb_backlight_config.level == 0)
      breathing_min();
    else
      breathing_max();
    breathing_halt = BREATHING_HALT_ON;
    breathing_interrupt_enable();
}

void breathing_disable(void)
{
    breathing_interrupt_disable();
    // Restore backlight level
    backlight_set(kb_backlight_config.level);
}

void breathing_self_disable(void)
{
  if (kb_backlight_config.level == 0)
    breathing_halt = BREATHING_HALT_OFF;
  else
    breathing_halt = BREATHING_HALT_ON;
}

void breathing_toggle(void) {
  if (is_breathing()){
    breathing_disable();
  } else {
    breathing_enable();
  }
}

void breathing_period_set(uint8_t value)
{
  if (!value)
    value = 1;
  breathing_period = value;
}

void breathing_period_default(void) {
  breathing_period_set(BREATHING_PERIOD);
}

void breathing_period_inc(void)
{
  breathing_period_set(breathing_period+1);
}

void breathing_period_dec(void)
{
  breathing_period_set(breathing_period-1);
}

/* To generate breathing curve in python:
 * from math import sin, pi; [int(sin(x/128.0*pi)**4*255) for x in range(128)]
 */
static const uint8_t breathing_table[BREATHING_STEPS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 4, 5, 6, 8, 10, 12, 15, 17, 20, 24, 28, 32, 36, 41, 46, 51, 57, 63, 70, 76, 83, 91, 98, 106, 113, 121, 129, 138, 146, 154, 162, 170, 178, 185, 193, 200, 207, 213, 220, 225, 231, 235, 240, 244, 247, 250, 252, 253, 254, 255, 254, 253, 252, 250, 247, 244, 240, 235, 231, 225, 220, 213, 207, 200, 193, 185, 178, 170, 162, 154, 146, 138, 129, 121, 113, 106, 98, 91, 83, 76, 70, 63, 57, 51, 46, 41, 36, 32, 28, 24, 20, 17, 15, 12, 10, 8, 6, 5, 4, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// Use this before the cie_lightness function.
static inline uint16_t scale_backlight(uint16_t v) {
  return v / BACKLIGHT_LEVELS * kb_backlight_config.level;
}

static void breathing_callback(PWMDriver *pwmp)
{
  (void)pwmp;
  uint16_t interval = (uint16_t) breathing_period * 256 / BREATHING_STEPS;
  // resetting after one period to prevent ugly reset at overflow.
  breathing_counter = (breathing_counter + 1) % (breathing_period * 256);
  uint8_t index = breathing_counter / interval % BREATHING_STEPS;

  if (((breathing_halt == BREATHING_HALT_ON) && (index == BREATHING_STEPS / 2)) ||
      ((breathing_halt == BREATHING_HALT_OFF) && (index == BREATHING_STEPS - 1)))
  {
      breathing_interrupt_disable();
  }

  uint32_t duty = cie_lightness(scale_backlight(breathing_table[index] * 256));

  chSysLockFromISR();
  pwmEnableChannelI(
    &PWMD4,
    2,
    PWM_FRACTION_TO_WIDTH(
      &PWMD4,
      0xFFFF,
      duty
    )
  );
  chSysUnlockFromISR();
}
