// Copyright 2022 Matthew Dews (@matthew-dews)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include "dactyl_manuform.h"

#define XXX KC_NO

#define LAYOUT_6x7( \
    L00, L01, L02, L03, L04, L05, L06,                         R00, R01, R02, R03, R04, R05, R06, \
    L10, L11, L12, L13, L14, L15, L16,                         R10, R11, R12, R13, R14, R15, R16, \
    L20, L21, L22, L23, L24, L25, L26,                         R20, R21, R22, R23, R24, R25, R26, \
    L30, L31, L32, L33, L34, L35, L36,                         R30, R31, R32, R33, R34, R35, R36, \
    L40, L41, L42, L43, L44, L45, L46,                         R40, R41, R42, R43, R44, R45, R46, \
                   L52, L53,                                             R52, R53, \
                             L54, L55,                         R50, R51, \
                                       L64, L65,      R60, R61, \
                                       L62, L63,      R62, R63 \
) { \
    { L00, L01, L02, L03, L04, L05, L06 }, \
    { L10, L11, L12, L13, L14, L15, L16 }, \
    { L20, L21, L22, L23, L24, L25, L26 }, \
    { L30, L31, L32, L33, L34, L35, L36 }, \
    { L40, L41, L42, L43, L44, L45, L46 }, \
    { XXX, XXX, XXX, L52, L53, L54, L55 }, \
    { XXX, XXX, XXX, L62, L63, L64, L65 }, \
\
    { R00, R01, R02, R03, R04, R05, R06 }, \
    { R10, R11, R12, R13, R14, R15, R16 }, \
    { R20, R21, R22, R23, R24, R25, R26 }, \
    { R30, R31, R32, R33, R34, R35, R36 }, \
    { R40, R41, R42, R43, R44, R45, R46 }, \
    { R50, R51, R52, R53, XXX, XXX, XXX }, \
    { R60, R61, R62, R63, XXX, XXX, XXX } \
}
