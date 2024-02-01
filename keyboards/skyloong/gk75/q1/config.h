// Copyright 2023 JZ-Skyloong (@JZ-Skyloong)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

//#define USB_POLLING_INTERVAL_MS 1
#define FORCE_NKRO

#define ENCODER_MAP_KEY_DELAY 10

#define DRIVER_ADDR_2 0b0100011
#define DRIVER_COUNT 2

#define RGB_MATRIX_LED_COUNT 87
#define CAPS_LOCK_INDEX 44
#define WIN_MOD_INDEX 20
#define MAC_MOD_INDEX 21
#define WIN_LOCK_INDEX 75
#define SDB B12

/* RGB Matrix Animation modes. Explicitly enabled
 * For full list of effects, see:
 * https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects
 */
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CUSTOM_solid_green
#define RGB_MATRIX_DEFAULT_HUE 0

#define WAIT_FOR_USB

