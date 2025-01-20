#include QMK_KEYBOARD_H
#include "helpers.h"

bool is_shift_pressed(void) {
    return get_mods() & MOD_BIT(KC_LSFT);
}

bool is_ctrl_pressed(void) {
    return get_mods() & MOD_BIT(KC_LCTL);
}

bool is_alt_pressed(void) {
    return get_mods() & MOD_BIT(KC_RALT);
}

bool is_key_press(uint16_t keycode, const keyrecord_t *record) {
    if (!record->event.pressed) {
        return false;
    }
    return true;
};


