#pragma once 

#include "config_common.h" 

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0002
#define DEVICE_VER      0x0001
#define MANUFACTURER    Kingly_keys
#define PRODUCT         The_RoPro
#define DESCRIPTION     Keyboard

 /* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 13

 /* key matrix pins */
#define MATRIX_ROW_PINS { F4, F5, F6, F7, B1, F1, }
#define MATRIX_COL_PINS { F0, D1, D0, D4, C6, D7, E6, B4, B5, B3, B2, B6, D2 }
#define UNUSED_PINS

 /* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

 /* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

 /* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

 /* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
