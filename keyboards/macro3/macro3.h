/* Copyright 2020 David Philip Barr <@davidphilipbarr>
 * Copyright 2021 @filterpaper
 * SPDX-License-Identifier: GPL-2.0+
 */

#include "quantum.h"

#define LAYOUT( \
    K00, K01, K02, K03, \
    K10, K11, K12, K13  \
) \
{ \
    { K00, K01, K02, K03 }, \
    { K10, K11, K12, K13 }  \
}

