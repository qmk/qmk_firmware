#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x6666
#define PRODUCT_ID      0x6666
#define DEVICE_VER      0x0001
#define MANUFACTURER    Pabile
#define PRODUCT         Pabile20
#define DESCRIPTION     5x4 Macropad

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 4

/* pin-out */
#define MATRIX_ROW_PINS { B3, B4, B5, D7, E6 }
#define MATRIX_COL_PINS { D0, B2, D4, B6 }
#define UNUSED_PINS
 
#define ENCODERS_PAD_A { F5, F7 }
#define ENCODERS_PAD_B { F6, B1 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW
