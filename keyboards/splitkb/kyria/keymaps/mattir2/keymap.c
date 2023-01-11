/* Copyright 2020 Matthew Gilbert <hello+github@mattir.com>
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
  QWERTY,
  LOWER,
  RAISE,
  FUNCS
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [QWERTY] = LAYOUT(
      KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS,
      KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
      QK_LEAD, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_LSFT, KC_GRV, TT(FUNCS), KC_RSFT, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_MINS,
      KC_LSFT, KC_LALT, KC_LGUI, LT(LOWER, KC_SPC), LT(RAISE, KC_ENT), LT(RAISE, KC_ENT), LT(LOWER, KC_SPC), KC_BSPC, KC_LCTL, KC_RSFT
      ),
  [LOWER] = LAYOUT(
      _______, KC_EXLM, KC_AT, KC_HASH, KC_LCBR, KC_RCBR, _______, _______, _______, _______, _______, _______,
      _______, KC_DLR, KC_PERC, KC_CIRC, KC_LPRN, KC_RPRN, KC_EQL, KC_PLUS, KC_MINS, KC_ASTR, KC_SLSH, _______,
      _______, KC_AMPR, _______, _______, KC_LBRC, KC_RBRC, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
      ),
  [RAISE] = LAYOUT(
      _______, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, _______,
      KC_VOLU, _______, KC_BTN1, KC_BTN3, KC_BTN2, KC_WH_U, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_BRIU, _______,
      KC_VOLD, KC_MUTE, KC_MPRV, KC_MPLY, KC_MNXT, KC_WH_D, KC_WH_L, KC_WH_R, _______, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_BRID, _______,
      _______, _______, _______, _______, _______, _______, _______, KC_DEL, _______, _______
      ),
  [FUNCS] = LAYOUT(
      _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_PPLS, KC_P7, KC_P8, KC_P9, KC_PAST, _______,
      _______, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_PMNS, KC_P4, KC_P5, KC_P6, KC_PSLS, KC_PEQL,
      _______, KC_F11, KC_F12, _______, _______, _______, _______, _______, _______, _______, KC_P0, KC_P1, KC_P2, KC_P3, KC_PDOT, KC_PENT,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
      ),
};

LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_ONE_KEY(KC_A) {
      tap_code16(SGUI(KC_L));
    }
    SEQ_TWO_KEYS(KC_S, KC_S) {
      tap_code16(SGUI(KC_5));
    }
  }
}
