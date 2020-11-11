#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x4444
#define PRODUCT_ID      0x0003
#define DEVICE_VER      0x0001
#define MANUFACTURER    4pplet
#define PRODUCT         waffling60 Rev A
#define DESCRIPTION     A steezy keeb

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 11
// ROWS: Top to bottom, COLS: Left to right

#define MATRIX_ROW_PINS {D4,D1,C2,C4,C7,B2}
#define MATRIX_COL_PINS {D3,D0,D2,B6,B5,B4,B3,D6,D5,B0,B1}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 0

#define QMK_ESC_OUTPUT D3 // usually COL
#define QMK_ESC_INPUT D4 // usually ROW
