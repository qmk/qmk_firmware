// Copyright 2022 Alexander Lozyuk (@keyzog)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once


/* USB Device descriptor parameter */
#define VENDOR_ID       0x4C41 // "LA" Lozyuk Alexander
#define PRODUCT_ID      0x0001
#define DEVICE_VER      0x0001
#define MANUFACTURER    keyzog
#define PRODUCT         Kapl Keyboard

/* key matrix size */
/* Rows are doubled up */
#define MATRIX_ROWS 10
#define MATRIX_COLS 7

// wiring of each half
#define MATRIX_ROW_PINS { C6, D7, E6, B4, B5 }
#define MATRIX_COL_PINS { F5, F6, F7, B1, B3, B2, B6 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5


/* Serial settings */
#define USE_SERIAL

/* serial.c configuration for split keyboard */
#define SOFT_SERIAL_PIN D2

/* Select hand configuration */
#define MASTER_LEFT

#define RGB_DI_PIN D4
#define RGBLED_NUM 88
#define RGBLED_SPLIT { 44, 44 }
#define RGBLIGHT_SPLIT
#define RGBLIGHT_LIMIT_VAL 120 // limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash.

#define DRIVER_LED_TOTAL 88
#define RGB_MATRIX_SPLIT { 44, 44 }
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 120 // limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash.
#define SPLIT_TRANSPORT_MIRROR

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
