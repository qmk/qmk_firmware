/*
Copyright 2019 bemeier

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
#define PRODUCT_ID 0x0000
#define DEVICE_VER 0x0002
#define MANUFACTURER Bemeier
#define PRODUCT bmek
#define DESCRIPTION Mechanical Keyboard

/* Keyboard Matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS \
        { B4, B5, D7, F5, F4 }
// V1:  { B7, B4, B6, D7, D4 }
#define MATRIX_COL_PINS \
        { F6, B0, B1, F7, C7, C6, B6, F1, B2, B3, D6, D3, D2, D1, D0 } 
// V1:  { F1, B0, B1, B2, B3, D0, D1, D2, C6, C7, F7, F6, F5, F4, B5 }
#define UNUSED_PINS \
    { D4, D5, F0, B7 }

#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN E6
#ifdef RGB_DI_PIN
   #define RGBLED_NUM 6
   #define RGBLIGHT_HUE_STEP 8
   #define RGBLIGHT_SAT_STEP 8
   #define RGBLIGHT_VAL_STEP 8
   #define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
#endif

#define DEBOUNCE 5
#define RETRO_TAPPING
#define TAPPING_TERM 100

#define FORCE_NKRO

#define DYNAMIC_MACRO_NO_NESTING
