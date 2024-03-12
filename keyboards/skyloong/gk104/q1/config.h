// Copyright 2023 JZ-Skyloong (@JZ-Skyloong)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define MAC_PIN C13

#ifdef ENCODER_ENABLE
#    define ENCODER_MAP_KEY_DELAY 10
#endif

#define DIP_SWITCH_PINS {A4}

#ifdef RGB_MATRIX_ENABLE
#    define AW20216S_CS_PIN_1 B12
#    define AW20216S_CS_PIN_2 B11
// Hardware enable lines may be connected to the same pin
#    define AW20216S_EN_PIN B5

#    define NUM_LOCK_INDEX 33
#    define WIN_MOD_INDEX 22
#    define MAC_MOD_INDEX 23
#    define WIN_LOCK_INDEX 93
#    define CAPS_LOCK_INDEX 58
#    define SCR_LOCK_INDEX 14
#    define SDB B5
#endif // RGB_MATRIX_ENABLE


