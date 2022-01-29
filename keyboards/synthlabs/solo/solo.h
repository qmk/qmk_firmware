// Copyright 2022 Aaron Hong (@hongaaronc)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"


#define XXX KC_NO

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array
#define LAYOUT_all(                                                                 \
                        K01, K02, K03, K04, K05, K06, K07,                          \
        K08, K09, K10,                                                              \
                        K11, K12, K13, K14, K15, K16, K17                           \
    ) {                                                                             \
        {               K01, K02, K03, K04, K05, K06, K07       },                  \
        {   K08, K09, K10                                       },                  \
        {               K11, K12, K13, K14, K15, K16, K17       }                   \
    }
#define LAYOUT_left(                                                                \
                             K02,      K04,      K06,                               \
        K08, K09, K10,                                                              \
                        K11,      K13,      K15,      K17                           \
    ) {                                                                             \
        {               XXX, K02, XXX, K04, XXX, K06, XXX       },                  \
        {   K08, K09, K10                                       },                  \
        {               K11, XXX, K13, XXX, K15, XXX, K17       }                   \
    }
#define LAYOUT_right(                                                               \
                 K16,      K14,      K12,                                           \
                                            K08, K09, K10,                          \
            K07,      K05,      K03,      K01                                       \
    ) {                                                                             \
        {               K01, XXX, K03, XXX, K05, XXX, K07       },                  \
        {   K08, K09, K10                                       },                  \
        {               XXX, K12, XXX, K14, XXX, K16, XXX       }                   \
    }
