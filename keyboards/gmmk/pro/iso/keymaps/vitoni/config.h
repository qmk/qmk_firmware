// Copyright 2021 Victor Toni (@vitoni)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#if defined(RGB_MATRIX_ENABLE)
    #define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_COLOR
     // number of milliseconds to wait until turning off RGB automatically
    #define RGB_DISABLE_TIMEOUT 300000 // 300 seconds / 5 min
    // start fading out before getting disabled
    // fading out is timed (depending on the rgb_matrix_config.speed) to have finished before reaching RGB_DISABLE_TIMEOUT
    #define RGB_DISABLE_WITH_FADE_OUT
    #define RGB_DISABLE_WHEN_USB_SUSPENDED
    // fade in when we have been suspended
    #define RGB_FADE_IN
#endif
