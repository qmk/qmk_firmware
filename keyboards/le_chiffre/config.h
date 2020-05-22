#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0xD645
#define DEVICE_VER 0x0001
#define MANUFACTURER tominabox1
#define PRODUCT Le Chiffre

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
#define MATRIX_ROW_PINS { B3, D4, F1, C6 }
#define MATRIX_COL_PINS { F4, F5, B0, B2, B1, B4, D7, C7, D2, F7 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION ROW2COL

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Define encoder pads */
#define ENCODERS_PAD_A { D5 }
#define ENCODERS_PAD_B { D3 }

/* #define RGB_DI_PIN F0
   #define RGBLED_NUM 1  */
