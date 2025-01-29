// Copyright 2025 Viktus Design LLC
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef RGB_MATRIX_ENABLE
    #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
    #define RGB_MATRIX_KEYPRESSES
    #define RGB_MATRIX_SLEEP // turn off effects when suspended
    #define EECONFIG_KB_DATA_SIZE 28
#endif
