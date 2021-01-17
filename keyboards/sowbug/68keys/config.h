// config.h

#pragma once

#include "config_common.h"

// USB Device descriptor parameter
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x8888
#define DEVICE_VER      0x0001
#define MANUFACTURER    Generic
#define PRODUCT         Keyboard
#define DESCRIPTION     Keyboard

// key matrix size
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

// key matrix pins
#define MATRIX_ROW_PINS { C14, C15, A0, A1, A2 }
#define MATRIX_COL_PINS { A3, A4, A5, A6, A7, B0, B1, B10, B11, B12, B13, B14, B15, A8, A9, A10 }
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
    #define RGB_MATRIX_KEYPRESSES
    #define DRIVER_LED_TOTAL (68)
    #define RGBLED_NUM (DRIVER_LED_TOTAL)
#endif
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 128
