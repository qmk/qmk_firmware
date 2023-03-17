// Copyright 2022 peepeetee (@peepeetee)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define ___ KC_NO

#define LAYOUT_numpad_6x5( \
    K00, K01, K02, K03, K04, \
    K10, K11, K12, K13, K14, \
    K20, K21, K22, K23, K24, \
    K30, K31, K32, K33, \
    K40, K41, K42, K43, K53, \
    K50, K51,      K52  \
) { \
    { K00, K01, K02, K03, K04 }, \
    { K10, K11, K12, K13, K14 }, \
    { K20, K21, K22, K23, K24 }, \
    { K30, K31, K32, K33, ___ }, \
    { K40, K41, K42, K43, ___ }, \
    { K50, K51, K52, K53, ___ }, \
}
