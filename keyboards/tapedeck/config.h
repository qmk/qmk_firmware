/*
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

/* Matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 5

/* Pin-out */
#define MATRIX_ROW_PINS { B2, B3, B1 }
#define MATRIX_COL_PINS { B5, B4, E6, D7, C6 }
#define QMK_LED B0

#define QMK_ESC_OUTPUT B2
#define QMK_ESC_INPUT B5

/* ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* RGB */
#define RGB_DI_PIN B6
#define RGBLED_NUM 3
#define RGBLIGHT_EFFECT_STATIC_LIGHT
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_LIMIT_VAL 225

/* Rotary Encoder*/
#define ENCODERS_PAD_A { F4, F6 }
#define ENCODERS_PAD_B { F5, F7 }
#define ENCODER_RESOLUTION 4

/* SLIDER */
#define POT_ENABLE

