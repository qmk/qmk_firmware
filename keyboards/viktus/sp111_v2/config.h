// Copyright 2023 BlindAssassin111 (@blindassassin111)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once


#ifdef RGB_MATRIX_ENABLE
    // The number of LEDs connected
    #define RGB_MATRIX_LED_COUNT 3
    #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
    #define RGB_MATRIX_KEYPRESSES
    #define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended
    #define EECONFIG_KB_DATA_SIZE 12
#endif
