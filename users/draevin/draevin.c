#include "draevin.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CM_QW: // Switch between Colemak and QWERTY
            if (record->event.pressed) {
                layer_invert(_CM);
                layer_invert(_QW);
            }
            return false;
        case KC_MAKE:
            if (!record->event.pressed) {
                SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP ":flash\n");
                reset_keyboard();
            }
            break;
        case PRNPAIR:
            if (record->event.pressed) {
                SEND_STRING("()");
                tap_code(KC_LEFT);
            }
            break;
        case BRCPAIR:
            if (record->event.pressed) {
                uint8_t shifted = get_mods() & (MOD_MASK_SHIFT);
                    if (shifted) {
                        unregister_code(KC_LSFT);
                        unregister_code(KC_RSFT);
                        SEND_STRING("{}"SS_TAP(X_LEFT));
                        // tap_code(KC_LEFT);
                    }
                    else {
                        SEND_STRING("[]"SS_TAP(X_LEFT));
                        // tap_code(KC_LEFT);
                    }
            }
            break;
    }
    return true;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS)  // shift/caps TD
};
