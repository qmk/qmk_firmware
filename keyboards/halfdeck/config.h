// Copyright 2018 Wez Furlong (@wez)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT




// Apparently need both of these defined for RESET to be effective?!
#define CATERINA_BOOTLOADER
//#define BOOTLOADER_CATERINA

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 12
//#define DIODE_DIRECTION CUSTOM_MATRIX

#define TOUCHPAD_IS_CIRQUE 0
#define ENABLE_TOUCHPAD 0

#define MOUSEKEY_ANALOG_XYVH 1
#define MOUSEKEY_MAX_SPEED 15
// This sets the compile time default for mk_wheel_max_speed.
// You can change mk_wheel_max_speed in your keymap at runtime
// if you want to dynamically adjust this value.
#define MOUSEKEY_WHEEL_MAX_SPEED 1
