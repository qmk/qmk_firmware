// Copyright 2022 Thunderbird2086 (Thunderbird2086)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#include "via.h"


// This a shortcut to help you visually see your layout.

#define ___ KC_NO

#define LAYOUT(             \
             k15,           \
          k16,  k17,        \
       k18,        k19,     \
     k20, k21,   k22, k23,  \
   k00, k01, k02, k03, k04, \
   k05, k06, k07, k08, k09, \
   k10, k11, k12, k13, k14  \
) \
{ \
    { k00, k01, k02, k03, k04 }, \
    { k05, k06, k07, k08, k09 }, \
    { k10, k11, k12, k13, k14 }, \
    { ___, ___, k15, ___, ___ }, \
    { ___, k16, ___, k17, ___ }, \
    { ___, k18, ___, k19, ___ }, \
    { k20, k21, ___, k22, k23 }  \
}
