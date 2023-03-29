#pragma once


/*
 * Keyboard Matrix Assignments
*/
#define MATRIX_ROW_PINS { C13, B2, B1, A4, A3 }
#define MATRIX_COL_PINS { A6, A7, B0, A9, A8, A14, A15, B3, B4, B5, B8, B7, B6, B9 }

/* COL2ROW, ROW2COL, or CUSTOM_MATRIX */
#define DIODE_DIRECTION COL2ROW

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define SLEEP_LED_GPT_DRIVER GPTD1
