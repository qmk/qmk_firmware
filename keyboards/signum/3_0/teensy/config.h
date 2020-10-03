#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    qmkbuilder
#define PRODUCT         keyboard
#define DESCRIPTION     Keyboard

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 12

/* key matrix pins */
#define MATRIX_ROW_PINS { B0, B3, F6, C7 }
#define MATRIX_COL_PINS { C6, D2, B7, D3, D0, F7, F5, B6, B5, B4, D1, D7 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define LEADER_TIMEOUT 300
#define LEADER_PER_KEY_TIMING 300
#define TAPPING_TERM 500
#define IGNORE_MOD_TAP_INTERRUPT

#endif
