// Copyright 2021 JasonRen(biu)
// Copyright 2022 Drashna Jael're (@Drashna Jael're)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"
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

#define RGB_MATRIX_SPLIT \
    { 43, 43 }

#define RGB_DI_PIN D3
#define RGBLED_NUM 86
#define DRIVER_LED_TOTAL RGBLED_NUM

#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
#define RGB_DISABLE_WHEN_USB_SUSPENDED
#define RGB_MATRIX_CENTER \
    { 112, 32 }

#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_MODS_ENABLE
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_OLED_ENABLE
#define SPLIT_TRANSACTION_IDS_KB KEYBOARD_CURRENT_ALPA_SYNC

#define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
