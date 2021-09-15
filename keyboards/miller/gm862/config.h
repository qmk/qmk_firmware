#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x4B42
#define PRODUCT_ID      0x0223
#define DEVICE_VER      0x0001
#define MANUFACTURER    MILLER
#define PRODUCT         GM862

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14
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
#define MATRIX_ROW_PINS {F0, F1, F4, F5, B4}
#define MATRIX_COL_PINS {B5, B6, C6, C7, F7, F6, B0, B1, B2, B3, B7, D2, D3, D5 }
#define UNUSED_PINS
/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 3
#ifdef RGB_MATRIX_ENABLE
#    define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#    define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#    define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#    define DISABLE_RGB_MATRIX_BAND_SAT
#    define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#    define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#    define DISABLE_RGB_MATRIX_SPLASH
#    define DISABLE_RGB_MATRIX_MULTISPLASH
#    define DISABLE_RGB_MATRIX_SOLID_SPLASH
#    define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH
#    define DISABLE_RGB_MATRIX_DIGITAL_RAIN
#    define DRIVER_ADDR_1 0b1010000
#    define DRIVER_ADDR_2 0b1010000 // this is here for compliancy reasons.
#    define DRIVER_COUNT 2
#    define DRIVER_1_LED_TOTAL 62
#    define DRIVER_LED_TOTAL DRIVER_1_LED_TOTAL
#endif
