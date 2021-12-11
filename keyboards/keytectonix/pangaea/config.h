#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID    0x1209
#define PRODUCT_ID   0x4655
#define DEVICE_VER   0x0001
#define MANUFACTURER Keytectonix
#define PRODUCT      Pangaea
#define DESCRIPTION  Parts adjustable keyboard

/* key matrix size */
#define MATRIX_ROWS 5 * 2 //split keyboard
#define MATRIX_COLS 4 * 2 //duplex matrix

/* key matrix pin assign */
#define MATRIX_ROW_PINS { B4, B5, F4, F5, F6 }
#define MATRIX_COL_PINS { D4, C6, D7, E6 }

/* COL2ROW, ROW2COL*/
// #define DIODE_DIRECTION COL2ROW

#define ENCODERS_PAD_A {D1}
#define ENCODERS_PAD_B {D0}

/* Split Keyboard specific options */
#define SOFT_SERIAL_PIN D2 /* serial communication pin */

/* RGB options */
#define RGB_DI_PIN D3

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
