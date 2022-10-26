// Copyright 2022 Connor McQuade (@DJZenose)
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

#define BACKLIGHT_PIN C6

#define MATRIX_ROWS 12
#define MATRIX_COLS 9

#ifdef OLED_ENABLE
#define OLED_DISPLAY_128X32
#define I2C1_SCL_PIN A9
#define I2C1_SDA_PIN A10
#define OLED_BRIGHTNESS 128
#endif
