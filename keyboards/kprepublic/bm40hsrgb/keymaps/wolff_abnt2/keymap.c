/* Copyright 2020 lmlask
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include <keymap_brazilian_abnt2.h>

enum layers {
  _WORKMAN,
  _QWERTY,
  _DVORAK,
  _COLEMAK,
  _MIDI,
  _GAME,
  
  _SYM,
  _FUNCTION,
  _NAV,
  _NUM,
  _ADJUST,
  _MOUSE,
  
  _CPY,
  _SWP
};

enum planck_keycodes {
  WORKMAN = QK_USER,
  QWERTY,
  DVORAK,
  COLEMAK,
  MIDI,
  GAME,
  TOG_CPY,
  TOG_SWP,
};

#define NAVTAB LT(_NAV, KC_TAB)
#define SYM LT(_SYM, KC_BSPC)
#define NUM LT(_NUM, KC_DEL)
#define FUN MO(_FUNCTION)
#define CTL_ENT RCTL_T(KC_ENT)

//Hand swap config, similar to Planck
const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
  {{11, 0}, {10, 0}, {9, 0}, {8, 0}, {7, 0}, {6, 0}, {5, 0}, {4, 0}, {3, 0}, {2, 0}, {1, 0}, {0, 0} },
  {{11, 1}, {10, 1}, {9, 1}, {8, 1}, {7, 1}, {6, 1}, {5, 1}, {4, 1}, {3, 1}, {2, 1}, {1, 1}, {0, 1} },
  {{11, 2}, {10, 2}, {9, 2}, {8, 2}, {7, 2}, {6, 2}, {5, 2}, {4, 2}, {3, 2}, {2, 2}, {1, 2}, {0, 2} },
  {{0, 3},  {1, 3},  {2, 3}, {3, 3}, {4, 3},     {5, 3},     {6, 3}, {7, 3}, {8, 3}, {9, 3}, {10, 3}},
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//BASE LAYERS
[_QWERTY] = LAYOUT_planck_mit(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    BR_ACUT,
    NAVTAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    BR_CCED, BR_TILD,
    SC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  BR_SLSH, SC_RSPC,
    KC_LCTL, KC_LGUI, KC_LALT, KC_MEH,  NUM,         KC_SPC,       SYM,     FUN,     KC_RALT, KC_HYPR, CTL_ENT
),
[_WORKMAN] = LAYOUT_planck_mit(
    KC_ESC,  KC_Q,    KC_D,    KC_R,    KC_W,    KC_B,    KC_J,    KC_F,    KC_U,    KC_P,    BR_CCED, BR_ACUT,
    NAVTAB,  KC_A,    KC_S,    KC_H,    KC_T,    KC_G,    KC_Y,    KC_N,    KC_E,    KC_O,    KC_I,    BR_TILD,
    SC_LSPO, KC_Z,    KC_X,    KC_M,    KC_C,    KC_V,    KC_K,    KC_L,    KC_COMM, KC_DOT,  BR_SLSH, SC_RSPC,
    KC_LCTL, KC_LGUI, KC_LALT, KC_MEH,  NUM,         KC_SPC,       SYM,     FUN,     KC_RALT, KC_HYPR, CTL_ENT
),
[_DVORAK] = LAYOUT_planck_mit(
    KC_ESC,  KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    BR_SLSH, BR_ACUT,
    NAVTAB,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    BR_TILD,
    SC_LSPO, BR_CCED, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    SC_RSPC,
    KC_LCTL, KC_LGUI, KC_LALT, KC_MEH,  NUM,         KC_SPC,       SYM,     FUN,     KC_RALT, KC_HYPR, CTL_ENT
),
[_COLEMAK] = LAYOUT_planck_mit(
    KC_ESC,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    BR_CCED, BR_ACUT,
    NAVTAB,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    BR_TILD,
    SC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  BR_SLSH, SC_RSPC,
    KC_LCTL, KC_LGUI, KC_LALT, KC_MEH,  NUM,         KC_SPC,       SYM,     FUN,     KC_RALT, KC_HYPR, CTL_ENT
),

//UTILITY LAYERS - SHORTCUT (CPY), SWAP HANDS (SWP)
[_CPY] = LAYOUT_planck_mit(
    _______, KC_PGUP, KC_HOME, KC_UP,   KC_END,  _______, _______, _______, _______, _______, _______, _______,
    _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______,
    _______, C(KC_Z), C(KC_X), C(KC_C), C(KC_V), _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,     _______,      _______, _______, _______, _______, _______
),
[_SWP] = LAYOUT_planck_mit(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, NUM,     SH_T(KC_BSPC),_______,     _______, _______, _______, _______, _______
),
//AUX LAYERS (NAV, SYM, NUM, FN)
[_NAV] = LAYOUT_planck_mit(
    KC_CAPS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, KC_PGUP,  KC_HOME, KC_UP,   KC_END,  C(KC_V), C(KC_Z),
    _______, KC_LALT, KC_LGUI, KC_LSFT, KC_LCTL, _______, KC_PGDN,  KC_LEFT, KC_DOWN, KC_RGHT, C(KC_C), C(KC_X),
    _______, _______, _______, _______, _______, _______, KC_ENT,   KC_BSPC, KC_DEL,  KC_VOLD, KC_VOLU, _______,
    _______, _______, _______, _______, _______,      KC_ENT,       _______, _______, KC_MPRV, KC_MPLY, KC_MNXT
),
[_SYM] = LAYOUT_planck_mit(
    BR_DQUO, BR_EXLM, BR_AT,   BR_HASH, BR_DLR,  BR_PERC, BR_DIAE, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
    BR_QUOT, BR_BSLS, BR_SCLN, KC_MINS, BR_QUOT, _______, _______, KC_PLUS, _______, BR_LBRC, BR_RBRC, _______,
    _______, BR_PIPE, BR_COLN, KC_UNDS, BR_DQUO, _______, _______, KC_EQL,  _______, BR_LCBR, BR_RCBR, _______,
    _______, _______, _______, _______, _______,     _______,      _______, _______, _______, _______, _______
),
[_NUM] = LAYOUT_planck_mit(
    _______, _______, _______, _______, _______, _______, _______, KC_7,    KC_8,    KC_9,    BR_SLSH, BR_MINS,
    _______, BR_SLSH, KC_ASTR, KC_MINS, KC_PLUS, _______, _______, KC_4,    KC_5,    KC_6,    BR_ASTR, BR_PLUS,
    _______, BR_PERC, KC_EQL,  KC_DOT,  KC_COMM, _______, _______, KC_1,    KC_2,    KC_3,    BR_COLN, BR_DOT,
    _______, _______, _______, _______, _______,     _______,      KC_0,    KC_BSPC, BR_COMM, BR_EQL,  KC_ENT
),
[_FUNCTION] = LAYOUT_planck_mit(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_SCRL, _______, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_INS,
    _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_NUM,  _______, KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_PAUS,
    _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, _______, KC_F21,  KC_F22,  KC_F23,  KC_F24,  KC_APP,
    _______, _______, _______, _______, _______,     _______,      _______, _______, KC_MPRV, KC_MPLY, KC_MNXT
),
//ADJUST LAYER FOR KEYBOARD CONTROL
[_ADJUST] = LAYOUT_planck_mit(
    QK_BOOT, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, _______, MIDI,    GAME,    _______, _______, _______,
    KC_CAPS, RGB_RMOD,RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, _______, QWERTY,  DVORAK,  COLEMAK, WORKMAN, _______,
    QK_RBT,  _______, _______, _______, _______, _______, _______, TOG_CPY, TOG_SWP, _______, _______, _______,
    RGB_TOG, _______, _______, _______, _______,     _______,      _______, _______, _______, _______, _______
),
//MOUSE LAYER
[_MOUSE] = LAYOUT_planck_mit(
    KC_ESC,   KC_BTN6, KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_WH_U, KC_WH_L, KC_MS_U, KC_WH_R, KC_BTN6, KC_NO,
    _______,  KC_BTN4, KC_BTN2, KC_BTN3, KC_BTN1, KC_NO,  KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN4, KC_NO,
    _______,  KC_BTN5, KC_ACL2, KC_ACL1, KC_ACL0, KC_NO,  KC_BTN7, KC_BTN1, KC_BTN3, KC_BTN2, KC_BTN5, _______,
    _______,  _______, _______, _______, _______,    _______,      _______, _______, _______, _______, _______
),
//MIDI
[_MIDI] = LAYOUT_planck_mit(
    MI_Cs,   MI_Ds,   MI_F,    MI_Fs,   MI_Gs,   MI_As,   MI_C,    MI_Cs1, MI_Ds1, MI_F1,  MI_Fs1,  MI_Gs1,
    MI_C,    MI_D,    MI_E,    MI_F,    MI_G,    MI_A,    MI_B,    MI_C1,  MI_D1,  MI_E,   MI_F1,   MI_G1,
    MI_BNDU, MI_OCTU, MI_TRSU, MI_VELU, KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,  MI_MODU,MI_CHNU, MI_TOGG,
    MI_BNDD, MI_OCTD, MI_TRSD, MI_VELD, MI_SOFT,     MI_SUST,      SYM,    FUN,    MI_MODD,MI_CHND, MI_AOFF
),
//GAME
[_GAME] = LAYOUT_planck_mit(
    KC_ESC,   JS_0,     JS_1,     JS_2,     JS_3,   JS_4,  JS_5,   JS_6,   JS_7,   JS_8,     JS_9,    KC_P,
    KC_TAB,   JS_10,    JS_11,    JS_12,    JS_13,  JS_14, JS_15,  JS_16,  JS_17,  JS_18,    JS_19,   KC_O,
    KC_LSFT,  JS_20,    JS_21,    JS_22,    JS_23,  JS_24, JS_25,  JS_26,  JS_27,  JS_28,    JS_29,   KC_L,
    KC_LCTL,  KC_LGUI,  KC_LALT,  KC_MEH,   NUM,       KC_SPC,     SYM,    FUN,    KC_RALT,  KC_HYPR, CTL_ENT    
),
};

//Custom keycodes code for layer switching
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
    case WORKMAN:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_WORKMAN);
      }
      return false;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
    case MIDI:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_MIDI);
      }
      return false;
    case GAME:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_GAME);
      }
      return false;
    case TOG_CPY:
      if (record->event.pressed) {
        layer_invert(_CPY);
      }
      return false;
    case TOG_SWP:
      if (record->event.pressed) {
        layer_invert(_SWP);
      }
      return false;
   }
   return true;
}

//ADJUST and MOUSE layers activation code
layer_state_t layer_state_set_user(layer_state_t state) {
   state = update_tri_layer_state(state, _FUNCTION, _SYM, _ADJUST);
   state = update_tri_layer_state(state, _NAV, _NUM, _MOUSE);
   return state;
}




