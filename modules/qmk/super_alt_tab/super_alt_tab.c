// Copyright 2025 Christopher Courtney, aka Drashna Jael're  (@drashna)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "introspection.h"

ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(1, 0, 0);

static bool     is_alt_tab_active = false; // ADD this near the beginning of keymap.c
static uint16_t alt_tab_timer     = 0;     // we will be using them soon.

bool process_record_super_alt_tab(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_super_alt_tab_kb(keycode, record)) {
        return false;
    }

    switch (keycode) { // This will do most of the grunt work with the keycodes.
        case COMMUNITY_MODULE_SUPER_ALT_TAB:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
    }
    return true;
}

void housekeeping_task_super_alt_tab(void) {
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
}
