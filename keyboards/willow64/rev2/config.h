/*
Copyright 2019 @haswellep

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

#define VENDOR_ID 0xBB01
#define PRODUCT_ID 0x0011
#define DEVICE_VER 0x0001
#define MANUFACTURER @haswellep
#define PRODUCT Willow64_r02
#define DESCRIPTION Willow 64 rev02
#define MATRIX_ROWS 10
#define MATRIX_COLS 8
#define MATRIX_ROW_PINS { D4, C6, D7, E6, B4}
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, B2, B6}
#define UNUSED_PINS
#define DIODE_DIRECTION COL2ROW
#define MASTER_LEFT
#define SOFT_SERIAL_PIN D2  // or D1, D2, D3, E6
#define USE_SERIAL
#define SELECT_SOFT_SERIAL_SPEED 1
#define DEBOUNCE 5
#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE
#define RGBLED_SPLIT {29, 35}
#define RGB_DI_PIN D3
#define RGBLED_NUM 64
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_LIMIT_VAL 110 /* The maximum brightness level */
#define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
#define RGBLIGHT_ANIMATIONS

