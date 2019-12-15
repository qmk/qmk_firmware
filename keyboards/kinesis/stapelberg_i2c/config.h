#ifndef STAPELBERG_CONFIG_H
#define STAPELBERG_CONFIG_H

#include "../config.h"

/* USB Device descriptor parameter */
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0002

/* key matrix size */
#define MATRIX_ROWS 15
#define MATRIX_COLS  7

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
#define MATRIX_ROW_PINS { F6, F7, D2, D3, D4, D5, D6, D7, C0, C1, C2, C3, C4, C5, C6 }
#define MATRIX_COL_PINS { B0, B1, B2, B3, B4, B5, B6 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW


/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

#define IGNORE_MOD_TAP_INTERRUPT

#endif
