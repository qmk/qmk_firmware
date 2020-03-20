#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define MANUFACTURER    1up Keyboards
#define PRODUCT         Sweet16
#define DESCRIPTION     4x4 grid

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 4

/* number of backlight levels */
#define BACKLIGHT_LEVELS 10

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
