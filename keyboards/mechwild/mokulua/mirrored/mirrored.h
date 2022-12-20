// Copyright 2022 Kyle McCreery (@kylemccreery)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define ___ KC_NO

#define LAYOUT_mirrored( \
    L00, L01, L02, L03, L04, L05, L06,             R00, R01, R02, R03, R04, R05, R06, \
    L10, L11, L12, L13, L14, L15, L16,             R10, R11, R12, R13, R14, R15, R16, \
    L20, L21, L22, L23, L24, L25, L26,             R20, R21, R22, R23, R24, R25, R26, \
    L30, L31, L32, L33, L34, L35, L36, L37,   R30, R31, R32, R33, R34, R35, R36, R37, \
    L40, L41, L42, L43,    L44, L45,   L46,   R40,   R41, R42,    R43, R44, R45, R46  \
) { \
    { L00, L01, L02, L03, L04, L05 }, \
    { L10, L11, L12, L13, L14, L15 }, \
    { L20, L21, L22, L23, L24, L25 }, \
    { L30, L31, L32, L33, L34, L35 }, \
    { L40, L41, L42, L43, L44, L45 }, \
    { L46, L36, L37, L26, L16, L06 }, \
    { R06, R05, R04, R03, R02, R01 }, \
    { R16, R15, R14, R13, R12, R11 }, \
    { R26, R25, R24, R23, R22, R21 }, \
    { R37, R36, R35, R34, R33, R32 }, \
    { R46, R45, R44, R43, R42, R41 }, \
    { R40, R31, R30, R20, R10, R00 }  \
}

#define LAYOUT       LAYOUT_mirrored