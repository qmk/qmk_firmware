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

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 10
#define MATRIX_COLS 8


// wiring of each half
#define MATRIX_ROW_PINS { F0, B5, B4, D7, D6 }
#define MATRIX_COL_PINS { B6, C6, C7, D4, D2, D3, D5, NO_PIN } // no B7 on left hand
#define MATRIX_ROW_PINS_RIGHT { F0, B5, B4, D7, D6 }
#define MATRIX_COL_PINS_RIGHT { B6, C6, C7, D4, D2, D3, D5, B7 }


#define DIODE_DIRECTION COL2ROW

/* Split Defines */
#define SPLIT_USB_DETECT
#define MASTER_LEFT
#define USE_I2C

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5


/* ws2812 RGB LED */
#define RGB_DI_PIN E6
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_TWINKLE

//#define RGBLIGHT_SPLIT
#define RGBLED_NUM 24    // Number of LEDs
#define RGBLED_SPLIT { 12, 12 }



#define ENCODERS_PAD_A {F4}
#define ENCODERS_PAD_B {F1}
//#define ENCODERS_PAD_A_RIGHT {F4}
//#define ENCODERS_PAD_B_RIGHT {F1}

#define ENCODER_RESOLUTIONS { 8 }

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
