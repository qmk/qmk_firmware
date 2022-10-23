/*
Copyright 2021 Bryan Ong

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

/*Bootmagic boot button, set to topmost, leftmost key */
#define BOOTMAGIC_LITE_ROW	2
#define BOOTMAGIC_LITE_COLUMN	0

/* encoder */
/* #define NUMBER_OF_ENCODERS 1 */
#define ENCODERS_PAD_A { D3 }
#define ENCODERS_PAD_B { D2 }
#define ENCODER_RESOLUTION 1

/* key matrix size */
#define MATRIX_ROWS 9
#define MATRIX_COLS 8

/* key matrix pins */
#define MATRIX_ROW_PINS { F1, E6, F4, B1, F5, B2, F6, B3, B7 }
#define MATRIX_COL_PINS { F0, D0, C7, C6, B6, B5, B4, D1 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5


#define LED_NUM_LOCK_PIN  D4
#define LED_CAPS_LOCK_PIN D6

#define RGB_DI_PIN F7
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
#define RGBLED_NUM 14
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8