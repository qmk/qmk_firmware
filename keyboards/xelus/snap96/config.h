#pragma once

#include "config_common.h"

// USB Device descriptor parameter
#define VENDOR_ID       0x5845 // XE
#define PRODUCT_ID      0x5396 // Snap96
#define DEVICE_VER      0x0001
#define MANUFACTURER    Xelus
#define PRODUCT         Snap96
#define DESCRIPTION     Snap96

// key matrix size
#define MATRIX_ROWS 12
#define MATRIX_COLS 10

// key matrix pins
#define MATRIX_ROW_PINS { B2, B1, B0, C7, F6, F7, B3, D1, D2, D7, B6, C6 }
#define MATRIX_COL_PINS { E6, D5, B7, D0, F5, D3, B4, B5, D4, D6 }
#define UNUSED_PINS

// COL2ROW or ROW2COL
#define DIODE_DIRECTION COL2ROW

// Set 0 if debouncing isn't needed
#define DEBOUNCE 5

// Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap
#define LOCKING_SUPPORT_ENABLE
// Locking resynchronize hack
#define LOCKING_RESYNC_ENABLE

// 3 layers or else it will not fit in EEPROM
#define DYNAMIC_KEYMAP_LAYER_COUNT 3
