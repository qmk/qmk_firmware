/*
Copyright 2021 0xCB - Conor Burns

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
// clang-format off

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 3

/* Keyboard Matrix Assignments */
#define DIRECT_PINS { \
    { D2, D4, F4 }, \
    { D7, B1, B3 }, \
    { E6, B4, B2 } \
}
#define TAP_CODE_DELAY 10
#define ENCODER_RESOLUTION 4
#define ENCODERS_PAD_A { F6 }
#define ENCODERS_PAD_B { F5 }

#define BACKLIGHT_PIN B5
#define BACKLIGHT_BREATHING
#define BACKLIGHT_LEVELS 7

#define RGB_DI_PIN D3
#ifdef RGB_DI_PIN
  #define RGBLED_NUM 4
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
  #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
  #define RGBLIGHT_ANIMATIONS /* comment this and uncomment the lines below to save space */
  // #define RGBLIGHT_EFFECT_BREATHING
  // #define RGBLIGHT_EFFECT_SNAKE
  // #define RGBLIGHT_EFFECT_STATIC_GRADIENT
  // #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
  // #define RGBLIGHT_EFFECT_RAINBOW_MOOD
  /* default setup after eeprom reset */
  #define RGBLIGHT_DEFAULT_MODE RGBLIGHT_EFFECT_BREATHING + 2
  #define RGBLIGHT_DEFAULT_HUE 152
  #define RGBLIGHT_DEFAULT_SAT 232
  #define RGBLIGHT_DEFAULT_VAR 255
  #define RGBLIGHT_DEFAULT_SPD 2
#endif
// clang-format on

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
/* Oled Size */
#define OLED_DISPLAY_128X64
#define OLED_FONT_END 255
#define OLED_FONT_H "gfxfont.c"

/* QMK DFU */
#define QMK_LED B0
