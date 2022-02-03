// Copyright 2021 Will McGloughlin (@wymcg)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
    K00, K01, K02, K03, \
    K10, K11, K12, K13, \
    K20, K21, K22, K23 \
) { \
    {K00, K01, K02, K03}, \
    {K10, K11, K12, K13}, \
    {K20, K21, K22, K23} \
}
