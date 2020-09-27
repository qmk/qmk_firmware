/* Copyright 2020 keyboard-magpie
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


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.  


enum centromere_layers
{
    _BASE,
    _SYMB,
    _NUMB,
};

  enum combo_events {
    COMBO_BSPC,
    COMBO_TAB,
    COMBO_ESC,
    COMBO_DEL,
    COMBO_UNDS,
    COMBO_BKSL,
    COMBO_LESS,
    COMBO_MORE,
    COMBO_QUOT,
    COMBO_DASH,
      };


      /* Combomap
 *
 * ,-----------------------------.       ,--------------------------------.
 * |      |    ESC    |     |     |      |     |           |    BSLH      |
 * |-----+-----+-----+-----+------|      |--------------------------------|
 * |      |   BSPC          |     |      |    LES  |  GRT   |             |
 * |-----+-----+-----+--RMB+-LMB--+      |--------------------------------|
 * |      |   MINS    |     |     |      |    QUO  | UNDR   |     |       |
 * `------+-----+-----+------+----'      `--------------------------------'
 *  .-------------------------.           .-----------------.
 *  |        |       |        |           |        |    |   |
 *  '-------------------------'           '-----------------'
 */
 
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Keymap 0: Basic layer
     *
     * ,-----------------------------.       ,--------------------------------.
     * |    Q |  W  |  E  |  R  |  T  |      |  Y  |  U  |  I  |  O  |    P   |
     * |-----+-----+-----+-----+------|      |--------------------------------|
     * |CTRL/A|  S  |  D  |  F  |  G  |      |  H  |  J  |  K  |  L  | CTRL/; |
     * |-----+-----+-----+-----+------+      |--------------------------------|
     * |SHFT/Z|  X  |  C  |  V  |  B  |      |  N  |  M  |  <  |  >  | SHFT/? |
     * `------+-----+-----+------+----'      `--------------------------------'
     *  .-------------------------.           .-----------------.
     *  |ESC/META|ENT/ALT|SPC(SYM)|           |SPC(NUM)|BSPC|TAB|
     *  '-------------------------'           '-----------------'
 */

[_BASE] = LAYOUT(
  KC_NO,   KC_Q,                  KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,                     KC_NO,
  KC_NO,   MT(MOD_LCTL, KC_A),    KC_S,    KC_D,    KC_F,    KC_G,         KC_H,    KC_J,    KC_K,    KC_L,    MT(MOD_LCTL, KC_SCLN),    KC_NO,
  KC_NO,   MT(MOD_RSFT, KC_Z),    KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M,    KC_COMM, KC_DOT,  MT(MOD_RSFT, KC_SLSH),    KC_NO,
  MT(MOD_LGUI, KC_ESC), MT(MOD_LALT, KC_ENT), LT(_SYMB, KC_SPC), LT(_NUMB, KC_SPC), KC_LSFT, MT(MOD_RSFT, KC_TAB)
  ),

    /* Keymap 1: Symbols layer
     * ,-----------------------------.       ,--------------------------------.
     * |  !   |  @  |  {  |  }  |       |  `  |  ~  |     |     |    \   |
     * |-----+-----+-----+-----+------|      |--------------------------------|
     * |  #   |  $  |  (  |  )  | LMB |      |  +  |  -  |  /  |  *  |    '   |
     * |-----+-----+-----+-----+------+      |--------------------------------|
     * |  %   |  ^  |  [  |  ]  | RMB |      |  &  |  =  |  ,  |  .  |   -    |
     * `------+-----+-----+------+----'      `--------------------------------'
     *          .-----------------.           .------------------.
     *          |MMB |  ;   |  =  |           |  =  |  ;  |  DEL |
     *          '-----------------'           '------------------'
 */
[_SYMB] = LAYOUT(
 KC_NO, KC_EXLM, KC_AT, KC_LCBR, KC_RCBR, KC_PIPE,        KC_GRV, KC_TILD, KC_TRNS, KC_TRNS, KC_BSLS, KC_NO,
 KC_NO, KC_HASH, KC_DLR, KC_LPRN, KC_RPRN, KC_BTN2,       KC_PLUS, KC_MINS, KC_SLSH, KC_ASTR, KC_QUOT, KC_NO,
 KC_NO, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_BTN1,      KC_AMPR, KC_EQL, KC_COMM, KC_DOT, KC_MINS, KC_NO,
 CMB_TOG, KC_SCLN, KC_EQL, KC_EQL, KC_SCLN, KC_DEL 
  ),

    /* Keymap 2: Pad/Function layer
     * ,-----------------------------.       ,-------------------------------.
     * |  1   |  2  |  3  |  4  |  5  |      |  6  |  7  |  8  |  9  |   0   |
     * |-----+-----+-----+-----+------|      |-------------------------------|
     * |  F1  | F2  | F3  | F4  |  F5 |      | LFT | DWN | UP  | RGT | VOLUP |
     * |-----+-----+-----+-----+------+      |-------------------------------|
     * |  F6  | F7  | F8  | F9  | F10 |      |MLFT | MDWN| MUP | MRGT| VOLDN |
     * `------+-----+-----+------+----'      `-------------------------------'
     *          .-----------------.           .-----------------.
     *          | F11 | F12|      |           |     | PLY | SKP |
     *          '-----------------'           '-----------------'
 */
[_NUMB] = LAYOUT(
     KC_NO, KC_1, KC_2, KC_3, KC_4, KC_5,           KC_6, KC_7, KC_8, KC_9, KC_0, KC_NO,
     KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,      KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_VOLU, KC_NO,
     KC_NO, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,     KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_VOLD, KC_NO, 
     KC_F11, KC_F12, KC_TRNS, KC_TRNS, KC_MPLY, KC_MNXT
     ),

};


// layer_state_t layer_state_set_user(layer_state_t state) {
//   return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
// }

#ifdef COMBO_ENABLE
const uint16_t PROGMEM combo_bspc[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM combo_tab[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM combo_esc[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM combo_del[] = {KC_A, KC_S, COMBO_END};
const uint16_t PROGMEM combo_unds[] = {KC_M, KC_COMM,  COMBO_END};
const uint16_t PROGMEM combo_bksl[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM combo_less[] = {KC_H, KC_J, COMBO_END};
const uint16_t PROGMEM combo_more[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM combo_quot[] = {KC_N, KC_M, COMBO_END};
const uint16_t PROGMEM combo_dash[] = {KC_X, KC_C, COMBO_END};
  
combo_t key_combos[COMBO_COUNT] = {
    [COMBO_BSPC] = COMBO(combo_bspc,KC_BSPC),
    [COMBO_TAB] = COMBO(combo_tab,KC_TAB),
    [COMBO_ESC] = COMBO(combo_esc,KC_ESC),
    [COMBO_DEL] = COMBO(combo_del,KC_DEL),
    [COMBO_UNDS] = COMBO(combo_unds, KC_UNDS),
    [COMBO_BKSL] = COMBO(combo_bksl,KC_BSLS),
    [COMBO_LESS] = COMBO(combo_less,KC_LT),
    [COMBO_MORE] = COMBO(combo_more,KC_GT),
    [COMBO_QUOT] = COMBO(combo_quot, KC_QUOT),
    [COMBO_DASH] = COMBO(combo_dash, KC_MINS),  
};
#endif
