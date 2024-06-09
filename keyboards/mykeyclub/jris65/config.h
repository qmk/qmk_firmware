#pragma once

// /* USB Device descriptor parameter */
// #define VENDOR_ID       0x5A4C
// #define PRODUCT_ID      0x4953
// #define DEVICE_VER      0x0001
// #define MANUFACTURER    ZL
// #define PRODUCT         IRIS65
// #define DESCRIPTION     IRIS65

/* key matrix size */
//#define MATRIX_ROWS 5
//#define MATRIX_COLS 16

/* key matrix pins */
//#define MATRIX_ROW_PINS { F7, F6, F5, B2, F4 }
//#define MATRIX_COL_PINS { B6, C6, C7, F1, F0, E6, B0, B1, B3, B7, D2, D1, D0, D7, B4, B5 }

//#define BOOTMAGIC_LITE_ROW 0
//#define BOOTMAGIC_LITE_COLUMN 0

#ifdef VIA_ENABLE
#define DYNAMIC_KEYMAP_LAYER_COUNT 5
#endif
