/*
This is the c configuration file for the subproject

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2017 Art Ortenburger

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
// Rows are doubled-up
#define MATRIX_ROWS 6
#define MATRIX_COLS 9

// wiring of each half


//PRO MICRO
#define MATRIX_ROW_PINS { D4, B4, B5 }
#define MATRIX_COL_PINS { D7, F4, F5, F6, F7, B1, B3, B2, B6 }
//#define MATRIX_COL_PINS { B2, B3, B1, F7, F6, F5, F4, D7 }


/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define SOFT_SERIAL_PIN D0

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* number of backlight levels */
// #define BACKLIGHT_LEVELS 3

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
// #define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
// #define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() ( \
    get_mods() == (MOD_BIT(KC_LSFT) | MOD_BIT(KC_LGUI)) \
)

/* ws2812 RGB LED */
//#define RGB_DI_PIN D3
//#define RGBLED_NUM 16    // Number of LEDs

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
