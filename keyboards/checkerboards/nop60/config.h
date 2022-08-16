 /*
Copyright 2021 Nathan Spears

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
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

/* key matrix pins */
#define MATRIX_ROW_PINS { F0, F1, E6, B7, C6 }
#define MATRIX_COL_PINS { F6, F5, F4, D0, D7, D3, D4, D5, D6, F7, C7, B4, B6, B5 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Switch LED Backlighting */
#define BACKLIGHT_PIN           D1
#define BACKLIGHT_PWM_DRIVER    PWMD3
#define BACKLIGHT_LEVELS 6
#define BACKLIGHT_BREATHING
#define BREATHING_PERIOD 6

// ws2812 options
#define RGB_DI_PIN D2 // pin the DI on the ws2812 is hooked-up to
#define RGBLIGHT_ANIMATIONS // run RGB animations
#define RGBLED_NUM 14 // number of LEDs
#define RGBLIGHT_HUE_STEP 12 // units to step when in/decreasing hue
#define RGBLIGHT_SAT_STEP 12 // units to step when in/decresing saturation
#define RGBLIGHT_VAL_STEP 12 // units to step when in/decreasing value (brightness)


/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
