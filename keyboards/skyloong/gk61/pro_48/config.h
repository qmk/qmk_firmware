// Copyright 2023 linlin012 (@linlin012)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define IS31FL3743A_I2C_ADDRESS_1 IS31FL3743A_I2C_ADDRESS_GND_GND

#define RGB_MATRIX_LED_COUNT 64
#define CAPS_LOCK_INDEX 28
#define WIN_MOD_INDEX 16
#define MAC_MOD_INDEX 17
#define SDB A4

#define RGB_MATRIX_SLEEP
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS

#define g_suspend_state rgb_matrix_get_suspend_state()
