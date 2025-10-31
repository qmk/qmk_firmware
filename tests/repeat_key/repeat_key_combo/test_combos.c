// Copyright 2023 Stefan Kerkmann (@KarlK90)
// Copyright 2023 @filterpaper
// Copyright 2023 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

const uint16_t xy_combo[] PROGMEM = {KC_X, KC_Y, COMBO_END};
combo_t        key_combos[]       = {COMBO(xy_combo, KC_Q)};
