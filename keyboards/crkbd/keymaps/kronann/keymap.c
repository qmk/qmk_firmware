#include QMK_KEYBOARD_H
#include "layers.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3_ex2(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LEFT,     KC_UP,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_RGHT,     KC_DOWN, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                          KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ESC,
                                            KC_LGUI, TL_LOWR, KC_SPC,      KC_ENT,  TL_UPPR, KC_LALT
    ),

    [_LOWER] = LAYOUT_split_3x6_3_ex2(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______,     LGUI(KC_PGUP), KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
        KC_LCTL, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______,     LGUI(KC_PGDN), KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD,
        KC_LSFT, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,                              KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, _______,
                                            _______, _______, LCTL(KC_SPC),    _______,    _______, _______
    ),

    [_RAISE] = LAYOUT_split_3x6_3_ex2(
        _______, XXXXXXX, XXXXXXX, MS_UP,   XXXXXXX, XXXXXXX, _______,     _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_PSCR, _______,
        KC_LCTL, MS_WHLU, MS_LEFT, MS_DOWN, MS_RGHT, MS_ACL0, _______,     _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX,
        KC_LSFT, MS_WHLD, MS_BTN3, MS_BTN2, MS_BTN1, XXXXXXX,                       KC_MUTE, KC_VOLD, KC_VOLU, KC_BRID, KC_BRIU, _______,
                                            MS_BTN2, TL_LOWR, MS_BTN1,     _______, _______, _______
    ),

    [_ADJUST] = LAYOUT_split_3x6_3_ex2(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   XXXXXXX,     XXXXXXX, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            XXXXXXX, _______, XXXXXXX,     XXXXXXX, _______, XXXXXXX
    ),
};

const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

const key_override_t *key_overrides[] = {
    &delete_key_override,
};
