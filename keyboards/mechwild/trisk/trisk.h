// Copyright 2022 Kyle McCreery (@kylemccreery)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define ___ KC_NO

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
         k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C \
) { \
    {  k00, k01, k02, k03, k04 }, \
    {  k05, k06, k07, k08, k09 },  \
    {  k0A, k0B, k0C, ___, ___ } \
}
