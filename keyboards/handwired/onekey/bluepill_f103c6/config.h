/* Copyright 2019
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

#define PRODUCT Onekey Bluepill STM32F103C6

#define MATRIX_COL_PINS { B0 }
#define MATRIX_ROW_PINS { A7 }
#define UNUSED_PINS

#define BACKLIGHT_PIN         A0
#define BACKLIGHT_PWM_DRIVER  PWMD2
#define BACKLIGHT_PWM_CHANNEL 1

#define RGB_DI_PIN A1

#define ADC_PIN A0

// This code does not fit into the really small flash of STM32F103x6 together
// with CONSOLE_ENABLE=yes, and the debugging console is probably more
// important for the "okeney" testing firmware.  In a real firmware you may be
// able to use these features if you keep the debugging console disabled.
#define NO_ACTION_LAYER
#define NO_ACTION_TAPPING
