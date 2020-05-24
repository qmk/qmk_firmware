#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x1337
#define PRODUCT_ID      0x88b2
#define DEVICE_VER      0x0002
#define MANUFACTURER    PFU
#define PRODUCT         keyboard
#define DESCRIPTION     HHKB Lite 2

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 14

/* key matrix pins */
#define MATRIX_ROW_PINS { B3, B2, B1, B0, F0, F1, F4, F5 }
#define MATRIX_COL_PINS { B7, D0, D1, D2, D3, C6, C7, D5, D4, D6, D7, B4, B5, B6 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

/* prevent stuck modifiers */
#define PREVENT_STUCK_MODIFIERS

#endif
