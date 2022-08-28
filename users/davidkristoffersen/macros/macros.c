// Copyright 2022 David Kristoffersen (@davidkristoffersen)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "macros.h"

// Prepend key records with macros
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (record->event.pressed) {
#ifdef SPLIT_SPACE
        handle_split_space(keycode, record);
#endif
        HANDLE_FALSE(process_debug(keycode, record));
        HANDLE_FALSE(process_language(keycode, record));
    }
    return true;
}
