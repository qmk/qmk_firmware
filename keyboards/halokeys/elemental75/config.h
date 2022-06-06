 /* Copyright 2022 Halokeys
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
#define VENDOR_ID 0xEA0B
#define PRODUCT_ID 0xEA75
#define DEVICE_VER 0x0001
#define MANUFACTURER Halokeys
#define PRODUCT Elemental75


/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 15

#define MATRIX_ROW_PINS { A2, A3, A4, A5, A6, A7 }
#define MATRIX_COL_PINS { B2, B1, B0, B10, B11, B13, B14, B15, A8, A9, A14, A15, B3, B4, B7 }
#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE 5

#define ENCODERS_PAD_A { B6 }
#define ENCODERS_PAD_B { B5 }
#define ENCODER_RESOLUTION 2
#define TAP_CODE_DELAY 10 // tap_code function delay for register and unregister

#define RGB_DI_PIN A10
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 22
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_LIMIT_VAL 255
#define RGBLIGHT_SLEEP

//#define RGBLIGHT_DISABLE_KEYCODES

// Tap dance term declaration
#define TAPPING_TERM 300

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
