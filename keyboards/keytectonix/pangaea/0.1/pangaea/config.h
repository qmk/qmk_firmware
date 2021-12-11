#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID    0xFEED // temporary id for testing
#define PRODUCT_ID   0x0000 // temporary id for testing
#define DEVICE_VER   0x0001
#define MANUFACTURER pangaea keyboard project
#define PRODUCT      pangaea
#define DESCRIPTION  hid keyboard

/* key matrix size */
#define MATRIX_ROWS 5 * 2
#define MATRIX_COLS 6

/* key matrix pin assign */
#define MATRIX_ROW_PINS       { F4, F5, F6, F7, B6 }
#define MATRIX_COL_PINS       { D4, C6, D7, E6, B4, B5 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Split Keyboard specific options */
#define SOFT_SERIAL_PIN D3 /* serial communication pin */

/* RGB options */
#define RGB_DI_PIN D1

#ifndef RGBLED_NUM
  #define RGBLED_NUM 6
  #define RGBLIGHT_SPLIT
  #define RGBLED_SPLIT { 3, 3 }
#endif

// fix iPhone and iPad power adapter issue
// iOS device need lessthan 100
#define USB_MAX_POWER_CONSUMPTION 100

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
