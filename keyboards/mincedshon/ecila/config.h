// Copyright 2022 mincedshon (@mincedshon)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

/*Bootmagic boot button, set to topmost, leftmost key */
#define BOOTMAGIC_LITE_ROW	0
#define BOOTMAGIC_LITE_COLUMN	0

/* encoder */
/* #define NUMBER_OF_ENCODERS 1 */
//#define ENCODERS_PAD_A { D3 }
//#define ENCODERS_PAD_B { D2 }
//#define ENCODER_RESOLUTION 1

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

/* key matrix pins */
#define MATRIX_ROW_PINS { E6, B3, B5, B4, D7 }
#define MATRIX_COL_PINS { B6, F7, F6, F5, F4, F1, F0, D6, B7, D0, D1, D2, D3, D5, D4 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5


//#define LED_NUM_LOCK_PIN  D4
//#define LED_CAPS_LOCK_PIN D6

#define RGB_DI_PIN B0
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
#define RGBLED_NUM 6
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_LIMIT_VAL 150
#define RGBLIGHT_SLEEP
