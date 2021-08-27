#include per_key.h

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MT(MOD_LGUI, KC_A):
            return TAPPING_TERM + LONG_TAPPING_TERM;
        case MT(MOD_LALT, KC_S):
            return TAPPING_TERM + LONG_TAPPING_TERM;
        case MT(MOD_LSFT, KC_D):
            return TAPPING_TERM + LONG_TAPPING_TERM;
        case MT(MOD_LCTL, KC_F):
            return TAPPING_TERM + LONG_TAPPING_TERM;
        case MT(MOD_RCTL, KC_H):
            return TAPPING_TERM + LONG_TAPPING_TERM;
        case MT(MOD_RSFT, KC_J):
            return TAPPING_TERM + LONG_TAPPING_TERM;
        case MT(MOD_RALT, KC_K):
            return TAPPING_TERM + LONG_TAPPING_TERM;
        case MT(MOD_RGUI, KC_L):
            return TAPPING_TERM + LONG_TAPPING_TERM;
        case KC_LCPO:
            return TAPPING_TERM 75;
        default:
            return TAPPING_TERM;
    }
}