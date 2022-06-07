/* Copyright 2022 GSKY <gskyGit@gsky.com.tw>
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

##define ___ KC_NO

//  ESC  F1   F2   F3   F4   F5   F6   F7   F8   F9   F10  F11  F12  Prt      Home
//  `    1    2    3    4    5    6    7    8    9    0    -    =    BSpc     Ins 
//  Tab  Q    W    E    R    T    Y    U    I    O    P    [    ]    \\       Del    
//  Caps A    S    D    F    G    H    J    K    L    ;    '         Enter    PgUp   
//  Sh_L      Z    X    C    V    B    N    M    ,    .    /    Sh_R   Up     PgDn    
//  Ct_L    Win_L   Alt_L      SPACE          Alt_R   FN   Ct_R    Left Down Right          

// clang-format off
#define LAYOUT( \
    k00, k10, k20, k30, k40, k50, k60, k70, k80, k90, ka0, kb0, kc0, kd0,     k56, \
    k01, k11, k21, k31, k41, k51, k61, k71, k81, k91, ka1, kb1, kc1, kd1,     k16, \
    k02, k12, k22, k32, k42, k52, k62, k72, k82, k92, ka2, kb2, kc2, kd2,     k06, \
    k03, k13, k23, k33, k43, k53, k63, k73, k83, k93, ka3, kb3,      kd3,     k26, \
    k04,      k24, k34, k44, k54, k64, k74, k84, k94, ka4, kb4, kd4,  k17,    k36, \
    k05,    k15,    k25,       k65,           k95,    ka5, kc5,    k07, k27, k37   \
)\
{\
    { k04, ___, k56, k07, kc5, k37, k05, k50},\
    { k12, k02, k13, k00, k24, k26, k01, k11},\
    { k22, k03, k23, ___, k34, k36, k10, k21},\
    { k32, k30, k33, k40, k44, k17, k20, k31},\
    { k42, k52, k43, k53, k54, k64, k51, k41},\
    { k72, k62, k73, k63, k84, k74, k61, k71},\
    { k82, kc2, k83, k60, k94, k06, kc1, k81},\
    { k92, k70, k93, k27, ka4, ___, k80, k91},\
    { ka2, kb2, ka3, kb3, kd2, kb4, kb1, ka1},\
    { k15, kd4, ka5, k25, k65, k95, ___, kd0},\
    { ___, kd1, kd2, kb0, kd3, kc0, k90, ka0},\
    { ___, ___, ___, ___, ___, ___, ___, ___},\
    { ___, ___, ___, ___, k56, ___, k16, ___},\
    { ___, ___, ___, ___, ___, ___, ___, ___} \
}
