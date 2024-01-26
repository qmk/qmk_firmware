// Copyright 2023 linlin012 (@linlin012)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_LED_COUNT 64
#    define CAPS_LOCK_INDEX 28
#    define WIN_MOD_INDEX 16
#    define MAC_MOD_INDEX 17
#    define SDB A4

#    define RGB_DISABLE_WHEN_USB_SUSPENDED
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS

#    define AW20216S_CS_PIN_1 B12
#    define AW20216S_EN_PIN_1 SDB
#endif // RGB_MATRIX_ENABLE
