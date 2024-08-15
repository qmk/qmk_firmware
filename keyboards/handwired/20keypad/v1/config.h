// Copyright 2024 Said Mrini (@smrini)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define DEBOUNCE 5 // Set the debounce time in milliseconds

// Locking resynchronize hack
#define LOCKING_RESYNC_ENABLE

// defining the builtin ws2812 RGB LED
#define WS2812_DI_PIN GP16
#define RGBLIGHT_LED_COUNT 1

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
