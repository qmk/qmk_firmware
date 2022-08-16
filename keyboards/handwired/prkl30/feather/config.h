/* Copyright 2020 Erkki Halinen & Toni Johansson
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
#define MATRIX_ROWS 4
#define MATRIX_COLS 10

/* PRKL30 feather pinout */
#define MATRIX_ROW_PINS { F4, F1, F0, D2}
#define MATRIX_COL_PINS { D3, D1, B7, D6, C7, B6, B5, D7, C6, D0}
/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW
#define ENCODERS_PAD_A { F7 }
#define ENCODERS_PAD_B { F6 }
#define ENCODER_RESOLUTION 4
#define UNUSED_PINS

/* RGB Light Configuration */

#define RGB_DI_PIN D1
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 13
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
