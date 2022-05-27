// Copyright 2022 David Kristoffersen (@davidkristoffersen)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "davidkristoffersen.h"

#define KC_RSPC KC_SPACE

#ifdef SPLIT_SPACE
#    define KC_LSPC LT(QGMLWB_NO_LOWER, KC_NO)
void handle_split_space(uint16_t keycode, keyrecord_t* record);
#else
#   define KC_LSPC KC_SPACE
#   define handle_split_space(k, r)
#endif

