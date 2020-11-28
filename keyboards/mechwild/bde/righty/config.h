#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x6D77 // mw = "MechWild"
#define PRODUCT_ID      0x1702
#define DEVICE_VER      0x0201
#define MANUFACTURER    MechWild
#define PRODUCT         BDE Righty
#define DESCRIPTION     41-key ortholinear 30% with numpad

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 14

/* key matrix pins */
#define MATRIX_ROW_PINS { F4, F5, D3}
#define MATRIX_COL_PINS { B4, B5, E6, C6, D4, D0, F4, F5, F6, B6, B3, B2, B1, F7}
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* number of backlight levels */
/* BDE v2.1 has no LEDs */
// #define BACKLIGHT_PIN D2
#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 3
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

