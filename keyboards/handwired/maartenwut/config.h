#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xBB80
#define PRODUCT_ID      0x050D
#define DEVICE_VER      0x0001
#define MANUFACTURER    Maartenwut
#define PRODUCT         Ortho
#define DESCRIPTION     Handwired ortholinear keyboard

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
#define MATRIX_ROW_PINS { D4, D0, D1, D2, D3 }
#define MATRIX_COL_PINS { C6, D7, E6, B4, B5, B6, B7, D6, F0, F1, F4, F5, F6, F7 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCING_DELAY 5

#define QMK_ESC_OUTPUT C6 // usually COL
#define QMK_ESC_INPUT D0 // usually ROW

#endif