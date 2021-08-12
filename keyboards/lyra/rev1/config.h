#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0x4443  //DC
#define PRODUCT_ID      0x4C43  //LC
#define DEVICE_VER      0x3031  //01
#define MANUFACTURER    Dom
#define PRODUCT         Lyra
#define DESCRIPTION     LyraKeyboard

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 10
#define MATRIX_COLS 7

// wiring of each half
#define MATRIX_ROW_PINS { D4, C6, D7, E6, B4, }
#define MATRIX_COL_PINS { B2, B3, B1, F7, F6, F5, F4, }

#define DIODE_DIRECTION COL2ROW

#define TAPPING_TERM 100
#define DEBOUNCE 5

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* communication between sides */
#define USE_SERIAL
#define SERIAL_USE_MULTI_TRANSACTION
#define SOFT_SERIAL_PIN D2

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

/* via stuff */