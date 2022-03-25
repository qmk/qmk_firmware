/*
Copyright 2015 Jun Wako <wakojun@gmail.com>

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

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x2B29
#define DEVICE_VER      0x0001
#define MANUFACTURER    Wolfmark Club
#define PRODUCT         WM1

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

//                         0    1    2    3    4     5   6   7    8     9   A   B  C   D   E  
#define MATRIX_ROW_PINS { C4,  A7,  A6,  A5,  A4 }
#define MATRIX_COL_PINS { B10, B11, B12, B13, B14, B15, C6, C10, C11, C12, D2, B5, B6, B7, B8 }

#define DIODE_DIRECTION COL2ROW

/* number of backlight levels */
// #define BACKLIGHT_PIN A2
// #ifdef BACKLIGHT_PIN
// #define BACKLIGHT_LEVELS 5
// #endif

#define RGB_DI_PIN A3
#ifdef RGB_DI_PIN
#define RGBLED_NUM 18
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
#define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
#endif
/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5
/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
