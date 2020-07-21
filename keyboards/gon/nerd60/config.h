#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6FD7
#define DEVICE_VER      0x0001
#define MANUFACTURER    GON
#define PRODUCT         NerD 60
#define DESCRIPTION     QMK port for the GON NerD 60 PCB

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 8

/* backlight */
#define BACKLIGHT_PIN B7
#define BACKLIGHT_LEVELS 3

/* matrix pins */
#define MATRIX_ROW_PINS { B4, E2, F4, F7, F1, F6, C6, F5, D7, C7 }
#define MATRIX_COL_PINS { E6, B0, B1, B2, B3, F0, D0, D5 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
