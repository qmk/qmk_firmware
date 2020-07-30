#pragma once

/* key matrix size */
#define MATRIX_ROWS 6
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

#define MATRIX_ROW_PINS { B12, B13, B14, B15, A3, B9 }
#define MATRIX_COL_PINS { B11, B10, B1, A10, B5, B4, B3, A15, A2, A1, A0, C15, C14, C13 }
#define UNUSED_PINS

