#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x6666
#define PRODUCT_ID      0x6669
#define DEVICE_VER      0x0001
#define MANUFACTURER    Pabile
#define PRODUCT         P40 Ortho Keyboard
#define DESCRIPTION     4x10 staggered keyboard

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 10

/* pin-out */
#define MATRIX_ROW_PINS { D1, D0, F4, F5 }
#define MATRIX_COL_PINS { D4, C6, D7, E6, B4, B2, B3, B1, F7, F6 }

#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW