
#include "../__init__.h"

bool caps_word_press_user(uint16_t keycode) {
    uprintf("caps word - %d\n", keycode);

    switch (keycode) {
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT));
            return true;

        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case TD_UNDS:
            return true;

        case KC_DOT:
        case KC_COMM:
        case KC_LBRC:
        case KC_QUOT:
        case KC_SCLN:
            if (highest_layer == STURDY)
                return false;

            add_weak_mods(MOD_BIT(KC_LSFT));
            return true;
    }

    return false;
}
