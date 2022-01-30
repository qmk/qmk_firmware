#include QMK_KEYBOARD_H
#include <keymap_jp.h>

bool tap_jp_code(uint16_t keycode, keyrecord_t *record) {
    if(!record->event.pressed) return true;

    bool lshift = get_mods() & MOD_BIT(KC_LSFT);
    bool rshift = get_mods() & MOD_BIT(KC_RSFT);
    uint16_t k = lshift | rshift ? (keycode | QK_LSFT) : keycode;

    switch (k) {
        case KC_LPRN : k = JP_LPRN; break;
        case KC_RPRN : k = JP_RPRN; break;
        case KC_AT   : k = JP_AT  ; break;
        case KC_LBRC : k = JP_LBRC; break;
        case KC_RBRC : k = JP_RBRC; break;
        case KC_LCBR : k = JP_LCBR; break;
        case KC_RCBR : k = JP_RCBR; break;
        case KC_MINS : k = JP_MINS; break;
        case KC_EQL  : k = JP_EQL ; break;
        case KC_BSLS : k = JP_BSLS; break;
        case KC_SCLN : k = JP_SCLN; break;
        case KC_QUOT : k = JP_QUOT; break;
        case KC_GRV  : k = JP_GRV ; break;
        case KC_PLUS : k = JP_PLUS; break;
        case KC_COLN : k = JP_COLN; break;
        case KC_UNDS : k = JP_UNDS; break;
        case KC_PIPE : k = JP_PIPE; break;
        case KC_DQT  : k = JP_DQUO; break;
        case KC_ASTR : k = JP_ASTR; break;
        case KC_TILD : k = JP_TILD; break;
        case KC_AMPR : k = JP_AMPR; break;
        case KC_CIRC : k = JP_CIRC; break;
        default      : return true;
    }

    unregister_code(KC_LSFT);
    unregister_code(KC_RSFT);
    if(((k & QK_LSFT) == QK_LSFT) | ((k & QK_RSFT) == QK_RSFT)) {
        register_code(KC_LSFT);
        tap_code(k);
        unregister_code(KC_LSFT);
    } else {
        tap_code(k);
    }
    if (lshift) register_code(KC_LSFT);
    if (rshift) register_code(KC_RSFT);

    return false;
}
