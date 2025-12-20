#include QMK_KEYBOARD_H
#include "translate_ansi_to_jis.h"

#define HANDLED false
#define NOT_HANDLED true

const uint16_t translate_map[][2] = {
    // clang-format off
    // ANSI   JIS
    {KC_EQL,  S(KC_MINS)},
    {KC_LBRC, KC_RBRC},
    {KC_BSLS, KC_INT3},
    {KC_RBRC, KC_NUHS},
    {KC_QUOT, S(KC_7)},
    {KC_GRV,  S(KC_LBRC)},
    {KC_RPRN, S(KC_9)},
    {KC_AT,   KC_LBRC},
    {KC_CIRC, KC_EQL},
    {KC_AMPR, S(KC_6)},
    {KC_ASTR, S(KC_QUOT)},
    {KC_LPRN, S(KC_8)},
    {KC_PLUS, S(KC_SCLN)},
    {KC_UNDS, S(KC_INT1)},
    {KC_LCBR, S(KC_RBRC)},
    {KC_PIPE, S(KC_INT3)},
    {KC_RCBR, S(KC_NUHS)},
    {KC_COLN, KC_QUOT},
    {KC_DQT,  S(KC_2)},
    {KC_TILD, S(KC_EQL)},
    // clang-format on
};

const size_t rows = sizeof(translate_map) / sizeof(translate_map[0]);

uint16_t find(uint16_t kc) {
    for (size_t index = 0; index < rows; index++) {
        if (translate_map[index][0] == kc) return translate_map[index][1];
    }
    return 0;
}

#define PUSH_NONE 0
// Assumes that multiple symbolic keys will never be used at the same time.
uint16_t pushing_shift_embeded_basic_kc = PUSH_NONE;

bool process_record_user_a2j(uint16_t kc, keyrecord_t *record) {
    if (kc > QK_MOD_TAP_MAX) return NOT_HANDLED;

    uint8_t mods_kc  = QK_MODS_GET_MODS(kc);
    uint8_t basic_kc = QK_MODS_GET_BASIC_KEYCODE(kc);

    if (record->event.pressed) {
        uint8_t  mod_state                    = get_mods();
        bool     shift_state_or_shift_embeded = (mod_state | mods_kc) & MOD_MASK_SHIFT;
        uint16_t shift_embeded_basic_kc       = shift_state_or_shift_embeded ? S((uint16_t)basic_kc) : basic_kc;
        uint16_t shift_embeded_basic_jis_kc   = find(shift_embeded_basic_kc);

        if (!shift_embeded_basic_jis_kc) return NOT_HANDLED;

        if (pushing_shift_embeded_basic_kc != PUSH_NONE) {
            uint16_t pushing_basic_kc = QK_MODS_GET_BASIC_KEYCODE(pushing_shift_embeded_basic_kc);
            unregister_code16(pushing_basic_kc);
        }

        if (mod_state & MOD_MASK_SHIFT) {
            del_mods(MOD_MASK_SHIFT);
            register_code16(shift_embeded_basic_jis_kc);
            set_mods(mod_state);
        } else {
            register_code16(shift_embeded_basic_jis_kc);
        }
        pushing_shift_embeded_basic_kc = shift_embeded_basic_kc;
        return HANDLED;
    }

    // if keycode is the same as previous one without mods.
    if (basic_kc == QK_MODS_GET_BASIC_KEYCODE(pushing_shift_embeded_basic_kc)) {
        unregister_code16(find(pushing_shift_embeded_basic_kc));
        pushing_shift_embeded_basic_kc = PUSH_NONE;
        return HANDLED;
    }

    return NOT_HANDLED;
}
