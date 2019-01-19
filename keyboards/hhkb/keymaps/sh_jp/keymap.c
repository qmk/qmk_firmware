#include QMK_KEYBOARD_H

#define _______ KC_TRNS

enum
{
    DVOR,
    QWER,
    NEW_CMD,
    SYMB,
    FUNC
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DVOR] = LAYOUT_JP(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_LBRC, KC_RBRC, KC_JYEN, KC_BSPC,
        KC_TAB, KC_QUOT, KC_COMM, KC_DOT, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, KC_SLSH, KC_EQL,
        KC_LCTL, KC_A, KC_O, KC_E, KC_U, KC_I, KC_D, KC_H, KC_T, KC_N, KC_S, KC_MINS, KC_BSLS, KC_ENT,
        KC_LSFT, KC_SCLN, KC_Q, KC_J, KC_K, KC_X, KC_B, KC_M, KC_W, KC_V, KC_Z, KC_RO, KC_UP, KC_RSFT,
        MO(FUNC), KC_ZKHK, KC_LALT, MO(NEW_CMD), MO(SYMB), MT(MOD_LSFT, KC_SPC), MO(SYMB), KC_TAB, KC_RGUI, TG(QWER), KC_LEFT, KC_DOWN, KC_RGHT),
    [QWER] = LAYOUT_JP(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_JYEN, KC_BSPC,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC,
        KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_BSLS, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RO, KC_UP, KC_RSFT,
        MO(FUNC), KC_ZKHK, KC_LALT, MO(NEW_CMD), MO(SYMB), MT(MOD_LSFT, KC_SPC), MO(SYMB), KC_TAB, KC_RGUI, _______, KC_LEFT, KC_DOWN, KC_RGHT),

    [NEW_CMD] = LAYOUT_JP(
        _______, LGUI(KC_1), LGUI(KC_2), LGUI(KC_3), LGUI(KC_4), LGUI(KC_5), LGUI(KC_6), LGUI(KC_7), LGUI(KC_8), LGUI(KC_9), LGUI(KC_0), _______, _______, _______, LGUI(KC_BSPC),
        _______, LGUI(KC_Q), LGUI(KC_W), LGUI(KC_E), LGUI(KC_R), LGUI(KC_T), LGUI(KC_Y), LGUI(KC_U), LGUI(KC_I), LGUI(KC_O), LGUI(KC_P), LGUI(KC_LBRC), LGUI(KC_RBRC),
        _______, LGUI(KC_A), LGUI(KC_S), LGUI(KC_D), LGUI(KC_F), LGUI(KC_G), LGUI(KC_H), LGUI(KC_J), LGUI(KC_K), LGUI(KC_L), _______, _______, _______, _______,
        LGUI(KC_LSFT), LGUI(KC_Z), LGUI(KC_X), LGUI(KC_C), LGUI(KC_V), LGUI(KC_B), LGUI(KC_N), LGUI(KC_M), LGUI(KC_COMM), LGUI(KC_DOT), LGUI(KC_SLSH), _______, _______, _______,
        _______, _______, _______, _______, _______, LGUI(KC_SPC), _______, _______, _______, _______, LGUI(KC_LEFT), LGUI(KC_DOWN), LGUI(KC_RGHT)),

    [SYMB] = LAYOUT_JP(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, KC_LBRC, KC_RBRC, _______, _______, LSFT(KC_LBRC), LSFT(KC_RBRC), _______, _______, _______, _______,
        _______, LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_4), LSFT(KC_5), LSFT(KC_6), LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), LSFT(KC_0), _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

    [FUNC] = LAYOUT_JP(
        KC_PWR, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_INS, KC_DEL,
        KC_CAPS, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, KC_UP, _______,
        _______, KC_VOLD, KC_VOLU, KC_MUTE, KC_PWR, _______, KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT, _______, KC_PENT,
        _______, _______, _______, _______, _______, _______, KC_PPLS, KC_PMNS, KC_END, KC_PGDN, KC_DOWN, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______)};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t macro_id, uint8_t opt)
{
    return MACRO_NONE;
}
