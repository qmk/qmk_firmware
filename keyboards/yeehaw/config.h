/* Copyright 2021 Caleb Lightfoot
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
#define VENDOR_ID       0x5351
#define PRODUCT_ID      0x5458
#define DEVICE_VER      0x0100
#define MANUFACTURER    squashkb
#define PRODUCT         Yeehaw


/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 14

/* Keyboard Matrix Assignments */
#define DIRECT_PINS { \
{ D2, D4, C6, E6, F5, B1, D3, D7, B4, F6, B3, B5, F7, F4 } \
}

#define ENCODERS_PAD_A { D1 }
#define ENCODERS_PAD_B { D0 }

#define RGB_DI_PIN B2
#ifdef RGB_DI_PIN
  #define RGBLED_NUM 7
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
  #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
  /*== all animations enable ==*/
  #define RGBLIGHT_ANIMATIONS
#endif
