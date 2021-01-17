// config.h

#pragma once

#include "config_common.h"

// USB Device descriptor parameters
#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x8889
#define DEVICE_VER 0x0001
#define MANUFACTURER Mike Tsao
#define PRODUCT ANSI TKL
#define DESCRIPTION A keyboard

// key matrix size
#define MATRIX_ROWS 6
#define MATRIX_COLS 17

// key matrix pins
#define MATRIX_ROW_PINS \
    { C14, C15, A0, A1, A2, A3 }
#define MATRIX_COL_PINS \
    { A4, A5, A6, A7, B0, B1, B10, B11, B12, B13, B14, B15, A8, A9, A10, A15, B3 }
#define UNUSED_PINS

// COL2ROW or ROW2COL
#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN B9
// Want backlighting and RGB Matrix patterns? See the note in the readme,
// apply the patches, and then uncomment the line below as well as the ones
// in rules.mk.
//
// #define BACKLIGHT_PIN rgb_matrix
#ifdef RGB_DI_PIN
#    define RGB_MATRIX_KEYPRESSES
#    define DRIVER_LED_TOTAL (87)
#    define RGBLED_NUM (DRIVER_LED_TOTAL)
#endif
