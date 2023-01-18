// Copyright 2023 Laneware Peripherals
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* key matrix pins */
#define MATRIX_ROW_PINS { E6, B7, D0, D1, D2, B1 }
#define MATRIX_COL_PINS { D3, D5, D4, D6, D7, B4, B5, B6, C6, C7, F7, F6, F5, F4, B0, B2 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 15

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE


// The pin connected to the data pin of the LEDs
#define RGB_DI_PIN B1
// The number of LEDs connected
#define DRIVER_LED_TOTAL 256
#define RGBLED_NUM 100
#define RGBLIGHT_DEFAULT_HUE 201
#define RGBLIGHT_LIMIT_VAL 50