// Copyright 2022 Cable Car Designs (@westfoxtrot)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 10

#define MATRIX_ROW_PINS { B0, F1, F5, F6, F7, D1, F4, D4, C6, C7 }
#define MATRIX_COL_PINS { D6, D7, B4, B5, B6, B7, B3, B2, B1, F0 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL, or CUSTOM_MATRIX */
#define DIODE_DIRECTION COL2ROW

#define BACKLIGHT_BREATHING
#define BACKLIGHT_LEVELS 5

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define BACKLIGHT_PIN D0

#define RGB_DI_PIN D5
#ifdef RGB_DI_PIN
   #define RGBLED_NUM 3
   #define RGBLIGHT_HUE_STEP 12
   #define RGBLIGHT_SAT_STEP 25
   #define RGBLIGHT_VAL_STEP 12
   #define RGBLIGHT_LIMIT_VAL 255
   #define RGBLIGHT_SLEEP
   #define RGBLIGHT_EFFECT_BREATHING
   #define RGBLIGHT_EFFECT_RAINBOW_MOOD
   #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
   #define RGBLIGHT_EFFECT_SNAKE
   #define RGBLIGHT_EFFECT_KNIGHT
   #define RGBLIGHT_EFFECT_CHRISTMAS
   #define RGBLIGHT_EFFECT_STATIC_GRADIENT
   #define RGBLIGHT_EFFECT_RGB_TEST
   #define RGBLIGHT_EFFECT_ALTERNATING
   #define RGBLIGHT_EFFECT_TWINKLE
#endif
