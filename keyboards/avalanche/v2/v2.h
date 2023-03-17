// Copyright 2022 Vitaly Volkov (@vlkv)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define L__ KC_NO
#define R__ KC_NO

#define LAYOUT( \
         L00, L01, L02, L03, L04, L05,           R05, R04, R03, R02, R01, R00, \
         L10, L11, L12, L13, L14, L15,           R15, R14, R13, R12, R11, R10, \
    L40, L20, L21, L22, L23, L24, L25, L26, R26, R25, R24, R23, R22, R21, R20, R40, \
         L30, L31, L32, L33, L34, L35, L36, R36, R35, R34, R33, R32, R31, R30, \
                   L42, L43, L44, L45, L46, R46, R45, R44, R43, R42 \
) \
{ \
    { L00, L01, L02, L03, L04, L05, L__}, \
    { L10, L11, L12, L13, L14, L15, L__}, \
    { L20, L21, L22, L23, L24, L25, L26}, \
    { L30, L31, L32, L33, L34, L35, L36}, \
    { L40, L__, L42, L43, L44, L45, L46}, \
    { R00, R01, R02, R03, R04, R05, R__}, \
    { R10, R11, R12, R13, R14, R15, R__}, \
    { R20, R21, R22, R23, R24, R25, R26}, \
    { R30, R31, R32, R33, R34, R35, R36}, \
    { R40, R__, R42, R43, R44, R45, R46} \
}
