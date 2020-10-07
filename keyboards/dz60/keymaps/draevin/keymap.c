#include QMK_KEYBOARD_H
#include "draevin.h"

#define LAYOUT_wrapped(...) LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_CM] = LAYOUT_wrapped (
        HYPR_T(KC_ESC), ________________NUMBER_LEFT________________, ________________NUMBER_RIGHT_______________, KC_MINS, KC_EQL,  KC_BSPC, KC_DEL, \
        KC_TAB,         _________________COLEMAK_L1________________, _________________COLEMAK_R1________________, KC_LBRC, KC_RBRC, KC_BSLS, \
        KC_BSPC,        _________________COLEMAK_L2________________, _________________COLEMAK_R2________________, KC_QUOT,          KC_ENT, \
        TD(TD_CAPS),    XXXXXXX, _________________COLEMAK_L3________________, _________________COLEMAK_R3________________, KC_RSFT, MO(_FN), \
        KC_LCTL,        KC_LGUI, KC_LALT,                   KC_SPC,  MO(_FN),  KC_SPC,           KC_RCTL, KC_RALT, XXXXXXX, KC_RGUI, KC_HYPR
    ),

    [_QW] = LAYOUT_wrapped (
        HYPR_T(KC_ESC), ________________NUMBER_LEFT________________, ________________NUMBER_RIGHT_______________, KC_MINS, KC_EQL,  KC_BSPC, KC_DEL, \
        KC_TAB,         _________________QWERTY_L1_________________, _________________QWERTY_L1_________________, KC_LBRC, KC_RBRC, KC_BSLS, \
        KC_BSPC,        _________________QWERTY_L2_________________, _________________QWERTY_L2_________________, KC_QUOT,          KC_ENT, \
        TD(TD_CAPS),    XXXXXXX, _________________QWERTY_L3_________________, _________________QWERTY_L3_________________, KC_RSFT, MO(_FN), \
        KC_LCTL,        KC_LGUI, KC_LALT,                   KC_SPC,  MO(_FN),  KC_SPC,           KC_RCTL, KC_RALT, XXXXXXX, KC_RGUI, KC_HYPR
    ),

    [_FN] = LAYOUT_wrapped (
        KC_GRV,         _________________FROW_LEFT_________________, _________________FROW_RIGHT________________,  KC_F11,  KC_F12,  _______, _______, \
        _______,        ___________________FN_L1___________________, ___________________FN_R1___________________, _______, _______, RESET, \
        _______,        ___________________FN_L2___________________, ___________________FN_R2___________________,  _______,          _______, \
        _______,        XXXXXXX, ___________________BLANK___________________, ___________________FN_R3___________________, _______, _______, \
        _______,        ___________________BLANK___________________,                            _______, _______, _______, _______, CM_QW
    )
};
