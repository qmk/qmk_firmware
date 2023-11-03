// Copyright 2023 KiwiKey
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef OLED_ENABLE
#    define OLED_DISPLAY_128X64
#    define OLED_TIMEOUT 30000
#    define OLED_FONT_H "keyboards/kiwikey/kawii9v2/lib/glcdfont.c"
#endif

#ifdef RGB_MATRIX_ENABLE
#    define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended
#    define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CYCLE_UP_DOWN // Set default RGB Matrix mode
#endif
