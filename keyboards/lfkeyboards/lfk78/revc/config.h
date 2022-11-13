#pragma once

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
#define MATRIX_ROW_PINS { D2, D3, D4, D5, D6 }
#define MATRIX_COL_PINS { A0, A1, A2, A3, A4, A5, A6, A7, E6, E7, F0, F1, F2, F3, C0, C1, C2, C3 }

#define RGBLED_NUM 27
