#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0000
#define DEVICE_VER      0x0001
#define MANUFACTURER    Swiftrax
#define PRODUCT         UnSplit
#define DESCRIPTION     40% keyboard with exposed SMD components

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 12

/* key matrix pins */
#define MATRIX_ROW_PINS { B6, D7, B5, B4 }
#define MATRIX_COL_PINS { D1, D2, D3, D5, D4, D6, C6, C7, F6, F5, F4, F1 }
#define UNUSED_PINS { B0, B1, B2, B3, B7, D0, E6, F7 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* number of backlight levels */

#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 0
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5
