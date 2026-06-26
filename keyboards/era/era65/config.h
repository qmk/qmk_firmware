// Copyright 2023 eerraa (@era)
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

#define PICO_XOSC_STARTUP_DELAY_MULTIPLIER 64

#define BACKLIGHT_PWM_DRIVER PWMD0
#define BACKLIGHT_PWM_CHANNEL RP2040_PWM_CHANNEL_A
