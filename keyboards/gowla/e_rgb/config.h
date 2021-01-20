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

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0007
#define DEVICE_VER      0x0001
#define MANUFACTURER    Gowla
#define PRODUCT         Gowla Macro eRGB

/* Matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 3

/* Pin-out */
#define MATRIX_ROW_PINS { D1, D0, D4 }
#define MATRIX_COL_PINS { B5, B4, E6 }
#define UNUSED_PINS

/* ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* RGB */
#define RGB_DI_PIN B6
#define RGBLED_NUM 3
#define RGBLIGHT_EFFECT_STATIC_LIGHT
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_LIMIT_VAL 225

/* Rotary Encoder*/
#define ENCODERS_PAD_A { B2 }
#define ENCODERS_PAD_B { B3 }
#define ENCODER_RESOLUTION 4

