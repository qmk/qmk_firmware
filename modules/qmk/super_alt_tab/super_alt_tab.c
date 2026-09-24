// Copyright 2025 Christopher Courtney, aka Drashna Jael're  (@drashna)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(1, 0, 0);

static bool     is_alt_tab_active = false;
static uint16_t alt_tab_timer     = 0;

#ifndef COMMUNITY_MODULE_SUPER_ALT_TAB_TIMEOUT
#    define COMMUNITY_MODULE_SUPER_ALT_TAB_TIMEOUT 1000
#endif // COMMUNITY_MODULE_SUPER_ALT_TAB_TIMEOUT
#ifndef COMMUNITY_MODULE_SUPER_ALT_TAB_MODIFIER
#    define COMMUNITY_MODULE_SUPER_ALT_TAB_MODIFIER MOD_LALT
#endif // COMMUNITY_MODULE_SUPER_ALT_TAB_MODIFIER
#ifndef COMMUNITY_MODULE_SUPER_ALT_TAB_KEY
#    define COMMUNITY_MODULE_SUPER_ALT_TAB_KEY KC_TAB
#endif // COMMUNITY_MODULE_SUPER_ALT_TAB_KEY

bool process_record_super_alt_tab(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_super_alt_tab_kb(keycode, record)) {
        return false;
    }

    switch (keycode) { // This will do most of the grunt work with the keycodes.
        case COMMUNITY_MODULE_SUPER_ALT_TAB:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_mods(COMMUNITY_MODULE_SUPER_ALT_TAB_MODIFIER);
                }
                alt_tab_timer = timer_read();
                register_code(COMMUNITY_MODULE_SUPER_ALT_TAB_KEY);
            } else {
                unregister_code(COMMUNITY_MODULE_SUPER_ALT_TAB_KEY);
            }
            break;
    }
    return true;
}

void housekeeping_task_super_alt_tab(void) {
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > COMMUNITY_MODULE_SUPER_ALT_TAB_TIMEOUT) {
            unregister_mods(COMMUNITY_MODULE_SUPER_ALT_TAB_MODIFIER);
            is_alt_tab_active = false;
        }
    }
}
