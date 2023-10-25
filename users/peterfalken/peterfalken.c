// Copyright 2023 Peter.Falken (@PeterFalken)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "peterfalken.h"

// Magic keycodes - overwrite placeholder functions
uint16_t keycode_config(uint16_t keycode) {
    return keycode;
}

uint8_t mod_config(uint8_t mod) {
    return mod;
}

// Switch layer
#ifndef CUSTOM_LAYER_STATE
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
#endif  // CUSTOM_LAYER_STATE
