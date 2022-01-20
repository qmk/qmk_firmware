/**
 * config.h
 *
 */
#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xDEAD
#define PRODUCT_ID      0x6585
#define DEVICE_VER      0x0001
#define MANUFACTURER    astro
#define PRODUCT         smk 60

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15
/* key matrix pins */
#define MATRIX_ROW_PINS { B0, F0, F1, F5, B2 }
#define MATRIX_COL_PINS { B4, B5, B6, C6, C7, F6, F7, F4, B1, B3, D0, D1, D2, D3, D5}
#define UNUSED_PINS
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

//rgb light setting
#define RGBLED_NUM      4
#define RGB_DI_PIN      E6
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
