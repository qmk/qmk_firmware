/*
Copyright 2020 Moritz Plattner

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

#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 12
#define MATRIX_COLS 11

#define MATRIX_ROW_PINS { B11, B10, B2,  B1,  B0, A7, A6,  A5,  A4,  A3,  A2, A0 }
#define MATRIX_COL_PINS { B12, B13, B14, B15, A8, A9, A10, A13, A14, A15, B3     }

#define LED_NUM_LOCK_PIN B6
#define LED_CAPS_LOCK_PIN B5
#define LED_SCROLL_LOCK_PIN B4
#define LED_PIN_ON_STATE 0

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE 5

/* Backlight */
#define BACKLIGHT_PIN A1
#define BACKLIGHT_BREATHING
#define BACKLIGHT_PWM_DRIVER PWMD2
#define BACKLIGHT_PWM_CHANNEL 2
#define BACKLIGHT_PAL_MODE 2
#define BACKLIGHT_LEVELS 5
#define BACKLIGHT_ON_STATE 1
#define BACKLIGHT_PWM_OUTPUT_FREQUENCY 1000 // Increases backlight PWM freq if compiled with an unmerged PR. Does no harm without it.
