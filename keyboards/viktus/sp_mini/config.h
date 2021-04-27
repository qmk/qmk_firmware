/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

/* USB Device descriptor parameter */
#define VENDOR_ID       0x5644
#define PRODUCT_ID      0x5111
#define DEVICE_VER      0x0100
#define MANUFACTURER    Viktus Design
#define PRODUCT         SP Mini

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 10
#define MATRIX_COLS 8


// wiring of each half
#define MATRIX_ROW_PINS { F0, B5, B4, D7, D6 }
#define MATRIX_COL_PINS { B6, C6, C7, D4, D2, D3, D5 } // no B7 on left hand
#define MATRIX_ROW_PINS_RIGHT { F0, B5, B4, D7, D6 }
//#define MATRIX_COL_PINS_RIGHT { B6, C6, C7, D4, D2, D3, D5, B7 }
#define MATRIX_COL_PINS_RIGHT { B7, D5, D3, D2, D4, C7, C6, B6 }

#define DIODE_DIRECTION COL2ROW

/* Split Defines */
#define MASTER_LEFT

#define USE_I2C

/* serial.c configuration for split keyboard */
//#define SOFT_SERIAL_PIN D1


/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* ws2812 RGB LED */
#define RGB_DI_PIN E6
#define RGBLIGHT_ANIMATIONS
//#define RGBLIGHT_SPLIT
#define RGBLED_NUM 24    // Number of LEDs
#define RGBLED_SPLIT { 12, 12 }

//#define ENCODERS_PAD_A {F4}
//#define ENCODERS_PAD_B {F1}
//#define ENCODERS_PAD_A_RIGHT {F4}
//#define ENCODERS_PAD_B_RIGHT {F1}


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
