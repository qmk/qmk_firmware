#include QMK_KEYBOARD_H

enum layer {
    QWERTY,
    COLEMAK,
    FUNCTION,
    ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [QWERTY] = LAYOUT_60_tsangan_hhkb(
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSLS, KC_GRV,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSPC,
        LT(2, KC_CAPS),     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  LT(2,KC_ENT),
        SC_LSPO,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  SC_RSPC,  MO(3),
        KC_LCTL,  KC_LALT,  KC_LGUI,                                          KC_SPC,                                           KC_RGUI,  KC_RALT, KC_RCTL
    ),

    [COLEMAK] = LAYOUT_60_tsangan_hhkb(
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSLS, KC_GRV,
        KC_TAB,   KC_Q,     KC_W,     KC_F,     KC_P,     KC_G,     KC_J,     KC_L,     KC_U,     KC_Y,     KC_SCLN,  KC_LBRC,  KC_RBRC,  KC_BSPC,
        LT(2, KC_CAPS),     KC_A,     KC_R,     KC_S,     KC_T,     KC_D,     KC_H,     KC_N,     KC_E,     KC_I,     KC_O,     KC_QUOT,  LT(2,KC_ENT),
        SC_LSPO,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_K,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  SC_RSPC,  MO(3),
        KC_LCTL,  KC_LALT,  KC_LGUI,                                          KC_SPC,                                           KC_RGUI,  KC_RALT, KC_RCTL
    ),

    [FUNCTION] = LAYOUT_60_tsangan_hhkb(
        XXXXXXX,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   XXXXXXX, XXXXXXX,
        XXXXXXX,  XXXXXXX,  KC_MPLY,  KC_MPRV,  KC_MNXT,  XXXXXXX,  XXXXXXX,  KC_HOME,  KC_UP,    KC_END,   KC_PSCR,  KC_SCRL,  KC_PAUS,  XXXXXXX,
        _______,            XXXXXXX,  KC_MUTE,  KC_VOLD,  KC_VOLU,  XXXXXXX,  XXXXXXX,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_DEL,   KC_INS,   _______,
        _______,            KC_UNDO,  KC_CUT,   KC_COPY,  KC_PSTE,  KC_AGIN,  XXXXXXX,  XXXXXXX,  KC_WBAK,  KC_WFWD,  KC_WREF,  _______,  KC_WHOM,
        _______,  _______,  _______,                                          _______,                                          _______,  KC_APP,  _______
    ),

    [ADJUST] = LAYOUT_60_tsangan_hhkb(
        C(A(KC_DEL)),  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_BRID,  KC_BRIU,  XXXXXXX, XXXXXXX,
        C(S(KC_ESC)),  TO(0),    XXXXXXX,  XXXXXXX,  QK_BOOT,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,            XXXXXXX,  XXXXXXX,  TO(1),    XXXXXXX,  XXXXXXX,  NK_TOGG,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,
        XXXXXXX,  XXXXXXX,  XXXXXXX,                                          _______,                                          XXXXXXX,  XXXXXXX, XXXXXXX
    ),

};
