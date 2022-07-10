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

/* USB Device descriptor parameter */
#define VENDOR_ID       0xE0E0
#define PRODUCT_ID      0x0030
#define DEVICE_VER      0x0002
#define MANUFACTURER    Ergorius & Tooni Skyy
#define PRODUCT         PRKL30

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 10

/* prkl30 default pinout */
#define MATRIX_ROW_PINS { D4, C6, D7, E6 }
#define MATRIX_COL_PINS { B4, B5, F6, F5, F4, F7, B1, B3, B2, B6}
/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW
#define ENCODERS_PAD_A { D3 }
#define ENCODERS_PAD_B { D2 }
#define ENCODER_RESOLUTION 4
#define UNUSED_PINS

/* RGB Light Configuration */

#define RGB_DI_PIN D1
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 13
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
