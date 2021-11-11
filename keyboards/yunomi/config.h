// Copyright 2021 Austin Wang (@Dafondo)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID    0xFEED
#define PRODUCT_ID   0x0000
#define DEVICE_VER   0x0001
#define MANUFACTURER Google
#define PRODUCT      yunomi

/* key matrix size */
#define MATRIX_ROWS 11
#define MATRIX_COLS 11

/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS { B0, B1, B2, B3, B4, D0, D1, D2, D3, D4, D5 }
#define MATRIX_COL_PINS { D0, D1, D2, D3, D4, D5, B0, B1, B2, B3, B4 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
