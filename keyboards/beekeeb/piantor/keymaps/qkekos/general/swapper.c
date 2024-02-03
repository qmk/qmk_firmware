
#include "../__init__.h"

bool is_active = false;

bool swapper_pr(uint16_t keycode, keyrecord_t *record, bool *return_value) {
    if (!record->event.pressed) {
        if (IS_QK_LAYER_TAP(keycode) && is_active) {
            tap_code16(KC_ENT);
            is_active = false;
        }

        return false;
    }

    switch (keycode) {
        case HK_SWAP:
            is_active = true;
            return false;

        case KC_ESC:
        case KC_ENT:
            is_active = false;
            return false;
    }

    return false;
}
