/*
Copyright 2021 Ross Montsinger <ross@montsinger.net>

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
#define VENDOR_ID       0x524D
#define PRODUCT_ID      0x0002
#define DEVICE_VER      0x0001
#define MANUFACTURER    Montsinger
#define PRODUCT         Trio Rev. 1

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 1

/* Keyboard Matrix Assignments */
#define DIRECT_PINS { \
    { D3 }, \
    { C6 }, \
    { B4 } \
}

#define ENCODERS_PAD_A { F5, B3, B6 }
#define ENCODERS_PAD_B { D1, E6, B5 }


/*#define RGB_DI_PIN D7
#ifdef RGB_DI_PIN
  #define RGBLED_NUM 4
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  */
  //#define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
  //#define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
  /*== all animations enable ==*/
  //#define RGBLIGHT_ANIMATIONS
//#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
