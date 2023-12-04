// Copyright 2023 JZ-Skyloong (@JZ-Skyloong)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define LED_CAPS_LOCK_PIN C15
#define LED_SCROLL_LOCK_PIN C14
#define MAC_PIN C13

#ifdef ENCODER_ENABLE
#    define ENCODER_MAP_KEY_DELAY 20
#endif

#ifdef RGB_MATRIX_ENABLE
#    define DRIVER_1_CS B12
#    define DRIVER_2_CS B11
// Hardware enable lines may be connected to the same pin
#    define DRIVER_1_EN B5
#    define DRIVER_2_EN B5

#    define CAPS_LOCK_INDEX 50
#    define WIN_MOD_INDEX 22
#    define MAC_MOD_INDEX 23
#    define WIN_LOCK_INDEX 75
#    define SCR_LOCK_INDEX 14
#    define SDB B5
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#    define RGB_DISABLE_WHEN_USB_SUSPENDED
#endif // RGB_MATRIX_ENABLE
