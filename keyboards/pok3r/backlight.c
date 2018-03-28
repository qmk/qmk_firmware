/* Copyright 2018 Jonathan A. Kollasch
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ch.h"
#include "hal.h"

#include "quantum.h"
#include "backlight.h"

#ifdef BACKLIGHT_ENABLE
void
backlight_init_ports(void)
{
  /* 210Hz, 200 steps per cycle */
  static const PWMConfig config = {
    .frequency = 210 * 200,
    .period = 200,
    .callback = NULL,
    .channels = {
      [0] = {
        .mode = PWM_OUTPUT_ACTIVE_HIGH,
        .callback = NULL,
      },
    },
  };

  palSetLine(LINE_BLPWM);
  palSetLineMode(LINE_BLPWM, PAL_MODE_OUTPUT_PUSHPULL|PAL_MODE_HT32_AF(AFIO_TM));
  pwmStart(&PWMD_MCTM0, &config);

  palClearLine(LINE_BLEN);
  palSetLineMode(LINE_BLEN, PAL_MODE_OUTPUT_OPENDRAIN);
}

void
backlight_set(uint8_t level)
{
  if (level == 0) {
    pwmDisableChannel(&PWMD_MCTM0, 0);
    palClearLine(LINE_BLEN);
  } else if (level <= BACKLIGHT_LEVELS) {
    pwmEnableChannel(&PWMD_MCTM0, 0, PWM_FRACTION_TO_WIDTH(&PWMD_MCTM0, BACKLIGHT_LEVELS, level));
    palSetLine(LINE_BLEN);
  }
}
#endif
