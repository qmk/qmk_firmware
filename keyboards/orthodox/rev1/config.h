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

#ifndef REV1_CONFIG_H
#define REV1_CONFIG_H

#include "../config.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x3060
#define DEVICE_VER      0x0001
#define MANUFACTURER    deductivemonkee
#define PRODUCT         Monkeebs Orthodox Rev.1
#define DESCRIPTION     Oreodox

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 6
#define MATRIX_COLS 9

// wiring of each half


//PRO MICRO
#define MATRIX_ROW_PINS { D4, B4, B5 }
#define MATRIX_COL_PINS { D7, F4, F5, F6, F7, B1, B3, B2, B6 }
//#define MATRIX_COL_PINS { B2, B3, B1, F7, F6, F5, F4, D7 }

/*/
//TEENSY
#define MATRIX_ROW_PINS { D0, C6, C7, }
#define MATRIX_COL_PINS { D2, F5, F6, F7, B6, B5, B4, D7, D6 }
/*/

#define CATERINA_BOOTLOADER

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* number of backlight levels */
// #define BACKLIGHT_LEVELS 3

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
// #define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
// #define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

/* ws2812 RGB LED */
//#define RGB_DI_PIN D3
//#define RGBLIGHT_TIMER
//#define RGBLED_NUM 16    // Number of LEDs
//#define ws2812_PORTREG  PORTD
//#define ws2812_DDRREG   DDRD

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
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

#endif
