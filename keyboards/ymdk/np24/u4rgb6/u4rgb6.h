/* Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>
 * Copyright 2021 Simon Arlott
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

#define XXX KC_NO

#define LAYOUT_ortho_6x4( \
    k00,  k10,  k20,  k30, \
    k01,  k11,  k21,  k31, \
    k02,  k12,  k22,  k32, \
    k03,  k13,  k23,  k33, \
    k04,  k14,  k24,  k34, \
    k05,  k15,  k25,  k35  \
) { \
    { k00, k10, k20, k30 }, \
    { k01, k11, k21, k31 }, \
    { k02, k12, k22, k32 }, \
    { k03, k13, k23, k33 }, \
    { k04, k14, k24, k34 }, \
    { k05, k15, k25, k35 }  \
}

#define LAYOUT_ortho_4x6_right( \
    k00, k01, k02, k03, k04, k05, \
    k10, k11, k12, k13, k14, k15, \
    k20, k21, k22, k23, k24, k25, \
    k30, k31, k32, k33, k34, k35  \
) { \
    { k05, k15, k25, k35 }, \
    { k04, k14, k24, k34 }, \
    { k03, k13, k23, k33 }, \
    { k02, k12, k22, k32 }, \
    { k01, k11, k21, k31 }, \
    { k00, k10, k20, k30 }  \
}

#define LAYOUT_ortho_4x6_left( \
    k00, k01, k02, k03, k04, k05, \
    k10, k11, k12, k13, k14, k15, \
    k20, k21, k22, k23, k24, k25, \
    k30, k31, k32, k33, k34, k35  \
) { \
    { k30, k20, k10, k00 }, \
    { k31, k21, k11, k01 }, \
    { k32, k22, k12, k02 }, \
    { k33, k23, k13, k03 }, \
    { k34, k24, k14, k04 }, \
    { k35, k25, k15, k05 }  \
}

#define LAYOUT_numpad_6x4( \
    k00, k10, k20, k30, \
    k01, k11, k21, k31, \
    k02, k12, k22,      \
    k03, k13, k23, k33, \
    k04, k14, k24,      \
    k15,      k25, k35  \
) { \
    { k00, k10, k20, k30 }, \
    { k01, k11, k21, k31 }, \
    { k02, k12, k22, XXX }, \
    { k03, k13, k23, k33 }, \
    { k04, k14, k24, XXX }, \
    { XXX, k15, k25, k35 }  \
}
