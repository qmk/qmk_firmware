// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "secure.h"
#include "process_secure.h"
#include "quantum_keycodes.h"

bool preprocess_secure(uint16_t keycode, keyrecord_t *record) {
    if (secure_is_unlocking()) {
        // !pressed will trigger on any already held keys (such as layer keys),
        // and cause the request secure check to prematurely fail.
        if (record->event.pressed) {
            secure_keypress_event(record->event.key.row, record->event.key.col);
        }

        // Normal keypresses should be disabled until the sequence is completed
        return false;
    }

    return true;
}

bool process_secure(uint16_t keycode, keyrecord_t *record) {
#ifndef SECURE_DISABLE_KEYCODES
    if (!record->event.pressed) {
        if (keycode == SECURE_LOCK) {
            secure_lock();
            return false;
        }
        if (keycode == SECURE_UNLOCK) {
            secure_unlock();
            return false;
        }
        if (keycode == SECURE_TOGGLE) {
            secure_is_locked() ? secure_unlock() : secure_lock();
            return false;
        }
        if (keycode == SECURE_REQUEST) {
            secure_request_unlock();
            return false;
        }
    }
#endif
    return true;
}
