/*
Copyright 2021 Studio Kestra

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
#define VENDOR_ID       0x7C10
#define MANUFACTURER    Studio Kestra
#define PRODUCT         Galatea

#define MATRIX_ROWS 12
#define MATRIX_COLS 9

#define MATRIX_COL_PINS { F0, F1, F4, F5, F6, F7, C7, B2, D5 }
#define MATRIX_ROW_PINS { D1, D0, B0, B7, E6, B3, B6, C6, D6, D7, B4, D3 }
#define DIODE_DIRECTION COL2ROW

#define LED_CAPS_LOCK_PIN B5
#define LED_SCROLL_LOCK_PIN D2
#define LED_PIN_ON_STATE 0

#if defined(KEYBOARD_studiokestra_galatea_rev2)
  #define RGB_DI_PIN D4
  #define RGBLED_NUM 24
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
  #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
   #define RGBLIGHT_EFFECT_BREATHING
   #define RGBLIGHT_EFFECT_RAINBOW_MOOD
   #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
   #define RGBLIGHT_EFFECT_SNAKE
   #define RGBLIGHT_EFFECT_KNIGHT
   #define RGBLIGHT_EFFECT_CHRISTMAS
   #define RGBLIGHT_EFFECT_STATIC_GRADIENT
   #define RGBLIGHT_EFFECT_RGB_TEST
   #define RGBLIGHT_EFFECT_ALTERNATING
// /*== customize breathing effect ==*/
//   /*==== (DEFAULT) use fixed table instead of exp() and sin() ====*/
   #define RGBLIGHT_BREATHE_TABLE_SIZE 256      // 256(default) or 128 or 64
//   /*==== use exp() and sin() ====*/
//   #define RGBLIGHT_EFFECT_BREATHE_CENTER 1.85  // 1 to 2.7
//   #define RGBLIGHT_EFFECT_BREATHE_MAX    255   // 0 to 255
#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Bootmagic Lite key configuration */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
