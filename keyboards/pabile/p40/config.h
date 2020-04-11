#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x1234
#define PRODUCT_ID      0x0000
#define DEVICE_VER      0x0001
#define MANUFACTURER    Pabile
#define PRODUCT         Pabile40 Keyboard
#define DESCRIPTION     4x10 staggered keyboard

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 10

/* pin-out
for PCB ver0.01 452019 */
#define MATRIX_ROW_PINS { F6, B3, B2, B6 }
#define MATRIX_COL_PINS { F4, F5, B5, B4, E6, D7, C6, D4, D0, D1 }
/*
for pro micro facing back of pcb
#define MATRIX_ROW_PINS { D4, E6, B4, B5 }
#define MATRIX_COL_PINS { D1, D0, B6, B2, B3, B1, F7, F6, F5, F4 }
*/
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/*
#define TAPPING_TERM 200
*/
#define RETRO_TAPPING
