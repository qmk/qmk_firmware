// Copyright 2024 @Filios92
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

enum combos { ctrl };

uint16_t const ctrl_combo[]    = {KC_H, KC_J, COMBO_END};

combo_t key_combos[] = {
    [ctrl]     = COMBO(ctrl_combo, KC_LCTL)
};
