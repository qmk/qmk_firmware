// Copyright 2021 Victor Toni (@vitoni)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#if defined(RGB_MATRIX_ENABLE)
    #define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_COLOR
     // number of milliseconds to wait until turning off RGB automatically
    #define RGB_DISABLE_TIMEOUT 300000 // 300 seconds / 5 min
    #define RGB_DISABLE_WHEN_USB_SUSPENDED
#endif
