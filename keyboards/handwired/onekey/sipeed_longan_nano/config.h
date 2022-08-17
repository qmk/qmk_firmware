/* Copyright 2021 QMK
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

#pragma once

#include "config_common.h"

#define MATRIX_COL_PINS \
    { B0 }
#define MATRIX_ROW_PINS \
    { A7 }

#define BACKLIGHT_PIN A1           /* Green LED. */
#define BACKLIGHT_PWM_DRIVER PWMD5 /* GD32 numbering scheme starts from 0, TIMER4 on GD32 boards is TIMER5 on STM32 boards. */
#define BACKLIGHT_PWM_CHANNEL 2    /* GD32 numbering scheme starts from 0, Channel 1 on GD32 boards is Channel 2 on STM32 boards. */

#define RGB_DI_PIN A2
#define RGB_CI_PIN B13

#define ADC_PIN A0

#define I2C1_CLOCK_SPEED 1000000 /* GD32VF103 supports fast mode plus. */
#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2
