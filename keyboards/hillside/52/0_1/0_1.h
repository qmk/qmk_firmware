// Copyright 2021 Michael McCoyd (@mmccoyd)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

/* This is a mapping so keymap files can be more readable to humans.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts those identifiers into a two-dimensional array which
 * represents the switch matrix.
 * 
 * The identifiers could be anything, but for human sanity have the folowing form
 * <Left or Right><Physical or thumb row><Circuit column counting from outer pinky>
 */

// clang-format off
#define LAYOUT( \
  L00, L01, L02, L03, L04, L05,                     R05, R04, R03, R02, R01, R00, \
  L10, L11, L12, L13, L14, L15,                     R15, R14, R13, R12, R11, R10, \
  L20, L21, L22, L23, L24, L25, LT5,           RT5, R25, R24, R23, R22, R21, R20, \
  L30, L31, L32,      LT1, LT2, LT3, LT4, RT4, RT3, RT2, RT1,      R32, R31, R30 \
  ) \
  { \
    { L00,   L01, L02, L03,   L04,   L05 }, \
    { L10,   L11, L12, L13,   L14,   L15 }, \
    { L20,   L21, L22, L23,   L24,   L25 }, \
    { L30,   L31, L32, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, LT1, LT2, LT3,   LT4,   LT5 }, \
    { R00,   R01, R02, R03,   R04,   R05 }, \
    { R10,   R11, R12, R13,   R14,   R15 }, \
    { R20,   R21, R22, R23,   R24,   R25 }, \
    { R30,   R31, R32, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, RT1, RT2, RT3,   RT4,   RT5 } \
  }
// clang-format on
