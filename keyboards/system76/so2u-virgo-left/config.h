#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    System76
#define PRODUCT         Virgo
#define DESCRIPTION     Virgo Keyboard

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 7

/* key matrix pins */
#define MATRIX_ROW_PINS { A3, A2, A1, A0, D15, D14 }
#define MATRIX_COL_PINS { D2, D3, D4, D5, D6, D7, D8 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#endif // CONFIG_H
