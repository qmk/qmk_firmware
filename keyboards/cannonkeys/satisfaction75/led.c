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
// #include "backlight.h"
#include "led.h"
#include "satisfaction75.h"
#include "printf.h"


static PWMConfig pwmCFG = {
  10000,                              /* 10kHz PWM clock frequency  */
  50,                              /* PWM period (in ticks) 1S (1/10kHz=0.1mS 0.1ms*10000 ticks=1S) */
  NULL,                               /* No Callback */
  {
      {PWM_OUTPUT_ACTIVE_HIGH, NULL}, /* Enable Channel 0 */
      {PWM_OUTPUT_DISABLED, NULL}, /* Enable Channel 1 */
      {PWM_OUTPUT_DISABLED, NULL},
      {PWM_OUTPUT_DISABLED, NULL}
  },
  0,                                  /* HW dependent part.*/
  0
};

void backlight_init_ports(void) {
    printf("backlight_init_ports()\n");
    palSetPadMode(GPIOA, 6, PAL_MODE_ALTERNATE(1));
    pwmStart(&PWMD3, &pwmCFG);
    pwmEnableChannel(&PWMD3, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD3, 10000));
}

void backlight_set(uint8_t level) {
    printf("backlight_set(%d)\n", level);
    uint32_t duty = (uint32_t)((float)level/BACKLIGHT_LEVELS * 10000);
    if (level == 0) {
        // Turn backlight off
        pwmDisableChannel(&PWMD3, 0);
    } else {
      printf("enabling backlight\n");
      // Turn backlight on
      pwmEnableChannel(&PWMD3, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD3, duty));
    }
}


uint8_t backlight_tick = 0;

void backlight_task(void) {
  // if (curr_level == 0){
  //   return;
  // backlight_tick = (backlight_tick +
  // }

  // if ((0xFFFF >> ((BACKLIGHT_LEVELS - curr_level) * ((BACKLIGHT_LEVELS + 1) / 2))) & (1 << backlight_tick)) {
  //     palSetPad(GPIOA, 8);
  // } else {
  //     palClearPad(GPIOA, 8);
  // }1) % 16;
}
