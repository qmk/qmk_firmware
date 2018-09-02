#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0C60
#define DEVICE_VER      0x00C6
#define MANUFACTURER    PeiorisBoards
#define PRODUCT         QC60
#define DESCRIPTION     Split 60% staggered keyboard

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 10
#define MATRIX_COLS 8

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)
