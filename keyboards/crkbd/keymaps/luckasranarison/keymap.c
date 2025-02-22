/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

enum custom_keycods {
    KC_MSFN = SAFE_RANGE,
};

enum combos {
    CB_LGUI,
    CB_LSFT,
    CB_LCTL,
    CB_LALT,
    CB_RALT,
    CB_RCTL,
    CB_RSFT,
    CB_RGUI,
};

const uint16_t PROGMEM cb_lgui[] = {KC_A, KC_S, COMBO_END};
const uint16_t PROGMEM cb_lsft[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM cb_lctl[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM cb_lalt[] = {KC_S, KC_F, COMBO_END};
const uint16_t PROGMEM cb_ralt[] = {KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM cb_rctl[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM cb_rsft[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM cb_rgui[] = {KC_L, KC_SCLN, COMBO_END};

combo_t key_combos[] = {
    [CB_LGUI] = COMBO(cb_lgui, KC_LGUI),
    [CB_LSFT] = COMBO(cb_lsft, KC_LSFT),
    [CB_LCTL] = COMBO(cb_lctl, KC_LCTL),
    [CB_LALT] = COMBO(cb_lalt, KC_LALT),
    [CB_RALT] = COMBO(cb_ralt, KC_RALT),
    [CB_RCTL] = COMBO(cb_rctl, KC_RCTL),
    [CB_RSFT] = COMBO(cb_rsft, KC_RSFT),
    [CB_RGUI] = COMBO(cb_rgui, KC_RGUI),
};

#define TH_ENSH RSFT_T(KC_ENT)
#define TD_MSFN LT(3, KC_MSFN)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3( //                                   BASE
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            MO(4),   MO(1),  KC_SPC,    TH_ENSH, TD_MSFN,  OSL(5)
                                      //`--------------------------'  `--------------------------'
  ),

    [1] = LAYOUT_split_3x6_3( //                               SYMBOL/NUMBER
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, KC_PIPE,                      KC_PLUS,    KC_1,    KC_2,    KC_3, KC_MINS, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_ASTR, KC_SLSH, KC_LPRN, KC_RPRN, KC_BSLS,                       KC_EQL,    KC_4,    KC_5,    KC_6, KC_UNDS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_TILD, KC_EXLM, KC_HASH, KC_PERC,   KC_AT,                      KC_AMPR,    KC_7,    KC_8,    KC_9,  KC_DLR, KC_CIRC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, _______, _______,    _______,    KC_0, XXXXXXX
                                      //`--------------------------'  `--------------------------'

  ),

    [2] = LAYOUT_split_3x6_3( //                                   MOUSE
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, XXXXXXX, XXXXXXX, XXXXXXX, MS_WHLU, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, MS_WHLL, MS_BTN2, MS_BTN1, MS_WHLR,                      MS_LEFT, MS_DOWN,   MS_UP, MS_RGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MS_WHLD, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, _______,   _______,   TG(2), XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

    [3] = LAYOUT_split_3x6_3( //                                   EDIT
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       KC_INS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX,  KC_CUT, KC_PSTE, KC_COPY, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, KC_LCTL, KC_LSFT, KC_LALT, XXXXXXX,                       KC_DEL, KC_RALT, KC_RSFT, KC_RCTL, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, XXXXXXX, XXXXXXX,    XXXXXXX, _______, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

    [4] = LAYOUT_split_3x6_3_ex2( //                             FUNCTION
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, KC_VOLU,    KC_BRIU,  KC_PWR,   KC_F1,   KC_F2,   KC_F3,  KC_F10, KC_HOME,
  //|--------+--------+--------+--------+--------+--------|--------|  |--------+--------+--------+--------+--------+--------+--------|
      RM_TOGG, RM_HUEU, RM_SATU, RM_VALU, KC_MPRV, KC_MNXT, KC_VOLD,    KC_BRID, KC_SLEP,   KC_F4,   KC_F5,   KC_F6,  KC_F11, KC_PGUP,
  //|--------+--------+--------+--------+--------+--------|--------|  |--------+--------+--------+--------+--------+--------+--------|
      RM_NEXT, RM_HUED, RM_SATD, RM_VALD, KC_MSTP, KC_MPLY,                      KC_WAKE,   KC_F7,   KC_F8,   KC_F9,  KC_F12, KC_PGDN,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, KC_LALT,  KC_ENT,    KC_RCTL, KC_RSFT, KC_RGUI
                                      //`--------------------------'  `--------------------------'
  ),

    [5] = LAYOUT_split_3x6_3( //                               MACRO/SECRETS
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT, XXXXXXX, XXXXXXX,    MC_0, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    MC_2, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                         MC_1, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case TD_MSFN:
        if (record->tap.count && record->event.pressed) {
            layer_invert(2);
            return false;
        }
        break;

    // TODO: Implent macros with a secret system

    default:
        break;
    }

    return true;
}

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [2] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [3] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
};
#endif
