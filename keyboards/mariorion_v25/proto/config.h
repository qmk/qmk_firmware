// Copyright 2023 Maria (@toril940)
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

#define WS2812_EXTERNAL_PULLUP

#define CAPS_LOCK_LED A5
#define SCROLL_LOCK_LED A15

#define INDICATOR_0 C8
#define INDICATOR_1 C7
#define INDICATOR_2 C6