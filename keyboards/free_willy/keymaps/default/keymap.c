/* Copyright 2021 Caleb Lightfoot
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

enum layers{
  _BASE,
  _SYM,
  _NAV
};

#define KC_SYM_SPC LT(_SYM, KC_SPC)
#define KC_SFT_BCK LSFT_T(KC_BSPC)


enum combo_events {
  COMBO_NUMBAK,
  COMBO_TAB,
  COMBO_ESC,
  COMBO_DEL,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_Q,   KC_W,   KC_E,    KC_R,       KC_T,    KC_Y,     KC_U,       KC_I,    KC_O,    KC_P,
    KC_A,   KC_S,   KC_D,    KC_F,       KC_G,    KC_H,     KC_J,       KC_K,    KC_L,    KC_ENT,
    KC_Z,   KC_X,   KC_C,    KC_V,       KC_B,    KC_N,     KC_M,       KC_COMM, KC_DOT,  KC_SLSH,
                    KC_LCTL, KC_SFT_BCK, KC_LALT, KC_LGUI , KC_SYM_SPC, MO(_NAV)
  ),

  [_SYM] = LAYOUT(
    KC_1,       KC_2,     KC_3,      KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,
    KC_EXLM,    KC_AT,    KC_HASH,   KC_DLR,   KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_EQUAL, KC_MINS,
    KC_BSLS,    KC_SCLN,   KC_LCBR,   KC_LBRC,  KC_LPRN,  KC_RPRN,  KC_RBRC,  KC_RCBR,  KC_QUOT,  KC_GRV,
                          KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS
  ),

  [_NAV] = LAYOUT(
    QK_BOOT,    KC_NO,    KC_NO,    KC_NO,  KC_NO,   KC_NO,  KC_NO,    KC_NO,  KC_NO,  KC_NO,
    KC_LEFT,  KC_DOWN,  KC_UP,  KC_RGHT,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO,
    KC_NO,  KC_NO, KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,  KC_NO,   KC_NO,  KC_NO,
                   KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS
  ),
};


#ifdef COMBO_ENABLE
//const uint16_t PROGMEM combo_bspc[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM combo_numbak[] = {KC_0, KC_9, COMBO_END};
const uint16_t PROGMEM combo_tab[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM combo_esc[] = {KC_J, KC_F, COMBO_END};
const uint16_t PROGMEM combo_del[] = {KC_MINS, KC_EQL, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  //[COMBO_BSPC] = COMBO(combo_bspc,KC_BSPC),
  [COMBO_NUMBAK] = COMBO(combo_numbak,KC_BSPC),
  [COMBO_TAB] = COMBO(combo_tab,KC_TAB),
  [COMBO_ESC] = COMBO(combo_esc,KC_ESC),
  [COMBO_DEL] = COMBO(combo_del,KC_DEL),

};
#endif
