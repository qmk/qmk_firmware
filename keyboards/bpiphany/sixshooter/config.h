#pragma once


/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 3

/* Keyboard Matrix Assignments */
#define DIRECT_PINS { \
    { F7, F6, F1 }, \
    { F5, F4, F0 } \
}

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
