// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "twpair_on_jis.h"

// 薙刀式
#include "naginata.h"
NGKEYS naginata_keys;

enum layer_names {
  _BASE,
  _NAGINATA,
  _LOWER,
  _RAISE,
  _ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_ortho_4x10(
        KC_K    ,KC_D    ,KC_N    ,KC_F      ,KC_Q          ,KC_J          ,KC_BSPC   ,KC_R    ,KC_U    ,KC_P    ,
        KC_W    ,KC_I    ,KC_S    ,KC_A      ,KC_G          ,KC_Y          ,KC_E      ,KC_T    ,KC_H    ,KC_B    ,
        KC_Z    ,KC_X    ,KC_V    ,KC_C      ,KC_L          ,KC_M          ,KC_O      ,KC_COMM ,KC_DOT  ,KC_SLSH ,
        KC_LALT ,KC_LSFT ,KC_LCTL ,MO(_LOWER),LSFT_T(KC_SPC),LSFT_T(KC_ENT),MO(_RAISE),KC_RCTL ,KC_RSFT ,KC_RALT
    ),

    [_LOWER] = LAYOUT_ortho_4x10(
        XXXXXXX ,XXXXXXX ,KC_COLN ,KC_SCLN ,XXXXXXX ,KC_SLSH ,KC_7    ,KC_8    ,KC_9    ,KC_MINS ,
        XXXXXXX ,KC_LBRC ,KC_LCBR ,KC_LPRN ,KC_LT   ,KC_ASTR ,KC_4    ,KC_5    ,KC_6    ,KC_PLUS ,
        XXXXXXX ,KC_RBRC ,KC_RCBR ,KC_RPRN ,KC_GT   ,KC_0    ,KC_1    ,KC_2    ,KC_3    ,KC_EQL  ,
        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
    ),

    [_RAISE] = LAYOUT_ortho_4x10(
        KC_TILD ,KC_AT   ,KC_HASH ,KC_DLR  ,XXXXXXX      ,XXXXXXX ,KC_HOME ,KC_UP   ,KC_END  ,KC_BSPC ,
        KC_CIRC ,KC_AMPR ,KC_QUES ,KC_PERC ,KC_INT3      ,XXXXXXX ,KC_LEFT ,KC_DOWN ,KC_RGHT ,KC_DEL  ,
        KC_GRV  ,KC_PIPE ,KC_EXLM ,KC_UNDS ,LALT(KC_INT3),XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
    ),

    [_ADJUST] = LAYOUT_ortho_4x10(
        QK_BOOT ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,NG_TAYO ,NGSW_WIN,XXXXXXX ,XXXXXXX ,XXXXXXX ,
        KC_SLEP ,KC_F5   ,KC_F6   ,KC_F7   ,KC_F8   ,NG_KOTI ,NGSW_MAC,NG_MLV  ,XXXXXXX ,XXXXXXX ,
        KC_WAKE ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,NG_SHOS ,NGSW_LNX,XXXXXXX ,XXXXXXX ,XXXXXXX ,
        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
    ),

    [_NAGINATA] = LAYOUT_ortho_4x10(
        NG_Q    ,NG_W    ,NG_E    ,NG_R    ,NG_T    ,NG_Y    ,NG_U    ,NG_I    ,NG_O    ,NG_P    ,
        NG_A    ,NG_S    ,NG_D    ,NG_F    ,NG_G    ,NG_H    ,NG_J    ,NG_K    ,NG_L    ,NG_SCLN ,
        NG_Z    ,NG_X    ,NG_C    ,NG_V    ,NG_B    ,NG_N    ,NG_M    ,NG_COMM ,NG_DOT  ,NG_SLSH ,
        _______ ,_______ ,_______ ,_______ ,NG_SHFT ,NG_SHFT2,_______ ,_______ ,_______ ,_______
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // 薙刀式
  if (!process_naginata(keycode, record))
    return false;
  // 薙刀式

  // typewriter pairing on jis keyboard
  if (!twpair_on_jis(keycode, record))
    return false;

  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

void matrix_init_user(void) {
  // 薙刀式
  uint16_t ngonkeys[] = {KC_Y, KC_E};
  uint16_t ngoffkeys[] = {KC_A, KC_G};
  set_naginata(_NAGINATA, ngonkeys, ngoffkeys);
  // 薙刀式
}
