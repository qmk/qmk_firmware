// Copyright 2022 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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


// #define RGB_DI_PIN D1
#define RGB_MATRIX_LED_COUNT 16
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255
#define RGB_MATRIX_DISABLE_KEYCODES
#define RGB_DISABLE_WHEN_USB_SUSPENDED
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS

#define RGBLIGHT_DI_PIN D2
#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_STATIC_GRADIENT + 9
#define RGBLIGHT_DEFAULT_HUE 213
