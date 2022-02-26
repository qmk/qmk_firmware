#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x4B50
#define PRODUCT_ID      0x1141
#define DEVICE_VER      0x0002
#define MANUFACTURER    KP Republic
#define PRODUCT         BM40V2
#define DESCRIPTION     BM40V2 RGB keyboard

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 12

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
#define MATRIX_ROW_PINS { D7, F7, F6, F5 }
#define MATRIX_COL_PINS { B2, B3, D5, D3,D2, B7, F0, B4, B5, B6, C6, C7, } 
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION ROW2COL
#define USB_POLLING_INTERVAL_MS 1

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
//rgb light setting
#define RGBLIGHT_LIMIT_VAL 150
#define RGBLED_NUM          6
#define RGB_DI_PIN          B0
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_MOOD
#define RGBLIGHT_HUE_STEP   8
#define RGBLIGHT_SAT_STEP   8
#define RGBLIGHT_VAL_STEP   8

#    define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#    define RGB_DISABLE_WHEN_USB_SUSPENDED true // turn off effects when suspended
#    define RGB_MATRIX_KEYPRESSES
#    define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#    define DISABLE_RGB_MATRIX_BAND_SAT
#    define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#    define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#    define DISABLE_RGB_MATRIX_RAINDROPS
#    define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#    define DRIVER_ADDR_1 0b1010000
#    define DRIVER_COUNT 2
#    define DRIVER_1_LED_TOTAL 47
#    define DRIVER_LED_TOTAL DRIVER_1_LED_TOTAL

#if defined(RGB_MATRIX_ENABLE) && defined(RGBLIGHT_ENABLE)
    #define RGB_MATRIX_DISABLE_KEYCODES
#endif

#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
