#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x1776
#define PRODUCT_ID      0x1776
#define DEVICE_VER      0x0001
#define MANUFACTURER    System76
#define PRODUCT         ortho_split_2u
#define DESCRIPTION     2U Split Ortho

/* key matrix size */
#define MATRIX_ROWS 12 // 6, but each side is separate
#define MATRIX_COLS 16

/* key matrix pins */
#define MATRIX_ROW_PINS { F4, F5, F6, F7, B1, B3 }
#define MATRIX_COL_PINS { D1, B5, D4, C6, D7, E6, B4 }
#define MATRIX_ROW_PINS_RIGHT { F4, F5, F6, F7, B1, B3 }
#define MATRIX_COL_PINS_RIGHT  { D3, D2, D1, B5, D4, C6, D7, E6, B4 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Settings for split keyboard */
#define MASTER_RIGHT               // Right half is the master, don't plug USB into left half
#define SOFT_SERIAL_PIN D0         // The halves communicate via serial on pin D0

#endif // CONFIG_H
