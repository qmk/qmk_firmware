#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0x6400
#define PRODUCT_ID      0x2371
#define DEVICE_VER      0x0001
#define MANUFACTURER    Bachoo
#define PRODUCT         Nemui
#define DESCRIPTION     Nemui Keyboard

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

#define MATRIX_COL_PINS { B2, B1, B0, B10, B11, A7, B12, B13, B14, A10, A9, A8, B7, B8, B9 }
#define MATRIX_ROW_PINS { A3, A4, A5, A6, A2 }
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

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
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION
