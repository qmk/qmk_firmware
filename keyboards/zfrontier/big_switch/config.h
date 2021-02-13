/*
Copyright 2020 zFrontier <carl.xia@zfrontier.com>

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
#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x0A01
#define DEVICE_VER 0x0005
#define MANUFACTURER zFrontier
#define PRODUCT Red Comet Big Switch

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 1

/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS { F0 }
#define MATRIX_COL_PINS { F1 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* RGB light config */
#define RGB_DI_PIN B6
#define RGBLED_NUM 4
#define RGBLIGHT_VAL_STEP 17
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_EFFECT_BREATHE_CENTER 2.0
#define RGBLIGHT_EFFECT_BREATHE_MAX 255

/* long tapping config */
#define TAPPING_TERM 500
