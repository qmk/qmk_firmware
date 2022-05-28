// Copyright 2022 David Kristoffersen (@davidkristoffersen)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "macros.h"

// Prepend key records with macros
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (record->event.pressed) {
#ifdef SPLIT_SPACE
        handle_split_space(keycode, record);
#endif
        handle_false(process_debug(keycode, record));
#ifdef MULTI_LANGUAGE
        handle_false(process_language(keycode, record));
#endif
    }
    return true;
}
