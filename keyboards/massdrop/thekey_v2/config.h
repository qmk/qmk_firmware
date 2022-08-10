/* Copyright 2022 Jason Wihardja
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 3

/*
 * Keyboard Matrix Assignments
 */
#define MATRIX_ROW_PINS { D4 }
#define MATRIX_COL_PINS { D2, D1, D0 }

#define DIODE_DIRECTION ROW2COL

#define RGB_DI_PIN B1
#define RGBLED_NUM 5
#define RGBLIGHT_LED_MAP {4, 0, 1, 2, 3}
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 10
#define RGBLIGHT_VAL_STEP 15
#define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
#define RGBLIGHT_SLEEP /* If defined, the RGB lighting will be switched off when the host goes to sleep */
#define RGBLIGHT_LAYERS /* Enable lighting layers */
#define RGBLIGHT_LAYER_BLINK /* Enable lighting layer blink */
