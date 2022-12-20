/* 
Copyright 2022 Horns Lyn (@hornslyn)
SPDX-License-Identifier: GPL-2.0-or-later */
#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 15

/* key matrix pins */
#define MATRIX_ROW_PINS { B7, D0, D1, D2, D3, D5 }
#define MATRIX_COL_PINS { D4, D6, D7, B4, B5, B6, C6, C7, F7, F6, F5, F4, F1, F0, E6 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* number of backlight levels */
#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 3
#endif

/* encoder definitions */
#ifdef ENCODER_ENABLE
#define ENCODERS_PAD_A { B2 }
#define ENCODERS_PAD_B { B1 }
#endif

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define RGB_DI_PIN B3

#ifdef RGB_DI_PIN
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
#define RGBLED_NUM 1
#define RGBLIGHT_LAYERS
#define RGBLIGHT_LED_MAP { 0, 1 }
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_LIMIT_VAL 180
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
#endif
