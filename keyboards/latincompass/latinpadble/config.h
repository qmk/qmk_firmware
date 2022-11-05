/*
Copyright 2021 haierwangwei2005

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

#pragma once

#include "config_common.h"

// #define NO_ACTION_LAYER
// #define NO_ACTION_TAPPING
// #define NO_ACTION_ONESHOT

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 4
#define MATRIX_ROW_PINS { F0, F6, F5, F4, F1 }
#define MATRIX_COL_PINS { D6, D7, B5, B6 }

#define DIODE_DIRECTION ROW2COL

#define RGB_DI_PIN B7

#define RGBLED_NUM 4

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

#define RGBLIGHT_VAL_STEP 25
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_KNIGHT_OFFSET 20
#define RGBLIGHT_EFFECT_STATIC_GRADIENT

#define OLED_FONT_H "./lib/glcdfont.c"

#define ENCODERS_PAD_A { C7 }
#define ENCODERS_PAD_B { F7 }

#define ENCODER_RESOLUTION 4

#define VIA_HAS_BROKEN_KEYCODES
