/* Copyright 2020 David Dejaeghere
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
#define VENDOR_ID       0x4D53
#define PRODUCT_ID      0x0002
#define DEVICE_VER      0x0002
#define MANUFACTURER    Mech Studio
#define PRODUCT         UD_40 Ortholinear

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 12

// ROWS: Top to bottom, COLS: Left to right

#define MATRIX_ROW_PINS {C2,B4,B5,B6}
#define MATRIX_COL_PINS {C5,D0,B3,B2,B1,B0,D6,D5,D4,D3,D2,D1}
#define UNUSED_PINS {C4,C6,C7}

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN B7
 #ifdef RGB_DI_PIN
   #define RGBLED_NUM 10
   #define RGBLIGHT_HUE_STEP 8
   #define RGBLIGHT_SAT_STEP 8
   #define RGBLIGHT_VAL_STEP 8
   #define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
   #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
// /*== all animations enable ==*/
   #define RGBLIGHT_ANIMATIONS
 #endif

/* set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

#define QMK_ESC_OUTPUT F0 // usually COL
#define QMK_ESC_INPUT B7 // usually ROW
