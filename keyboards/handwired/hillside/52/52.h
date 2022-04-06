// Copyright 2021 Michael McCoyd (@mmccoyd)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts those identifiers into a two-dimensional array which
 * represents the switch matrix.
 */

// clang-format off
#define LAYOUT( \
  L00, L01, L02, L03, L04, L05,                     R00, R01, R02, R03, R04, R05, \
  L10, L11, L12, L13, L14, L15,                     R10, R11, R12, R13, R14, R15, \
  L20, L21, L22, L23, L24, L25, LT5,           RT5, R20, R21, R22, R23, R24, R25, \
  L30,      L32,      LT1, LT2, LT3, LT4, RT4, RT3, RT2, RT1,      R33,      R35, \
       L31, L33, L34,                                         R31, R32, R34 \
  ) \
  { \
    { L00,   L01, L02, L03, L04, L05 }, \
    { L10,   L11, L12, L13, L14, L15 }, \
    { L20,   L21, L22, L23, L24, L25 }, \
    { L30,   L31, L32, L33, L34, KC_NO }, \
    { KC_NO, LT1, LT2, LT3, LT4, LT5 }, \
    { R05,   R04, R03, R02, R01, R00 }, \
    { R15,   R14, R13, R12, R11, R10 }, \
    { R25,   R24, R23, R22, R21, R20 }, \
    { R35,   R34, R33, R32, R31, KC_NO }, \
    { KC_NO, RT1, RT2, RT3, RT4, RT5 }	\
  }
// clang-format on
