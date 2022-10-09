// Copyright 2021 Kumao Kobo (@kumaokobo)
// SPDX-License-Identifier: GPL-2.0+

#pragma once

#include "quantum.h"

#define LAYOUT( \
  L00, L01, L02, L03, L04, L05, L06,            R00, R01, R02, R03, R04, R05, R06, R07, R08, \
  L10, L11, L12, L13, L14, L15, L16,            R10, R11, R12, R13, R14, R15, R16, R17,      \
  L20, L21, L22, L23, L24, L25,                 R20, R21, R22, R23, R24, R25, R26, R27,      \
  L30, L31, L32, L33, L34, L35,                 R30, R31, R32, R33, R34, R35, R36, R37, R38, \
  L40, L41, L42, L43, L44, L45,                 R40, R41, R42,                R46, R47, R48  \
) \
{ \
    { L00,   L01,   L02,   L03,   L04,   L05,   L06 }, \
    { L10,   L11,   L12,   L13,   L14,   L15,   L16 }, \
    { L20,   L21,   L22,   L23,   L24,   L25    }, \
    { L30,   L31,   L32,   L33,   L34,   L35    }, \
    { L40,   L41,   L42,   L43,   L44,   L45    }, \
    { R00,   R01,   R02,   R03,   R04,   R05,   R06,   R07,   R08 }, \
    { R10,   R11,   R12,   R13,   R14,   R15,   R16,   R17    }, \
    { R20,   R21,   R22,   R23,   R24,   R25,   R26,   R27    }, \
    { R30,   R31,   R32,   R33,   R34,   R35,   R36,   R37,   R38 }, \
    { R40,   R41,   R42,   KC_NO, KC_NO, KC_NO, R46,   R47,   R48 } \
}
