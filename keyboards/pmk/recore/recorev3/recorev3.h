// Copyright 2024 Javier Oliver (@joliverMI)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#define kno KC_NO

#define LAYOUT_game_ortho_74(\
k00, k01, k02, k03, k04, k05, k06, k07,   k37, k38, k39, k40, k41, k42, k43, k44,\
k08, k09, k10, k11, k12, k13, k14, k15,   k45, k46, k47, k48, k49, k50, k51, k52,\
k16, k17, k18, k19, k20, k21,                       k53, k54, k55, k56, k57, k58,\
k22, k23, k24, k25, k26, k27, k28, k29,   k59, k60, k61, k62, k63, k64, k65, k66,\
k30, k31, k32, k33, k34, k35, k36,             k67, k68, k69, k70, k71, k72, k73 \
) \
{ \
    { k00, k01, k02, k03, k04, k05, k06, k07}, \
    { k08, k09, k10, k11, k12, k13, k14, k15}, \
    { k16, k17, k18, k19, k20, k21, kno, kno}, \
    { k22, k23, k24, k25, k26, k27, k28, k29}, \
    { k30, k31, k32, k33, kno, k34, k35, k36}, \
    { k37, k38, k39, k40, k41, k42, k43, k44}, \
    { k45, k46, k47, k48, k49, k50, k51, k52}, \
    { kno, kno, k53, k54, k55, k56, k57, k58}, \
    { k59, k60, k61, k62, k63, k64, k65, k66}, \
    { k67, k68, k69, kno, k70, k71, k72, k73} \
}

