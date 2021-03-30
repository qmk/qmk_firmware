/* Copyright 2019 marhalloweenvt
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once


#include "quantum.h"

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT_alice_split_bs( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e,      \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c,      K2e,      \
    k30, k31, k32, k33, k34, k35,      k37, k38, k39, k3a, k3b, k3c, k3d, k3e,      \
    k40,      k42, k43, k44,           k47,           k4a,                k4e       \
) { \
    { k00,  k01,   k02,   k03,  k04,  k05,   k06,   k07,   k08,  k09,   k0a,  k0b,  k0c,    k0d,    k0e, k0f    }, \
    { k10,  k11,   k12,   k13,  k14,  k15,   k16,   k17,   k18,  k19,   k1a,  k1b,  k1c,    k1d,    k1e, KC_NO  }, \
    { k20,  k21,   k22,   k23,  k24,  k25,   k26,   k27,   k28,  k29,   k2a,  k2b,  k2c,    KC_NO,  K2e, KC_NO  }, \
    { k30,  k31,   k32,   k33,  k34,  k35,   KC_NO, k37,   k38,  k39,   k3a,  k3b,  k3c,    k3d,    k3e, KC_NO  }, \
    { k40,  KC_NO, k42,   k43,  k44,  KC_NO, KC_NO, k47, KC_NO,  KC_NO, k4a,  KC_NO,KC_NO,  KC_NO,  k4e, KC_NO  }, \
}

#define LAYOUT LAYOUT_alice_split_bs
