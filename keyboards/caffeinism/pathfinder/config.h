#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xCAFF
#define PRODUCT_ID      0xF103
#define DEVICE_VER      0x0001
#define MANUFACTURER    caffeinism
#define PRODUCT         pathfinder

/* 
    key matrix size
    Haha QMK has set the maximum value of one MATRIX line to 32. Let's only input up to 32 pins.
*/
#define MATRIX_ROWS 31
#define MATRIX_COLS 31

/* key matrix pins */
#define MATRIX_ROW_PINS { A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, B0, B1, B2, B3, B4, B5, B6, B7, B8, B9, B10, B11, B12, B13, B14, B15 }
#define MATRIX_COL_PINS { A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, B0, B1, B2, B3, B4, B5, B6, B7, B8, B9, B10, B11, B12, B13, B14, B15 }
#define MATRIX_ALL_PINS_STRING { "A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8", "A9", "A10", "A11", "A12", "A13", "A14", "A15", "B0", "B1", "B2", "B3", "B4", "B5", "B6", "B7", "B8", "B9", "B10", "B11", "B12", "B13", "B14", "B15" }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 0

/* main loop timeout ms */
#define LOOP_TIMEOUT 60000
