#pragma once

#include "../config.h"
#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 16
#define MATRIX_COLS  8 

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
//Passed through the port multipler, so 4 pins =16
#define MATRIX_ROW_PINS { F0, F1, F2, F3, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN }

// May be upside down. 
#define MATRIX_COL_PINS { B0,B1, B2, B3, B4, B5, B6, B7 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW
