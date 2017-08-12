#ifndef ERGODOX_ERGODONE_CONFIG_H
#define ERGODOX_ERGODONE_CONFIG_H

#include "../config.h"

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x1307
#define DEVICE_VER      0x0001
#define MANUFACTURER    ErgoDone
#define PRODUCT         ErgoDone
#define DESCRIPTION     QMK keyboard firmware for ErgoDone

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 14

/* number of backlight levels */
#define BACKLIGHT_LEVELS 3

#define LED_BRIGHTNESS_LO       15
#define LED_BRIGHTNESS_HI       255

/* fix space cadet rollover issue */
#define DISABLE_SPACE_CADET_ROLLOVER

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

#define PREVENT_STUCK_MODIFIERS

#define USB_MAX_POWER_CONSUMPTION 500

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION
//#define DEBUG_MATRIX_SCAN_RATE

#endif
