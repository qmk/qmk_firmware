// Copyright 2022 Scott Moyse (@RonnyM82)
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

/* Enable RGB Lighting*/
#define RGB_DI_PIN GP19
#define RGBLED_NUM 108
#define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
#define RGBLIGHT_DEFAULT_HUE 160
#define RGBLIGHT_DEFAULT_SAT 255
#define RGBLIGHT_DEFAULT_VAL 25
#define RGBLIGHT_LIMIT_VAL 125