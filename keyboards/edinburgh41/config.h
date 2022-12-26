// Copyright 2022 L. Mistry (@schwarzer-geiger)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

// key matrix settings
#define MATRIX_ROWS 7
#define MATRIX_COLS 6

#define MATRIX_ROW_PINS \
    { F4, F5, F6, F7, B1, B3, B2 }
#define MATRIX_COL_PINS \
    { D1, D4, C6, D7, E6, B4 }

#define DIODE_DIRECTION COL2ROW

#define DEBOUNCE 5

// bootmagic settings

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

// Underglow LED settings

#define RGB_DI_PIN D0
#define RGBLED_NUM 10

// Thumbstick settings
#define ANALOG_JOYSTICK_X_AXIS_PIN B5
#define ANALOG_JOYSTICK_Y_AXIS_PIN B6

// Thumbstick defaults

#ifndef SCROLLING_LAYER
    #define SCROLLING_LAYER 1
#endif
#ifndef TAPPING_LAYER
    #define TAPPING_LAYER 2
#endif
#ifndef THUMBSTICK_RIGHT_TAP
    #define THUMBSTICK_RIGHT_TAP KC_RIGHT
#endif
#ifndef THUMBSTICK_LEFT_TAP
    #define THUMBSTICK_LEFT_TAP KC_LEFT
#endif
#ifndef THUMBSTICK_UP_TAP
    #define THUMBSTICK_UP_TAP KC_UP
#endif
#ifndef THUMBSTICK_DOWN_TAP
    #define THUMBSTICK_DOWN_TAP KC_DOWN
#endif
#ifndef CURSOR_SPEED
    #define CURSOR_SPEED 1
#endif
#ifndef SCROLL_SPEED
    #define SCROLL_SPEED 0.1
#endif
#ifndef SCROLL_DELAY_MS
    #define SCROLL_DELAY_MS 70
#endif
