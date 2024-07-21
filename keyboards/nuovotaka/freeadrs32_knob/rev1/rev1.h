// SPDX-FileCopyrightText: 2024 TaFahiro Natsume ( @nuovotaFa )
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#include "lib/freeadrs32/freeadrs32.h"


// clang-format off
#define LAYOUT(\
    N00, F01, F02, F03, F04, F05, F06, F07, F08,                \
    F11, F12, F13, F14, F15, F16, F17, F18,                     \
    N20, F21, F22, F23, F24, F25, F26, F27, F28,                \
    N30, F31, F32, F33, F34, F35, F36, F37, F38)                \
    {\
        {N00, F01, F02, F03, KC_NO, F04, F05, F06, F07, F08},   \
        {KC_NO, F11, F12, F13, KC_NO, F14, F15, F16, F17, F18}, \
        {N20, F21, F22, F23, KC_NO, F24, F25, F26, F27, F28},   \
        {N30, F31, F32, F33, KC_NO, F34, F35, F36, F37, F38}    \
    }

// clang-format on
