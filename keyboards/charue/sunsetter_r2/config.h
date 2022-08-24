// Copyright 2022 Charue Design
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

/* Key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 17

/* Keyboard Matrix Assignment s*/
#define MATRIX_ROW_PINS { B3, B2, F4, F5, F6 }
#define MATRIX_COL_PINS { F0, F1, F7, B1, D0, D1, D2, D3, D5, D4, D6, D7, B4, B5, B6, C6, C7 }
#define UNUSED_PINS { B7 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define LED_CAPS_LOCK_PIN B0

/* RGB */
#define RGB_DI_PIN E6
#ifdef RGB_DI_PIN
#    define RGBLED_NUM 10
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

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
