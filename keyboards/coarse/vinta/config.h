#pragma once


/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

#define MATRIX_ROW_PINS { A10, A9, B0, A7, A6 }
#define MATRIX_COL_PINS { A5, A4, A3, A2, A1, A0, F1, F0, B7, B6, B5, B4, B3, A15, A14, A13 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* If defined, GRAVE_ESC will always act as ESC when CTRL is held.
 * This is userful for the Windows task manager shortcut (ctrl+shift+esc).
 */
// #define GRAVE_ESC_CTRL_OVERRIDE
