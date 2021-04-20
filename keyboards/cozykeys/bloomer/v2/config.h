/*
Copyright 2021 Paul Ewing

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

// USB Device descriptor parameter
#define VENDOR_ID    0xFEED
#define PRODUCT_ID   0x1191
#define DEVICE_VER   0x0002
#define MANUFACTURER CozyKeys
#define PRODUCT      Bloomer

// Key matrix size
#define MATRIX_ROWS 6
#define MATRIX_COLS 15

// Keyboard Matrix Assignments
#define MATRIX_ROW_PINS { D0, D1, D3, D2, D4, B2 }
#define MATRIX_COL_PINS { F7, F6, F5, F4, F1, F0, B1, B4, C6, E6, B5, B6, B7, D6, C7 }
#define UNUSED_PINS
#define DIODE_DIRECTION COL2ROW

#ifdef RGBLIGHT_ENABLE
#define RGB_DI_PIN D7
#define RGBLED_NUM 12
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_LIMIT_VAL 255
#define RGBLIGHT_SLEEP
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_BREATHE_TABLE_SIZE    256
#define RGBLIGHT_EFFECT_BREATHE_CENTER 1.85
#define RGBLIGHT_EFFECT_BREATHE_MAX    255
#endif

// Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed
#define DEBOUNCE 5

// Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap
#define LOCKING_SUPPORT_ENABLE
// Locking resynchronize hack
#define LOCKING_RESYNC_ENABLE

