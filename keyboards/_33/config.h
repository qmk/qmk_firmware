#pragma once

#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */ 
#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x6a50
#define DEVICE_VER 0x0001
#define MANUFACTURER tominabox1
#define PRODUCT _33
#define DESCRIPTION "Itty Bitty otho 30"

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 10

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
#define MATRIX_ROW_PINS { F5, F6, C6, D0 }
#define MATRIX_COL_PINS { B4, B5, D5, F7, B1, F4, B3, D7, B0, B2 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION ROW2COL

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

// #define RGB_DI_PIN B6
// #define RGBLED_NUM 3
// #define RGBLIGHT_SLEEP

#define TAPPING_TERM 200
