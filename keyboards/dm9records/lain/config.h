// Copyright 2022 Takuya Urakawa @hsgw (dm9records.com, 5z6p.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0x04D8
#define PRODUCT_ID 0xE8F4
#define DEVICE_VER 0x0001
#define MANUFACTURER Dm9Records
#define PRODUCT lain

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 13

/*
 * Keyboard Matrix Assignments
 */
#define MATRIX_ROW_PINS \
    { C6, D7, D6, D4 }
#define MATRIX_COL_PINS \
    { C7, F7, F6, F5, F4, F1, F0, B3, B2, B1, D2, D3, D5 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* LED Settings */
#define LED_NUM 3
#define LED_PINS \
    { B6, B5, B4 }

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#define DYNAMIC_KEYMAP_LAYER_COUNT 6
