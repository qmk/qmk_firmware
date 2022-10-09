// Copyright 2021 Gabriel Kim (@gabrielkim13)
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
 *
 *
 * | Esc |   |  F1 |  F2 |  F3 |  F4 |  |  F5 |  F6 |  F7 |  F8 |  | F9 | F10 | F11 | F12 |  | SLk | Pau | NLk |
 * |  `  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  Back  |  | Ins | Hom | PUp |
 * |  Tab  |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |   \  |  | Del | End | PDn |
 * |   Caps  |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |   Enter  |
 * |   Shift   |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |    Shift     |        |  ^  |
 * | Ctrl | Win  | alt  |               Space                 | alt  |  fn  | Menu | Ctrl |  |  <  |  v  |  >  |
 */
#define LAYOUT_tkl_ansi( \
     k00 ,      k01 , k02 , k03 , k04 ,   k05 , k06 , k07 , k08 ,   k09 , k0A , k0B , k0C ,    k0D , k0E , k0F , \
     k10 , k11 , k12 , k13 , k14 , k15 , k16 , k17 , k18 , k19 , k1A , k1B , k1C ,  k1D   ,    k1E , k1F , k1G , \
      k20  , k21 , k22 , k23 , k24 , k25 , k26 , k27 , k28 , k29 , k2A , k2B , k2C , k2D  ,    k2E , k2F , k2G , \
       k30   , k31 , k32 , k33 , k34 , k35 , k36 , k37 , k38 , k39 , k3A , k3B ,    k3C   ,                      \
         k40    , k41 , k42 , k43 , k44 , k45 , k46 , k47 , k48 , k49 , k4A ,     k4B     ,          k4C ,       \
      k50 ,  k51 ,  k52 ,                k53                  ,  k54 ,  k55 ,  k56 ,  k57 ,    k58 , k59 , k5A   \
) { \
    { k00, KC_NO, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F, k1G }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, k2F, k2G }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, KC_NO, k3C, KC_NO, KC_NO, KC_NO }, \
    { k40, KC_NO, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, KC_NO, k4B, KC_NO, k4C, KC_NO }, \
    { k50, k51, k52, KC_NO, KC_NO, KC_NO, k53, KC_NO, KC_NO, KC_NO, k54, k55, k56, k57, k58, k59, k5A } \
}
