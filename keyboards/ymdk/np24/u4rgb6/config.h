/* Copyright 2021 Simon Arlott
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

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 4

/* key matrix pins */
#define MATRIX_ROW_PINS { B3, B6, B2, B1, D7, B4 }
#define MATRIX_COL_PINS { F5, F4, D3, D2 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* LED indicator pins */
#define LED_NUM_LOCK_PIN    C6
#define LED_PIN_ON_STATE    0

/* number of backlight levels */
#define BACKLIGHT_PIN B7
#ifdef BACKLIGHT_PIN
# define BACKLIGHT_LEVELS 31
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define RGB_DI_PIN E2
#ifdef RGB_DI_PIN
# define RGBLED_NUM 6
# define RGBLIGHT_ANIMATIONS
#endif
