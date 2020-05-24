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
#define MATRIX_ROW_PINS { F5, F4, F1, F0, B0, B1, B2, B3 }
#define MATRIX_COL_PINS { F6, F7, B6, B5, B4, D7, D6, D4, D5, C7, C6, D3, D2, D1}
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
