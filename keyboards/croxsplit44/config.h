/*
Copyright 2021 Samux6146

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

#define VENDOR_ID       0xB62C
#define PRODUCT_ID      0x6146
#define DEVICE_VER      0x0001
#define MANUFACTURER    Samux6146
#define PRODUCT         splitcustom44

#define MATRIX_ROWS 4
#define MATRIX_COLS 12
#define MATRIX_ROW_PINS { D4, D5, D6, D7 }
#define MATRIX_COL_PINS { B6, B5, B4, D2, C0, C1, F5, F4, F3, F2, F1, F0 }

#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN C4
#ifdef RGB_DI_PIN
    #define RGBLED_NUM 42
    #define RGBLIGHT_HUE_STEP 8
    #define RGBLIGHT_SAT_STEP 8
    #define RGBLIGHT_VAL_STEP 8
    #define RGBLIGHT_SLEEP 
    #define RGBLIGHT_ANIMATIONS

#endif