// Copyright 2021 Ll3macorn (@ll3macorn)
// SPDX-License-Identifier: GPL-2.0-or-later
#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x1234
#define PRODUCT_ID      0x2949
#define DEVICE_VER      0x0001
#define MANUFACTURER    Ll3macorn
#define PRODUCT         BongoPad
#define DESCRIPTION     BongoPad
#define NO_ACTION_TAPPING

#define RGB_DI_PIN E6
#define RGBLED_NUM 6




/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 3

/* key matrix pins */
#define MATRIX_ROW_PINS { F7, D7, C6, D4 }
#define MATRIX_COL_PINS { F4, F5, F6 }
#define UNUSED_PINS


/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define ENCODERS_PAD_A { B1 }
#define ENCODERS_PAD_B { B3 }
#define LAYER_STATE_8BIT
#define NO_ACTION_ONESHOT


/* number of backlight levels */

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 0

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

/* prevent stuck modifiers */
#define PREVENT_STUCK_MODIFIERS

#endif