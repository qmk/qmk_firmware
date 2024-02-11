
#include "../__init__.h"

bool is_active = false;

enum pr_response swapper_pr(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        if (IS_QK_LAYER_TAP(keycode) && is_active) {
            tap_code16(KC_ENT);
            is_active = false;
        }

        return PR_IGNORE;
    }

    switch (keycode) {
        case HK_SWAP:
            is_active = true;
            return PR_IGNORE;

        case KC_ESC:
        case KC_ENT:
            is_active = false;
            return PR_IGNORE;
    }

    return PR_IGNORE;
}
