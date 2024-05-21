// Copyright 2023 JZ-Skyloong (@JZ-Skyloong)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef ENCODER_ENABLE
#    define ENCODER_MAP_KEY_DELAY 10
#endif

#ifdef RGB_MATRIX_ENABLE
#    define AW20216S_CS_PIN_1 B12
#    define AW20216S_CS_PIN_2 B11
// Hardware enable lines may be connected to the same pin
#    define AW20216S_EN_PIN B5

#    define WIN_MOD_INDEX 19
#    define MAC_MOD_INDEX 20
#    define WIN_LOCK_INDEX 71
#    define CAPS_LOCK_INDEX 43
#endif // RGB_MATRIX_ENABLE


