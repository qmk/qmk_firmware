// Copyright 2024 lynton ivins (@stirrem)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

//#include "config.h"


/* Increase macro limit to 32 */

#define DYNAMIC_KEYMAP_MACRO_COUNT 32

/* lighting layers */

 #define RGBLIGHT_LAYERS
 #define WS2812_DI_PIN D0
 #define RGBLIGHT_LED_COUNT 15
 //#define RGBLED_NUM 15


/* all led features */
// #define RGBLED_NUM 14
//#define RGBLIGHT_LIMIT_VAL 200
//#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_STATIC_LIGHT
//#define RGBLIGHT_DEFAULT_ON true
//#define RGBLIGHT_DEFAULT_HUE 0
//#define RGBLIGHT_DEFAULT_SAT UINT8_MAX
//#define RGBLIGHT_DEFAULT_VAL RGBLIGHT_LIMIT_VAL
//#define RGBLIGHT_LAYERS
//#define RGBLIGHT_SLEEP

/*
 Feature disable options
 These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

/* key matrix size*/
//#define MATRIX_ROW_PINS { B6, B2, B3, B1, F7, F6 }
//#define MATRIX_COL_PINS { D3, D2, D1, D4, C6, D7, E6, B4 }
//#define UNUSED_PINS
