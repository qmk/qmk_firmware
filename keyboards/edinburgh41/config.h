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
#define RGBLIGHT_SLEEP

#define RGBLIGHT_DEFAULT_SAT 0

// Thumbstick settings

#define ANALOG_JOYSTICK_X_AXIS_PIN B5
#define ANALOG_JOYSTICK_Y_AXIS_PIN B6
#define SCROLLING_LAYER 1
#define TAPPING_LAYER 2

#define THUMBSTICK_RIGHT_TAP KC_RIGHT
#define THUMBSTICK_LEFT_TAP KC_LEFT
#define THUMBSTICK_UP_TAP KC_UP
#define THUMBSTICK_DOWN_TAP KC_DOWN

#define CURSOR_SPEED 1
#define SCROLL_SPEED 0.1

// tap dance settings
#define TAPPING_TERM 155