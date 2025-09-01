// Copyright 2025 joshsit (@joshsit)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

//Uncomment below to enable tap hold configuration for Home Row Mods:
// Configure the global tapping term (default: 200ms)
#define TAPPING_TERM 180
#define TAPPING_TERM_PER_KEY

#define IGNORE_MOD_TAP_INTERRUPT

// LED LIGHTING STUFF HERE
// #define WS2812_PIO_USE_PIO1 
#define RGBLIGHT_LAYERS
// #define WS2812_DI_PIN GP16
#define RGB_DI_PIN GP16
#define RGBLED_NUM 1
#define RGBLIGHT_LIMIT_VAL 50
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SLEEP
// #define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF


// #define MK_3_SPEED

#define MOUSEKEY_MOVE_DELTA 4
#define MOUSEKEY_TIME_TO_MAX 20
#define MOUSEKEY_WHEEL_MAX_SPEED 4

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define QUICK_TAP_TERM 0
//______________________________________________________________________________

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
