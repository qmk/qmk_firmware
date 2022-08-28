// Copyright 2022 Vitaly Volkov (@vlkv)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "avalanche.h"

#include "quantum.h"

#define L__ KC_NO
#define R__ KC_NO

#define LAYOUT( \
         L01, L02, L03, L04, L05, L06,           R06, R05, R04, R03, R02, R01, \
         L11, L12, L13, L14, L15, L16,           R16, R15, R14, R13, R12, R11, \
    L20, L21, L22, L23, L24, L25, L26, L27, R27, R26, R25, R24, R23, R22, R21, R20, \
         L31, L32, L33, L34, L35, L36, L37, R37, R36, R35, R34, R33, R32, R31, \
                        L44, L45, L46, L47, R47, R46, R45, R44 \
) \
{ \
    { L__, L01, L02, L03, L04, L05, L06, L__}, \
    { L__, L11, L12, L13, L14, L15, L16, L__}, \
    { L20, L21, L22, L23, L24, L25, L26, L27}, \
    { L__, L31, L32, L33, L34, L35, L36, L37}, \
    { L__, L__, L__, L__, L44, L45, L46, L47}, \
    { R__, R01, R02, R03, R04, R05, R06, R__}, \
    { R__, R11, R12, R13, R14, R15, R16, R__}, \
    { R20, R21, R22, R23, R24, R25, R26, R27}, \
    { R__, R31, R32, R33, R34, R35, R36, R37}, \
    { R__, R__, R__, R__, R44, R45, R46, R47} \
}
