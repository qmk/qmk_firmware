// Copyright 2023 takashicompany (@takashicompany)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include "quantum.h"

#define XXX KC_NO

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
    l01, l02, l03, l04, l05, r01, r02, r03, r04, r05, \
    l06, l07, l08, l09, l10, r06, r07, r08, r09, r10, \
    l11, l12, l13, l14, l15, r11, r12, r13, r14, r15, \
		 l16, l17, l18, l19, r16, r17, r18, r19       \
) { \
    { l01, l02, l03, l04, l05 }, \
    { l06, l07, l08, l09, l10 }, \
    { l11, l12, l13, l14, l15 }, \
    { XXX, l16, l17, l18, l19 }, \
    { r01, r02, r03, r04, r05 }, \
    { r06, r07, r08, r09, r10 }, \
    { r11, r12, r13, r14, r15 }, \
    { r16, r17, r18, r19, XXX }  \
}

