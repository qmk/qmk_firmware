// Copyright 2022 Keyprez (https://github.com/keyprez)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
  LA1, LA2, LA3, LA4, LA5, LA6, LA7, RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, RA9, \
  LB1, LB2, LB3, LB4, LB5, LB6,      RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8, RB9, \
  LC1, LC2, LC3, LC4, LC5, LC6,      RC1, RC2, RC3, RC4, RC5, RC6, RC7, RC8, RC9, RC10, \
  LD1, LD2, LD3, LD4, LD5, LD6, LD7, RD1, RD2, RD3, RD4, RD5, RD6, RD7, RD8, RD9, \
  LE1, LE2, LE3,      LE5, LE6,      RE1, RE2, RE3, RE4, RE5, RE6, RE7, RE8 \
  ) \
  { \
    { LA1, LA2, LA3, LA4, LA5, LA6, LA7, KC_NO }, \
    { LB1, LB2, LB3, LB4, LB5, LB6, KC_NO, KC_NO }, \
    { LC1, LC2, LC3, LC4, LC5, LC6, KC_NO, KC_NO }, \
    { LD1, LD2, LD3, LD4, LD5, LD6, LD7, KC_NO }, \
    { LE1, LE2, LE3, KC_NO, LE5, LE6, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8 }, \
    { RB1, RB2, RB3, RB4, RB5, RB6, RB7, KC_NO }, \
    { RC1, RC2, RC3, RC4, RC5, RC6, RC7, RC8 }, \
    { RD1, RD2, RD3, RD4, RD5, RD6, RD7, RD8 }, \
    { RE1, RE2, RE3, RE4, RE5, RE6, RE7, RE8 }, \
    { KC_NO, KC_NO, RA9, RB9, RB8, RC10, RC9, RD9 } \
  }
