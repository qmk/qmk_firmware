// Copyright 2022 Josh Hinnebusch (@hineybush)
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

#define LED_NUM_LOCK_PIN A6
#define LED_CAPS_LOCK_PIN B14
#define LED_SCROLL_LOCK_PIN B8
#define LED_ON_STATE 0
