// Copyright 2023 takashicompany (@takashicompany)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define LAYOUT( \
    l00, l01, l02, l03, l04, r00, r01, r02, r03, r04, \
    l05, l06, l07, l08, l09, r05, r06, r07, r08, r09, \
    l10, l11, l12, l13, l14, r10, r11, r12, r13, r14, \
    l15, l16, l17, l18, l19, r15, r16, r17, r18, r19  \
) { \
    { l00, l01, l02, l03, l04 }, \
    { l05, l06, l07, l08, l09 }, \
    { l10, l11, l12, l13, l14 }, \
    { l15, l16, l17, l18, l19 }, \
    { r00, r01, r02, r03, r04 }, \
    { r05, r06, r07, r08, r09 }, \
    { r10, r11, r12, r13, r14 }, \
    { r15, r16, r17, r18, r19 }  \
}