// Copyright (C) 2019, 2020  Keyboard.io, Inc
//
// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H

enum layer_names {
    _QW,
    _RS,
    _LW,
    _QWW,
};

enum custom_keycodes {
    CSS
};

#define MT_SS MT(MOD_LSFT, KC_SPACE)
#define TABALT ALT_T(KC_TAB)
#define SL LALT(KC_SPACE) // spot light
#define SS LGUI(S(KC_4))
#define SSC LGUI(LCTL(S(KC_4)))
#define MONLEFT LCTL(KC_LEFT)
#define MONDOWN LCTL(KC_DOWN)
#define MONUP LCTL(KC_UP)
#define MONRGHT LCTL(KC_RGHT)
#define MONCH LCTL(KC_SCLN)
#define LT_REISU LT(_RS, KC_LNG2) // Eisū (英数) on macOS
#define LT_LKANA LT(_LW, KC_LNG1) // Kana (かな) on macOS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QW] = LAYOUT( /* Qwerty */
            KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,     KC_U,    KC_I,    KC_O,    KC_P    ,
            KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,     KC_J,    KC_K,    KC_L,    KC_SCLN ,
            KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,     KC_TAB, KC_QUOT, KC_N,     KC_M,    KC_COMM, KC_DOT,  KC_SLSH ,
            KC_ESC,  KC_LALT, KC_LGUI, LCTL(KC_Q), LT_REISU, MT_SS,  KC_ENT,  LT_LKANA, KC_BSPC, KC_RCTL, KC_BSLS, KC_MINS ),

    [_RS] = LAYOUT( /* [> RAISE <] */
            KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
            KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
            _______, KC_LBRC, KC_LCBR, KC_PLUS, _______, KC_LCBR, KC_RCBR, _______, KC_EQL,  KC_RCBR, KC_RBRC, _______,
            _______, _______, _______, _______, _______, SSC,     SL,      _______, KC_DEL,  _______, _______, RTSEN),

    [_LW] = LAYOUT( /* [> LOWER <] */
            KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10  ,
            KC_F11,  _______, _______, _______, _______,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_F12  ,
            _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, MONLEFT, MONDOWN, MONUP,   MONRGHT, MONCH ,
            KC_GRV,  _______, _______, _______, _______, SS     , _______, _______, _______, _______, _______, KC_TILDE ),
};

// ブラウザスクショを取る関数
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CSS:
            if (record->event.pressed) {
                SEND_STRING(SS_LSFT(SS_LGUI("p"))); // selects all and copies
                SEND_STRING("Capture full size screenshot\n");
            } else {
                // when keycode QMKBEST is released
            }
            break;
    }
    return true;
};

