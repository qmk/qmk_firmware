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
#define MATRIX_ROW_PINS { D7, E0, E1, C0, C6, F6, D4, D2, D3, D0, B7, D1, E6, B4, B2 }
#define MATRIX_COL_PINS { E7, F0, F7, B1, B3, B0, D5 }


/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define IGNORE_MOD_TAP_INTERRUPT

// The Teensy 2++ consumes about 60 mA of current at its full speed of 16 MHz as
// per https://www.pjrc.com/teensy/low_power.html
#define USB_MAX_POWER_CONSUMPTION 100
