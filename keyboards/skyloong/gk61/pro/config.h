// Copyright 2023 linlin012 (@linlin012)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* Encoder Configuration */
#ifdef ENCODER_ENABLE
#    define ENCODER_RESOLUTION 2
#    define ENCODER_DEFAULT_POS 0x3
#endif

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

#ifdef RGB_MATRIX_ENABLE

#define DRIVER_COUNT 1
#define RGB_MATRIX_LED_COUNT 64
#define __flash  PROGMEM

/* Set Configuration for the Global Current Register */
#define ISSI_GLOBALCURRENT 255

/* Set to infinit, which is use in USB mode by default */
//#define RGB_MATRIX_TIMEOUT RGB_MATRIX_TIMEOUT_INFINITE

/* Allow shutdown of led driver to save power */
#define RGB_MATRIX_DRIVER_SHUTDOWN_ENABLE
/* Turn off backlight on low brightness to save power */
#define RGB_MATRIX_BRIGHTNESS_TURN_OFF_VAL 32

#define CAPS_LOCK_INDEX 28
#define WIN_MOD_INDEX 16
#define MAC_MOD_INDEX 17
#define WIN_LOCK_INDEX 54

/* RGB Matrix Animation modes. Explicitly enabled
 * For full list of effects, see:
 * https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects
 */

#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS

#endif
