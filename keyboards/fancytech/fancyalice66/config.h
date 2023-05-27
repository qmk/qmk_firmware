// Copyright 2022 chent7 (@chent7)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef RGB_MATRIX_ENABLE
#    define WS2812_DI_PIN B0
#    define RGB_DI_PIN B0
#    define RGB_MATRIX_LED_COUNT 82

    /* RGB Matrix effect */
#    define RGB_MATRIX_KEYPRESSES // reacts to keypresses
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#endif