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

//  ESC  F1   F2   F3   F4   F5   F6   F7   F8   F9   F10  F11  F12  Prt      Rotary(Mute)
//  `    1    2    3    4    5    6    7    8    9    0    -    =    BSpc     Del
//  Tab  Q    W    E    R    T    Y    U    I    O    P    [    ]             PgUp
//  Caps A    S    D    F    G    H    J    K    L    ;    '    #    Enter    PgDn
//  Sh_L \    Z    X    C    V    B    N    M    ,    .    /    Sh_R     Up   End
//  Ct_L    Win_L   Alt_L      SPACE          Alt_R   FN   Ct_R     Left Down Right

// clang-format off
#define LAYOUT( \
    k13, k26, k36, k31, k33, k07, k63, k71, k76, ka6, ka7, ka3, ka5, k97,     k01, \
    k16, k17, k27, k37, k47, k46, k56, k57, k67, k77, k87, k86, k66, ka1,     k65, \
    k11, k10, k20, k30, k40, k41, k51, k50, k60, k70, k80, k81, k61,          k15, \
    k21, k12, k22, k32, k42, k43, k53, k52, k62, k72, k82, k83, k84, ka4,     k25, \
    k00, k23, k14, k24, k34, k44, k45, k55, k54, k64, k74, k85, k91,     k35, k75, \
    k06,    k90,    k93,       k94,           k95,    k92, k04,     k03, k73, k05  \
) \
{ \
    { k00, k01, ___, k03, k04, k05, k06, k07}, \
    { k10, k11, k12, k13, k14, k15, k16, k17}, \
    { k20, k21, k22, k23, k24, k25, k26, k27}, \
    { k30, k31, k32, k33, k34, k35, k36, k37}, \
    { k40, k41, k42, k43, k44, k45, k46, k47}, \
    { k50, k51, k52, k53, k54, k55, k56, k57}, \
    { k60, k61, k62, k63, k64, k65, k66, k67}, \
    { k70, k71, k72, k73, k74, k75, k76, k77}, \
    { k80, k81, k82, k83, k84, k85, k86, k87}, \
    { k90, k91, k92, k93, k94, k95, ___, k97}, \
    { ___, ka1, ___, ka3, ka4, ka5, ka6, ka7}  \
}
// clang-format on
