// Copyright 2022 David Kristoffersen (@davidkristoffersen)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "macros.h"

// Prepend key records with macros
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (record->event.pressed) {
        handle_split_space(keycode, record);
        handle_false(process_static(keycode, record));
        handle_false(process_dynamic(keycode, record));
    }
    return true;
}
