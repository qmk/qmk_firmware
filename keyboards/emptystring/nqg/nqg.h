// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include "quantum.h"

#define LAYOUT( \
         L00, L01, L02, L03, L04,      L05, L06, L07, L08, L09, \
         L10, L11, L12, L13, L14,      L15, L16, L17, L18, L19, \
         L20, L21, L22, L23, L24,      L25, L26, L27, L28, L29, \
         L30,      L32, L33, L34,      L35, L36, L37            \
    ) { \
        {L00, L01,   L02, L03, L04, L05, L06, L07, L08,   L09},  \
        {L10, L11,   L12, L13, L14, L15, L16, L17, L18,   L19},  \
        {L20, L21,   L22, L23, L24, L25, L26, L27, L28,   L29},  \
        {L30, KC_NO, L32, L33, L34, L35, L36, L37, KC_NO, KC_NO} \
      }
