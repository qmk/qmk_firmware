// Copyright 2022 David Kristoffersen (@davidkristoffersen)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "split_space.h"

#ifdef SPLIT_SPACE
void handle_split_space(uint16_t keycode, keyrecord_t* record) {
    if (IS_LAYER_ON(NUMPAD)) clear_oneshot_mods();

    if (keycode == KC_LSPC) {
        if (get_oneshot_mods() & MOD_MASK_SHIFT) {
            clear_oneshot_mods();
            set_oneshot_mods(MOD_LCTL);
        }
        else {
            set_oneshot_mods(MOD_LSFT);
        }
    }
}
#endif
