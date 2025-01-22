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
bool is_alt_tab_active = false; // ADD this near the beginning of keymap.c
uint16_t alt_tab_timer = 0;     // we will be using them soon.


#include QMK_KEYBOARD_H

#define ALT_TAB     M(KC_ALT_TAB)  // Macro for Alt-Tab
enum custom_keycodes {
    SMTD_KEYCODES_BEGIN = SAFE_RANGE,
    CKC_A, // reads as C(ustom) + KC_A, but you may give any name here
    CKC_S,
    CKC_D,
    CKC_F,
    CKC_J, // reads as C(ustom) + KC_A, but you may give any name here
    CKC_K,
    CKC_L,
    CLT_1SPC,
    CLT_3TAB,
    CLT_2RET,
    CKC_GESC,
    CKC_QUOT,
    TILDE_SPC,
    KC_ALT_TAB,
    SMTD_KEYCODES_END,
};

enum {
    TD_CAPSW,
    TD_CP,
    TD_UNDO,
};

enum combos {
    BSLS_COMB,
    SLSH_COMB,
    LBRC_COMB,
    RBRC_COMB,
    LPRN_COMB,
    RPRN_COMB,
    DQUT_COMB,
    CSPC_COMB,
    OSM_L1_COMB,
    QUES_COMB,
    UND_COMB,
    COLON_COMB,
    CLN_COMB,
    SCLN_COMB,
    GRVSPC_COMB,
    PIPE_COMB,
TILDE_SPC_COMB,
};


tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_CAPSW] = ACTION_TAP_DANCE_DOUBLE(OSM(MOD_LSFT), CW_TOGG),
    [TD_CP] = ACTION_TAP_DANCE_DOUBLE(G(KC_C), G(KC_X)),
    [TD_UNDO] = ACTION_TAP_DANCE_DOUBLE(G(KC_Z), S(G(KC_Z))),
};

const uint16_t PROGMEM backslash[] = {CKC_D, KC_V, COMBO_END};
const uint16_t PROGMEM slash[] = {CKC_K, KC_M, COMBO_END};
const uint16_t PROGMEM lbracket[] = {CKC_J, CKC_K, COMBO_END};
const uint16_t PROGMEM rbracket[] = {CKC_K, CKC_L, COMBO_END};
const uint16_t PROGMEM lpar[] = {KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM rpar[] = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM dquote[] = {CKC_J, KC_I, COMBO_END};
const uint16_t PROGMEM osml1[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM cspc[] = {CKC_D, CKC_F, COMBO_END};
const uint16_t PROGMEM ques[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM und[] = {KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM cln[] = {CKC_S, CKC_D, COMBO_END};
const uint16_t PROGMEM scln[] = {KC_E, CKC_F, COMBO_END};
const uint16_t PROGMEM tilde_spc[] = {KC_I, CKC_L, COMBO_END};  // You can change these keys to your preference
const uint16_t PROGMEM pipe[] = {KC_I, CKC_K, COMBO_END};  // You can change these keys to your preference
const uint16_t PROGMEM grave[] = {KC_R, CKC_F, COMBO_END};  // You can change these keys to your preference



combo_t key_combos[] = {

    [BSLS_COMB] = COMBO(backslash, KC_BSLS),
    [SLSH_COMB] = COMBO(slash, KC_SLSH),
    [LBRC_COMB] = COMBO(lbracket, KC_LBRC),
    [RBRC_COMB] = COMBO(rbracket, KC_RBRC),
    [LPRN_COMB] = COMBO(lpar, KC_LPRN),
    [RPRN_COMB] = COMBO(rpar, KC_RPRN),
    [OSM_L1_COMB] = COMBO(osml1, OSL(1)),
    [CSPC_COMB] = COMBO(cspc, LCTL(KC_SPC)),
    [QUES_COMB] = COMBO(ques, KC_QUES),
    [UND_COMB] = COMBO(und, KC_UNDS),
    [CLN_COMB] = COMBO(cln, KC_COLN),
    [SCLN_COMB] = COMBO(scln, KC_SCLN),
    [PIPE_COMB] = COMBO(pipe, KC_PIPE),
    [GRVSPC_COMB] = COMBO_ACTION(scln),
    [TILDE_SPC_COMB] = COMBO_ACTION(tilde_spc),
    [DQUT_COMB] = COMBO_ACTION(dquote),
};


#include "sm_td.h"
#ifdef LAYOUT_split_3x5_3_ex2
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x5_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,  KC_VOLU,    KC_MUTE,   KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+---:w-----+--------+--------+--------|
      CKC_A,   CKC_S,   CKC_D,   CKC_F,   KC_G,  KC_VOLD,    KC_MPLY,   KC_H,   CKC_J,   CKC_K,   CKC_L,CKC_QUOT,
   //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                         CKC_GESC, CLT_1SPC, CLT_3TAB,                CLT_2RET, CLT_1SPC, TD(TD_CAPSW)
                                      //`--------------------------'  `--------------------------'

  ),

  [1] = LAYOUT_split_3x5_3_ex2(
  //,------------------------------------------------------.  ,--------------------------------------------------------------.
       KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_VOLU,      KC_MUTE,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
  //|--------+--------+--------+--------+--------+--------+  |--------+--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, G(KC_GRV), KC_VOLD, KC_MPLY, KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, CW_TOGG,
  //|--------+--------+--------+--------+--------+--------+  `--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, OSM(MOD_LSFT), C(KC_SPC), G(KC_TAB),                    KC_HOME, KC_PGDN, KC_PGUP, KC_END, S(KC_G),
  //|--------+--------+--------+--------+--------+--------+  ,--------+--------+--------+--------+--------+--------+--------|
                                 KC_LGUI, TD(TD_CAPSW),  KC_SPC,     KC_ENT, KC_BSPC, KC_DEL
                                      //`--------------------------'  `--------------------------'
  ),

  [2] = LAYOUT_split_3x5_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC, KC_LCTL, KC_RCTL, KC_CIRC, KC_AMPR,   KC_ASTR, KC_LPRN, KC_RPRN,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      KC_QUES, KC_UNDS, KC_COLN, KC_EQL, KC_GRV,   KC_LALT, KC_RALT, KC_MINS,  KC_LBRC,  KC_LCBR, KC_RCBR, KC_RBRC,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      KC_SCLN, KC_LT, KC_GT, KC_PLUS,   KC_TILD,                      KC_UNDS, KC_PLUS,  KC_LPRN, KC_RPRN,  KC_PIPE,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                KC_LGUI, KC_SPC,  KC_SPC,   KC_ENT, KC_BSPC, KC_LSFT
                                      //`--------------------------'  `--------------------------'
  ),

    [3] = LAYOUT_split_3x5_3_ex2(
  //,- --------------------------------------------------------------------------.  ,--------------------------------------------------------------.
      KC_ESC,    G(KC_LCBR),G(KC_RCBR),   KC_BSPC,      KC_DEL,      G(S(KC_4)),  XXXXXXX,   G(KC_ENT), S(KC_ENT), MS_UP, XXXXXXX,  XXXXXXX,
  //|--------+-------------+-------------+----------+-----------+--------+-------|  |--------+--------+--------+--------+--------+--------+--------|
      G(KC_GRV),   TD_UNDO,   TD_CP,      G(KC_V),    KC_ALT_TAB, C(G(S(KC_3))), XXXXXXX, MS_WHLL,   MS_LEFT, MS_DOWN, MS_RGHT, MS_WHLR,
   //|--------+-------------+------------+------------+--------+--------'`--------+--------+--------+--------+--------+--------+--------|
      KC_NO,     G(KC_ENT), S(KC_ENT),    KC_ENT,       G(S(KC_5)),                S(KC_ENT),    MS_WHLD, MS_WHLU, KC_ENT, XXXXXXX,
  //|--------+-------------+--------------+------------+------------+------+--------.  ,--------+--------+--------+------,--+--------+--------+--------|
                                  KC_LGUI, KC_SPC,  KC_SPC,     MS_BTN1, MS_BTN2, MS_BTN3

                                      //`--------------------------'  `--------------------------'
  ),

};
#endif

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [0] = { ENCODER_CCW_CW(RGB_MOD, RGB_RMOD), ENCODER_CCW_CW(RGB_HUI, RGB_HUD), ENCODER_CCW_CW(RGB_VAI, RGB_VAD), ENCODER_CCW_CW(RGB_SAI, RGB_SAD), },
  [1] = { ENCODER_CCW_CW(RGB_MOD, RGB_RMOD), ENCODER_CCW_CW(RGB_HUI, RGB_HUD), ENCODER_CCW_CW(RGB_VAI, RGB_VAD), ENCODER_CCW_CW(RGB_SAI, RGB_SAD), },
  [2] = { ENCODER_CCW_CW(RGB_MOD, RGB_RMOD), ENCODER_CCW_CW(RGB_HUI, RGB_HUD), ENCODER_CCW_CW(RGB_VAI, RGB_VAD), ENCODER_CCW_CW(RGB_SAI, RGB_SAD), },
  [3] = { ENCODER_CCW_CW(RGB_MOD, RGB_RMOD), ENCODER_CCW_CW(RGB_HUI, RGB_HUD), ENCODER_CCW_CW(RGB_VAI, RGB_VAD), ENCODER_CCW_CW(RGB_SAI, RGB_SAD), },
};
#endif


void on_smtd_action(uint16_t keycode, smtd_action action, uint8_t tap_count) {
    switch (keycode) {
        SMTD_MT(CKC_A, KC_A, KC_LEFT_CTRL)
        SMTD_MT(CKC_S, KC_S, KC_LEFT_ALT)
        SMTD_MT(CKC_D, KC_D, KC_LEFT_GUI)
        SMTD_MT(CKC_F, KC_F, KC_LSFT)

        SMTD_MT(CKC_J, KC_J, KC_LSFT)
        SMTD_MT(CKC_K, KC_K, KC_LEFT_GUI)
        SMTD_MT(CKC_L, KC_L, KC_LEFT_ALT)
        SMTD_MT(CKC_QUOT, KC_QUOT, KC_LEFT_CTRL)


        SMTD_LT(CLT_1SPC, KC_SPC, 1)
        SMTD_LT(CLT_2RET, KC_ENT, 2)
        SMTD_LT(CLT_3TAB, KC_TAB, 2)
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  if (!process_smtd(keycode, record)) {
    return false;
  }
  switch (keycode) { // This will do most of the grunt work with the keycodes.
    case KC_ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LGUI);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
  }
  return true;
}

void matrix_scan_user(void) { // The very important timer.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LGUI);
      is_alt_tab_active = false;
    }
  }
}


void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case TILDE_SPC_COMB:
      if (pressed) {
        tap_code16(KC_TILD);
        tap_code16(KC_SPC);
      }
      break;
    case DQUT_COMB:
      if (pressed) {
        tap_code16(KC_DQT);
        tap_code16(KC_SPC);
      }
      break;
    case GRVSPC_COMB:
      if (pressed) {
        tap_code16(KC_GRV);
        tap_code16(KC_SPC);
      }
      break;
  }
}


