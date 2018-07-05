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
//#include "led.h"



/* New awesome dual color leds functions, animations and more */
/* Based on pwm_callback by fcayci: https://github.com/fcayci/STM32F4-ChibiOS/blob/master/pwm_callback/main.c */

static void pwmcb(PWMDriver *pwmp);

static PWMConfig pwmcfg = {
    1000,        // Clock frecuency (seconds) = 1/value
    100,         // PWM period (ticks = clockfrecuency * pwmperiod)
    pwmcb,        // Callback, disable with NULL
    {
        {PWM_OUTPUT_ACTIVE_HIGH, NULL}, /* Enable Channel 0 */
        {PWM_OUTPUT_ACTIVE_HIGH, NULL}, /* Enable Channel 1 */
        //{PWM_OUTPUT_ACTIVE_HIGH, NULL}, /* Enable Channel 2 */
        //{PWM_OUTPUT_ACTIVE_HIGH, NULL}  /* Enable Channel 3 */
    },
    0, /* HW dependent part */
    0
};


/*
 * PWM callback.
 * Each time calculate the next duty cycle.
 */
static void pwmcb(PWMDriver *pwmp) {
    (void)pwmp;

    static uint16_t dir = 0, width = 0;

    if (dir == 0) {width = (width + 100);}
    else {width = (width - 100);}

    if (width >= 100) {dir = 1;}
    else if (width == 0) {dir = 0;}

    pwmEnableChannel(&PWMD4, 0, width);
    pwmEnableChannel(&PWMD4, 1, 100-width);
    //pwmEnableChannel(&PWMD4, 2, width);
    //pwmEnableChannel(&PWMD4, 3, 100-width);
}

static void iniciarluces(void) {

    palSetPadMode(GPIOC, 15, PAL_MODE_ALTERNATE(2));  /* Green */
    palSetPadMode(GPIOC, 14, PAL_MODE_ALTERNATE(2));  /* Red */

    pwmStart(&PWMD4, &pwmCFG);

}





// inline void gh60_caps_led_off(void)     { DDRB &= ~(1<<2); PORTB &= ~(1<<2); }

// inline void gh60_caps_led_on(void)      { DDRB |=  (1<<2); PORTB &= ~(1<<2); }