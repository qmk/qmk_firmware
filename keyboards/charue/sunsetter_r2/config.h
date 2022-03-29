// Copyright 2021 ILWrites (@ILWrites)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
// 0x4344 = CD for Charue Design
#define VENDOR_ID    0x4344
// 0x5335 = S2 for Sunsetter R2
#define PRODUCT_ID   0x5335
// 0x0001 = 1 for Base version
#define DEVICE_VER   0x0001
#define MANUFACTURER Charue Design
#define PRODUCT      Sunsetter R2

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 17

/*
 * Keyboard Matrix Assignments
 */
#define MATRIX_ROW_PINS { B3, B2, F4, F5, F6 }
#define MATRIX_COL_PINS { F0, F1, F7, B1, D0, D1, D2, D3, D5, D4, D6, D7, B4, B5, B6, C6, C7 }
#define UNUSED_PINS { B7 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define LED_CAPS_LOCK_PIN B0

#define RGB_DI_PIN E6
#ifdef RGB_DI_PIN
#    define RGBLED_NUM 10
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_RGB_TEST
#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5


/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
