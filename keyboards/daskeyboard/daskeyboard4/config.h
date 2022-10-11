// Copyright 2022 Commander1024 (@Commander1024)
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

/* configure bootmagic lite trigger to ESC */
#define BOOTMAGIC_LITE_ROW 5
#define BOOTMAGIC_LITE_COLUMN 16

/* configure rotary encoder */
#define ENCODERS_PAD_A { B13 }
#define ENCODERS_PAD_B { B12 }
#define ENCODER_RESOLUTION 4

/* LED indicators */
#define LED_NUM_LOCK_PIN C13
#define LED_CAPS_LOCK_PIN B14
#define LED_SCROLL_LOCK_PIN B2
#define LED_PIN_ON_STATE 1
