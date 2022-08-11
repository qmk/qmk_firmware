/**
 * config.h
 */

#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 7
#define MATRIX_COLS 14

/* key matrix pins */
#define MATRIX_ROW_PINS { E6, F0, B7, C7, D3, B0, D1 }
#define MATRIX_COL_PINS { F1, F4, F5, F6, F7, B6, B5, B4, D7, D0, D2, D6, D4, D5 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN B3

#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 16
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_SLEEP
#define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_RGB
#endif
