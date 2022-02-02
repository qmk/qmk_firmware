#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x23F8
#define PRODUCT_ID      0x10p4
#define DEVICE_VER      0
#define MANUFACTURER    evancook.audio
#define PRODUCT         tenpad

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 5

/* key matrix pins */

#define MATRIX_ROW_PINS {D0, D1}
#define MATRIX_COL_PINS {F4, F5, F6, F7, B1}

#define UNUSED_PINS {B3, B2, B6, B7, D5, C7, F1, F0, B4, E6, D7, C6, D4 }

