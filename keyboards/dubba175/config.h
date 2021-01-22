#pragma once

#include "config_common.h"

#define MANUFACTURER DrHigsby
#define PRODUCT Dubba175
#define VENDOR_ID 0x0420
#define PRODUCT_ID 0x0420
#define DEVICE_VER 0x0420

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 10

/* key matrix pins */
#define MATRIX_ROW_PINS { B1, B3, B2, B5 }
#define MATRIX_COL_PINS { D3, D2, D1, D0, D4, C6, D7, E6, B4, B6 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define COMBO_COUNT 8

#define COMBO_TERM 40