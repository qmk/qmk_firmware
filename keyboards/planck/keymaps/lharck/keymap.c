/* Copyright 2015-2021 Jack Humbert
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
#include "muse.h"
#include "print.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

        // MAIN LAYER
        [0] = LAYOUT_ortho_4x12(
          KC_Q, KC_W, KC_E, KC_R, KC_T, KC_NO, KC_NO, KC_Y, KC_U, KC_I, KC_O, KC_P,
          KC_A, KC_S, KC_D, KC_F, KC_G, KC_NO, KC_NO, KC_H, KC_J, KC_K, KC_L, KC_QUOT,
          MT(MOD_LGUI,KC_Z), KC_X, KC_C, MT(MOD_LALT, KC_V), KC_B, KC_NO, KC_NO, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
          KC_NO, KC_NO, MT(MOD_LCTL, KC_NO), LT(1, KC_SPC), KC_LSFT, KC_NO, KC_NO, KC_SPC, LT(2, KC_NO), KC_LALT, KC_NO, KC_NO
        ),

        // LOWER LAYER
        [1] = LAYOUT_ortho_4x12(
          KC_1, KC_2, KC_3, KC_4, KC_5, KC_NO, KC_NO, KC_6, KC_7, KC_8, KC_9, KC_0,
          KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, KC_NO, KC_NO, KC_NO, KC_LEFT, KC_UP, KC_DOWN, KC_RGHT, KC_ENT,
          KC_LBRC, KC_RBRC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_HOME, KC_PGUP, KC_PGDN, KC_END, KC_NO,
          KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_DEL, MO(3), KC_TRNS, KC_NO, KC_NO
        ),

        // RAISE LAYER 
        // 
        [2] = LAYOUT_ortho_4x12(
          KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_NO, KC_NO,KC_CIRC, KC_AMPR, KC_ASTR, KC_TILD, KC_NO,
          KC_NO, KC_NO, KC_COLON, KC_SCLN, KC_PIPE, KC_NO, KC_NO, KC_UNDS, KC_MINS, KC_PLUS, KC_EQL, KC_GRV,
          KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BSLS,
          KC_NO, KC_NO, KC_TRNS, MO(3), KC_ESC, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO
        ),

        // RAISE + LOWER LAYER
        [3] = LAYOUT_ortho_4x12(
          KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_NO, KC_NO, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,
          KC_F11, KC_F12, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, MU_ON, MU_OFF, AU_ON, AU_OFF, 
          KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, DB_TOGG, QK_BOOT, 
          KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
        )
};

const uint16_t PROGMEM comboBackspace[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM comboDeleteWord[] = {KC_J, KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM comboTab[] = {KC_D, KC_F, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(comboBackspace, KC_BSPC),
    COMBO(comboTab, KC_TAB),
    COMBO(comboDeleteWord, LCTL(KC_BSPC)),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MT(MOD_LGUI,KC_Z):
            return 120;
        default:
            return TAPPING_TERM;
    }
}