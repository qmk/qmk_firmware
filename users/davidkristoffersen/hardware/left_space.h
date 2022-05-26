// Copyright 2022 David Kristoffersen (@davidkristoffersen)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "davidkristoffersen.h"

#if SPLIT_SPACE == true

#    define KEY KC_NO
#    define KEYW LT(7, KEY)

void _handle_left_space(uint16_t keycode, keyrecord_t* record) {
    if (IS_LAYER_ON(7)) clear_oneshot_mods();

    if (keycode == KEYW) {
        if (get_oneshot_mods() & MOD_MASK_SHIFT) {
            clear_oneshot_mods();
            set_oneshot_mods(MOD_LCTL);
        }
        else
            set_oneshot_mods(MOD_LSFT);
    }
}
#endif

#if SPLIT_SPACE == true
#    define SPACE_TRI LT(7, KEY)
#    define handle_left_space(k, r) _handle_left_space(k, r)
#elif SPLIT_SPACE == false
#    define SPACE_TRI KC_RIGHT
#    define handle_left_space(k, r)
#else
#    define SPACE_TRI KC_SPC
#    define handle_left_space(k, r)
#endif
