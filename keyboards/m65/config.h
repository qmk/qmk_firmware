#pragma once

#include "config_common.h"

#define VENDOR_ID       0xBABA
#define PRODUCT_ID      0x6060
#define MANUFACTURER    m65
#define PRODUCT         keyboard

#define MATRIX_ROWS 5
#define MATRIX_COLS 13

#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE 5

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE

#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

#define PREVENT_STUCK_MODIFIERS
#define TAPPING_TOGGLE 2
