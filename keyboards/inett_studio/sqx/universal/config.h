/**
 * config.h
 *
 */
#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x694E  //'iN'
#define PRODUCT_ID      0x5336  //'S6'
#define DEVICE_VER      0x0001
#define MANUFACTURER    iNETT Studio
#define PRODUCT         SQUARE.X
#define DESCRIPTION     60% keyboard from the Square series

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14
#define MATRIX_ROW_PINS { F0, F1, F4, B7, D6}
#define MATRIX_COL_PINS { C7, C6, B6, B5, B4, F7, F6, F5, E6, B0, D2, D4, D5, D3 }
#define UNUSED_PINS
#define DIODE_DIRECTION ROW2COL

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


//rgb light setting
#define RGBLIGHT_LIMIT_VAL 128
#define RGBLED_NUM          18
#define RGB_DI_PIN          D7
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP   8
#define RGBLIGHT_SAT_STEP   8
#define RGBLIGHT_VAL_STEP   8

//rgb matrix setting
#define DRIVER_1_LED_TOTAL 36
#define DRIVER_2_LED_TOTAL 36
#define DRIVER_ADDR_1 0b1110100
#define DRIVER_ADDR_2 0b1110111
#define DRIVER_COUNT 2
#define DRIVER_LED_TOTAL (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)
