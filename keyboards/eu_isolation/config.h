
#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0000
#define DEVICE_VER      0x0001
#define MANUFACTURER    TuckTuckFloof
#define PRODUCT         EU ISOlation
#define DESCRIPTION     A terrible fucking creation involving a quad iso macro pad

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 14

/* NIU Mini PCB default pin-out */
#define MATRIX_ROW_PINS { D2, D3, F1, F0 }
#define MATRIX_COL_PINS { D0, D1, D4, D6, D7, B4, B5, B6, C6, C7, F7, F6, F5, F4}
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
