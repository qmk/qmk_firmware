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
#define PRODUCT_ID   0x3435
#define DEVICE_VER   0x0001
#define MANUFACTURER ChrisTrotter

/* key matrix size */
// Rows are doubled-up due to split kb; something in the qmk code requires this
#define MATRIX_ROWS 10
#define MATRIX_COLS 6

// wiring of each half
#define MATRIX_ROW_PINS { B7, D5, C7, F1, F0 }
#define MATRIX_COL_PINS { D4, C6, D7, E6, B4, B5 }

// TODO does this need to be reversed?
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

// WS2812 RGB LED strip input and number of LEDs
#define RGB_DI_PIN B6
#define RGBLED_NUM 57
// is this R,L ; or is it the opposite?
#define RGB_LED_SPLIT { 27, 30} 
// #define RGBLIGHT_LIMIT_VAL 180
// #define RGBLIGHT_ANIMATIONS
// #define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_TEST
/* number of backlight levels */
// #define BACKLIGHT_LEVELS 3

// audio
// #define AUDIO_PIN F5

/* trackball config */
#define PMW3360_CS_PIN B1