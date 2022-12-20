/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
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

#define ___ KC_NO

//  ESC  F1   F2   F3   F4   F5   F6   F7   F8   F9   F10  F11  F12  Prt      Del  Ins  PgUp  PgDn
//  `    1    2    3    4    5    6    7    8    9    0    -    =    BSpc     Num  /    *     -
//  Tab  Q    W    E    R    T    Y    U    I    O    P    [    ]    Enter    7    8    9     +
//  Caps A    S    D    F    G    H    J    K    L    ;    '    #    Enter    4    5    6     +
//  Sh_L \    Z    X    C    V    B    N    M    ,    .    /    Sh_R   Up     1    2    3     Enter
//  Ct_L    Win_L   Alt_L      SPACE          Alt_R   FN   Ct_R    Left Down Right 0    .     Enter

// clang-format off
#define LAYOUT( \
    k00, k10, k20, k30, k40, k50, k60, k70, k80, k90, ka0, kb0, kc0, kd0,     k06, k16, k26, k36,\
    k01, k11, k21, k31, k41, k51, k61, k71, k81, k91, ka1, kb1, kc1, kd1,     k46, k56, k66, k76,\
    k02, k12, k22, k32, k42, k52, k62, k72, k82, k92, ka2, kb2, kc2, kd3,     k86, k96, ka6, kb6,\
    k03, k13, k23, k33, k43, k53, k63, k73, k83, k93, ka3, kb3, kc3,          ka7, kb7, kc7,     \
    k04, k14, k24, k34, k44, k54, k64, k74, k84, k94, ka4, kb4, kd4,  k17,    k67, k77, k87, k97,\
    k05,    k15,    k25,       k65,           k95,    ka5, kc5,    k07, k27, k37,  k47, k57      \
)\
{\
    { k00, k01, k02, k03, k04, k05, k06, k07},\
    { k10, k11, k12, k13, k14, k15, k16, k17},\
    { k20, k21, k22, k23, k24, k25, k26, k27},\
    { k30, k31, k32, k33, k34, ___, k36, k37},\
    { k40, k41, k42, k43, k44, ___, k46, k47},\
    { k50, k51, k52, k53, k54, ___, k56, k57},\
    { k60, k61, k62, k63, k64, k65, k66, k67},\
    { k70, k71, k72, k73, k74, ___, k76, k77},\
    { k80, k81, k82, k83, k84, ___, k86, k87},\
    { k90, k91, k92, k93, k94, k95, k96, k97},\
    { ka0, ka1, ka2, ka3, ka4, ka5, ka6, ka7},\
    { kb0, kb1, kb2, kb3, kb4, ___, kb6, kb7},\
    { kc0, kc1, kc2, kc3, ___, kc5, ___, kc7},\
    { kd0, kd1, ___, kd3, kd4, ___, ___, ___} \
}
