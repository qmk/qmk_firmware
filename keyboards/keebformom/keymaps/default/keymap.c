/* Copyright 2022 Sandipratama
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


enum layers {
    _FIRST = 0,
    _SECOND,
    _THIRD,
    _FOURTH
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* FIRST
 * ,---------------------------------------------------------------------.
 * |   Q (ESC) W |   E  |   R  |   T  |   Y  |   U  |   I  |   O(DEL) P  |
 * |------+------+------+------+------+------+------+------+------+------|
 * |   A (TAB) S |   D  |   F  |   G(TO 1)H  |   J  |   K  |   L(CAPS);: |
 * |------+------+------+------+------+------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B(TO 2)N  |   M  |  ,<  |  .>(TO3)/?  |
 * |------+------+------+------+------+------+------+------+------+------|
 * | CTRL |  ALT | SHIFT|  L2  |ENTER | SPACE|   L1 | MUTE | PLAY | BSPC |
 * `---------------------------------------------------------------------'
 */
[_FIRST] = LAYOUT_ortho_4x10(
  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
  KC_LCTL, KC_LALT, KC_LSFT, MO(1),   KC_ENT,  KC_SPC, MO(2),    KC_MUTE, KC_MPLY, KC_BSPC
),
/* SECOND
 * ,---------------------------------------------------------------------.
 * |   !  |   @  |   {  |   }  |   '  |   "  |   -  |   7  |   8  |   9  |
 * |------+------+------+------+------+-------------+------+------+------|
 * |   #  |   $  |   (  |   )  |   ^  |   _  |   +  |   4  |   5  |   6  |
 * |------+------+------+------+------+------+------+------+------+------|
 * |   %  |   &  |   [  |   ]  |   *  |      |      |   1  |   2  |   3  |
 * |------+------+------+------+------+------+------+------+------+------|
 * | BASE |      |   \  |   |  |      |      |      |   =  |   0  | BSPC |
 * `---------------------------------------------------------------------'
 */

[_SECOND] = LAYOUT_ortho_4x10(
  KC_EXLM,    KC_AT,     KC_LCBR,    KC_RCBR,   KC_QUOT,   KC_DQT,     KC_PLUS,     KC_7,       KC_8,       KC_9,
  KC_HASH,    KC_DLR,    KC_LPRN,    KC_RPRN,   KC_CIRC,   KC_UNDS,     KC_MINS,    KC_4,       KC_5,       KC_6,
  KC_PERC,    KC_AMPR,   KC_LBRC,    KC_RBRC,   KC_ASTR,   _______,    _______,     KC_1,       KC_2,       KC_3,
  TO(0),      _______,   KC_BSLS,    KC_PIPE,   _______,   _______,    _______,     KC_EQL,     KC_0,       KC_BSPC
),

/* THIRD
 * ,---------------------------------------------------------------------.
 * |  INS | HOME | PGUP |      | CAPT |SELECT|      |      |  UP  |      |
 * |------+------+------+------+------+-------------+------+------+------|
 * |  DEL | END  | PGDN |      | SAVE | COPY |      | LEFT | DOWN | RGHT |
 * |------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | MYCMP| PASTE|      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------|
 * | BASE |      |      |      |      |      |      | VOLD |      | VOLU |
 * `---------------------------------------------------------------------'
 */
[_THIRD] = LAYOUT_ortho_4x10(
  KC_INS,  KC_HOME, KC_PGUP, KC_NO,    SGUI(KC_S),   LCTL(KC_A),   KC_NO,    KC_NO,   KC_UP,   KC_NO,
  KC_DEL,  KC_END,  KC_PGDN, KC_NO,    LCTL(KC_S),   LCTL(KC_C),   KC_NO,    KC_LEFT, KC_DOWN, KC_RGHT,
  KC_NO,   KC_NO,   KC_NO,   KC_NO,    LWIN(KC_E),   LCTL(KC_V),   KC_NO,    KC_NO,   KC_NO,   KC_NO,
  TO(0),   _______, _______, _______,  _______,      _______,      _______,  KC_VOLD, _______, KC_VOLU
),
/* FOURTH
 * ,---------------------------------------------------------------------.
 * |RGB M+|  HUD |  HUI |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |
 * |------+------+------+------+------+-------------+------+------+------|
 * |RGB M-|  SAD |  SAI |      |  F7  |  F8  |  F9  |  F10 | F11  | F12  |
 * |------+------+------+------+------+------+------+------+------+------|
 * |RGB TG|  VAD |  VAI |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------|
 * | BASE |      |      |      |      |      |      |      |      |      |
 * `---------------------------------------------------------------------'
 */
[_FOURTH] = LAYOUT_ortho_4x10(
  RGB_MOD, RGB_HUD, RGB_HUI, KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,
  RGB_RMOD,RGB_SAD, RGB_SAI, KC_NO,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  RGB_TOG, RGB_VAD, RGB_VAI, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  TO(0),   _______, _______, _______, _______, _______, _______, _______, _______, _______
)
};

// Combo key
const uint16_t PROGMEM test_combo1[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM test_combo2[] = {KC_MPLY, KC_BSPC, COMBO_END};
const uint16_t PROGMEM test_combo3[] = {KC_L, KC_SCLN, COMBO_END};
const uint16_t PROGMEM test_combo4[] = {KC_A, KC_S, COMBO_END};
const uint16_t PROGMEM test_combo5[] = {KC_G, KC_H, COMBO_END};
const uint16_t PROGMEM test_combo6[] = {KC_B, KC_N, COMBO_END};
const uint16_t PROGMEM test_combo7[] = {KC_O, KC_P, COMBO_END};
combo_t key_combos[] = {
    COMBO(test_combo1, KC_ESC),
    COMBO(test_combo2, TO(3)),
    COMBO(test_combo3, KC_CAPS),
    COMBO(test_combo4, KC_TAB),
    COMBO(test_combo5, TO(1)),
    COMBO(test_combo6, TO(2)),
    COMBO(test_combo7, KC_DEL),
};
