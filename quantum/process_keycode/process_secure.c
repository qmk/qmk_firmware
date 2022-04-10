// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "secure.h"
#include "process_secure.h"

bool process_secure(uint16_t keycode, keyrecord_t *record) {
    if (secure_is_unlocking()) {
        if (!record->event.pressed) {
            secure_keypress_event(record->event.key.row, record->event.key.col);
        }

        // Normal keypresses should be disabled until the sequence is completed
        return false;
    }

    return true;
}
