#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0C61
#define DEVICE_VER      0x00C6
#define MANUFACTURER    PeiorisBoards
#define PRODUCT         Ixora Rev1
#define DESCRIPTION     6key Macropad

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 6

#define MATRIX_ROW_PINS { A0 }
#define MATRIX_COL_PINS { B4, A15, B3, A1, B6, B5 }

/* COL2ROW, ROW2COL, or CUSTOM_MATRIX */
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 0
