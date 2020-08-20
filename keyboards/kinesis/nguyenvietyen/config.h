#pragma once

/* USB Device descriptor parameter */
#define PRODUCT_ID 0x6060
#define DEVICE_VER 0x0003

/* key matrix size */
#define MATRIX_ROWS 16
#define MATRIX_COLS 8

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
// Passed through the port multipler, so 4 pins =16
#define MATRIX_ROW_PINS { D0, D1, D2, D3 }
#define MATRIX_COL_PINS { B6, B2, B3, B1, F7, F6, F5, F4 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW
