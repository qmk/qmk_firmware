// Copyright 2022 Jason Williams (@wilba)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "config_common.h"

// USB Device descriptor parameter
#define VENDOR_ID       0x6582 // wilba.tech
#define PRODUCT_ID      0x0031 // PCB #49
#define DEVICE_VER      0x0001
#define MANUFACTURER    wilba.tech
#define PRODUCT         wilba.tech WT65-D

// key matrix size
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

// Keyboard Matrix Assignments
#define MATRIX_ROW_PINS { E6, F0, F4, F6, F7 }
#define MATRIX_COL_PINS { F5, D5, D3, D2, B7, B0, B3, C7, C6, B6, B5, B4, D7, D6, D4 }
#define UNUSED_PINS
#define DIODE_DIRECTION COL2ROW

// Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed
#define DEBOUNCE 5

#define LED_CAPS_LOCK_PIN F1

// Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap 
#define LOCKING_SUPPORT_ENABLE

// Locking resynchronize hack
#define LOCKING_RESYNC_ENABLE