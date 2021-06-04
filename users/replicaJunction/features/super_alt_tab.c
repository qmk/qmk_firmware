#include "super_alt_tab.h"

// https://docs.qmk.fm/#/feature_macros?id=super-alt%E2%86%AFtab

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

void matrix_scan_super_alt_tab(void) {
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > USER_SUPER_ALT_TAB_TIMEOUT) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
}


bool process_record_super_alt_tab(uint16_t keycode, const keyrecord_t *record) {
    if (keycode != SALTTAB) {
        return true;
    }

    if (record->event.pressed) {
        if (!is_alt_tab_active) {
            is_alt_tab_active = true;
            register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
    }
    else {
        unregister_code(KC_TAB);
    }

    return false;
}
