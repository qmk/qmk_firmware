/*
Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>

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

#define VENDOR_ID       0x1234
#define PRODUCT_ID      0x5679
#define MANUFACTURER    winkeyless.kr
#define PRODUCT         JC65 PS2AVRGB

/* matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 16

#define BACKLIGHT_LEVELS 1
#define RGBLED_NUM 16
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_EFFECT_KNIGHT_LED_NUM 8

#define NO_UART 1

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
