// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer_names {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_ortho_4x10(
        KC_Q,    KC_W,    KC_E,    KC_R,      KC_T,          KC_Y,          KC_U,      KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,      KC_G,          KC_H,          KC_J,      KC_K,    KC_L,    KC_SCLN,
        KC_Z,    KC_X,    KC_C,    KC_V,      KC_B,          KC_N,          KC_M,      KC_COMM, KC_DOT,  KC_SLSH,
        KC_LCTL, KC_LSFT, KC_LALT, MO(_LOWER),LSFT_T(KC_SPC),LSFT_T(KC_ENT),MO(_RAISE),KC_BSPC, KC_DEL,  KC_RSFT
    ),
    
    [_LOWER] = LAYOUT_ortho_4x10(
        KC_TAB  ,KC_COLN ,KC_SCLN ,KC_DQT  ,KC_QUOT ,KC_SLSH ,KC_7    ,KC_8    ,KC_9    ,KC_MINS ,
        KC_ESC  ,KC_LBRC ,KC_LCBR ,KC_LPRN ,XXXXXXX ,KC_ASTR ,KC_4    ,KC_5    ,KC_6    ,KC_PLUS ,
        XXXXXXX ,KC_RBRC ,KC_RCBR ,KC_RPRN ,XXXXXXX ,KC_0    ,KC_1    ,KC_2    ,KC_3    ,KC_EQL  ,
        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
    ),

    [_RAISE] = LAYOUT_ortho_4x10(
        KC_TILD ,KC_AT   ,KC_HASH ,KC_DLR  ,XXXXXXX        ,XXXXXXX ,KC_HOME ,KC_UP   ,KC_END  ,KC_DEL  ,
        KC_CIRC ,KC_AMPR ,KC_QUES ,KC_PERC ,KC_INT3      ,XXXXXXX ,KC_LEFT ,KC_DOWN ,KC_RGHT ,KC_BSPC ,
        KC_GRV  ,KC_PIPE ,KC_EXLM ,KC_UNDS ,LALT(KC_INT3),XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
    ),

    [_ADJUST] = LAYOUT_ortho_4x10(
        QK_BOOT ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,XXXXXXX ,XXXXXXX,XXXXXXX ,QK_RBT  ,XXXXXXX ,
        KC_SLEP ,KC_F5   ,KC_F6   ,KC_F7   ,KC_F8   ,XXXXXXX ,XXXXXXX,XXXXXXX  ,XXXXXXX ,XXXXXXX ,
        KC_WAKE ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,XXXXXXX ,XXXXXXX,XXXXXXX ,XXXXXXX ,XXXXXXX ,
        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
    ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}