// Copyright 2023 BlindAssassin111 (@blindassassin111)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* Split Defines */
#define SPLIT_USB_DETECT
#define MASTER_LEFT

#ifdef RGB_MATRIX_ENABLE
    // The number of LEDs connected
    #define RGB_MATRIX_LED_COUNT 3
    #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
    #define RGB_MATRIX_KEYPRESSES
    #define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended
    #define EECONFIG_KB_DATA_SIZE 12
#endif

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
