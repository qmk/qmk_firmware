// Copyright 2024 Javier Oliver (@joliverMI)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#define kno KC_NO

#define LAYOUT_game_split_85(\
k00, k01, k02, k03, k04, k05, k06, k07,   k42, k43, k44, k45, k46, k47, k48, k49,\
k08, k09, k10, k11, k12, k13, k14, k15,   k50, k51, k52, k53, k54, k55, k56,\
k16, k17, k18, k19, k20, k21, k22,        k57, k58, k59, k60, k61, k62, k63, k64,\
k23, k24, k25, k26, k27, k28, k29,        k65, k66, k67, k68, k69, k70, k71,\
k30, k31, k32, k33, k34, k35, k36,        k72, k73, k74, k75, k76, k77, k78,\
k37, k38, k39, k40, k41,                  k79, k80, k81, k82, k83, k84\
) \
{ \
    { k00, k01, k02, k03, k04, k05, k06, k07}, \
    { k08, k09, k10, k11, k12, k13, k14, k15}, \
    { k16, k17, k18, k19, k20, k21, k22, kno}, \
    { k23, k24, k25, k26, k27, k28, k29, kno}, \
    { k30, kno, k31, k32, k33, k34, k35, k36}, \
    { k37, k38, k39, k40, kno, kno, k41, kno}, \
    { k42, k43, k44, k45, k46, k47, k48, k49}, \
    { k50, k51, k52, k53, k54, k55, k56, kno}, \
    { k57, k58, k59, k60, k61, k62, k63, k64}, \
    { k65, k66, k67, k68, k69, k70, k71, kno}, \
    { k72, k73, k74, k75, k76, k77, k78, kno}, \
    { kno, k79, k80, k81, k82, k83, kno, k84} \
}
