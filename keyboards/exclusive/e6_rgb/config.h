/**
 * config.h
 *
 */
#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14
/* key matrix pins */
#define MATRIX_ROW_PINS { F1, F4, F5, F6, D6 }
#define MATRIX_COL_PINS { D7, B4, B5, B6, C6, C7, F7, F0, B0, B1, D2, D3, B3, B2 }
#define UNUSED_PINS
#define DIODE_DIRECTION COL2ROW

//rgb light setting
#define RGBLED_NUM      6
#define RGB_DI_PIN      B7
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8

#define DRIVER_ADDR_1 0b1010000

#define DRIVER_COUNT 1
#define DRIVER_LED_TOTAL 63
