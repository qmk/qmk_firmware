/* Copyright 2020 rtwayland
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

enum layer_names {
  _BASE,
  _SYMBOL,
  _NUM,
  _NAV,
  _MEDIA,
  _WORD,
  _FKEYS,
  _NUMPAD,
  _MOUSE
};

enum {
  TD_PLAY_DO_NOT_DISTURB
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
      LT(4, KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, TD(TD_PLAY_DO_NOT_DISTURB),
      LCTL_T(KC_ESC), KC_A, KC_S, KC_D, LT(2, KC_F), KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, LT(4, KC_QUOT),
      MO(5), LGUI_T(KC_Z), KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, LGUI_T(KC_SLSH), MO(5),
      MO(3), KC_LSFT, LALT_T(KC_TAB), LT(3, KC_ENT), LT(1, KC_SPC), KC_BSPC
     ),
  [_SYMBOL] = LAYOUT(
      LCTL(KC_C), KC_TILD, KC_AT, KC_LCBR, KC_RCBR, KC_HASH, KC_ASTR, KC_CIRC, KC_AMPR, KC_PIPE, KC_BSLS, LCTL(KC_GRV),
      KC_LCTL, KC_GRV, KC_MINS, KC_LPRN, KC_RPRN, KC_EXLM, KC_QUES, KC_DLR, KC_LT, KC_GT, KC_SLSH, KC_DQUO,
      KC_LALT, KC_LGUI, KC_UNDS, KC_LBRC, KC_RBRC, KC_PLUS, KC_P0, KC_EQL, KC_PERC, KC_COLN, KC_NO, KC_NO,
      KC_NO, KC_LSFT, LALT_T(KC_TAB), KC_NO, KC_TRNS, KC_NO
     ),
  [_NUM] = LAYOUT(
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_ASTR, KC_7, KC_8, KC_9, KC_SLSH, KC_EQL,
      KC_LCTL, KC_NO, MO(7), MO(6), KC_TRNS, KC_NO, KC_PLUS, KC_4, KC_5, KC_6, KC_MINS, KC_PERC,
      KC_LALT, KC_LGUI, KC_NO, KC_NO, KC_NO, KC_NO,  KC_0, KC_1, KC_2, KC_3, KC_DOT, KC_PENT,
      KC_NO, KC_LSFT, LALT_T(KC_TAB), KC_NO, KC_SPC, KC_BSPC
     ),
  [_NAV] = LAYOUT(
      KC_NO, KC_NO, LALT(KC_RGHT), SGUI(KC_LBRC), SGUI(KC_RBRC), KC_NO, KC_HOME, KC_PGDN, KC_PGUP, KC_NO, KC_NO, KC_NO,
      KC_NO, KC_LCTL, KC_LALT, KC_LSFT, KC_LGUI, KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_NO,
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, LALT(KC_LEFT), KC_END, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
      KC_TRNS, KC_NO, KC_NO, KC_NO, KC_SPC, KC_BSPC
     ),
  [_MEDIA] = LAYOUT(
      KC_TRNS, SGUI(KC_5), SGUI(KC_3), SGUI(KC_4), MEH(KC_4), KC_VOLU, LCA(KC_U), LCAG(KC_LEFT), LCAG(KC_RGHT), LCA(KC_I), LCA(KC_EQL), LALT(LGUI(KC_PWR)),
      KC_CAPS, KC_F11, KC_MPRV, KC_MNXT, KC_MPLY, KC_VOLD, LCA(KC_LEFT), LCA(KC_DOWN), LCA(KC_UP), LCA(KC_RIGHT), LCA(KC_MINS), KC_TRNS,
      KC_BRID, KC_BRIU, LGUI(KC_MINS), LGUI(KC_PLUS), LGUI(KC_GRV), KC_MUTE, LCA(KC_J), LCA(KC_ENT), LCA(KC_C), LCA(KC_K), MEH(KC_UP), QK_BOOT,
      LCTL(LSFT(KC_TAB)), LCTL(KC_TAB), KC_NO, KC_NO, MEH(KC_RGHT), MEH(KC_LEFT)
     ),
  [_WORD] = LAYOUT(
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
      KC_NO, KC_NO, LALT(LSFT(KC_MINS)), KC_NO, LALT(LGUI(KC_F)), KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
      KC_TRNS, KC_NO, LALT(KC_MINS), KC_NO, SGUI(LALT(KC_V)),  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
      KC_NO, KC_NO, KC_NO,  KC_NO, KC_NO, KC_DEL
     ),
  [_FKEYS] = LAYOUT(
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_F12, KC_F7, KC_F8, KC_F9, KC_F17, KC_F20,
      KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_F11, KC_F4, KC_F5, KC_F6, KC_F16, KC_F19,
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_F10, KC_F1, KC_F2, KC_F3, KC_F13, KC_F18,
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
     ),
  [_NUMPAD] = LAYOUT(
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_PAST, KC_P7, KC_P8, KC_P9, KC_PSLS, KC_PEQL,
      KC_LCTL, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PPLS, KC_P4, KC_P5, KC_P6, KC_PMNS, KC_PERC,
      KC_LALT, KC_LGUI, KC_NO, KC_NO, KC_NO, KC_NO,  KC_P0, KC_P1, KC_P2, KC_P3, KC_PDOT, KC_PENT,
      KC_NO, KC_TRNS, KC_NO, KC_NO, KC_LPRN, KC_RPRN
     ),
  [_MOUSE] = LAYOUT(
      KC_NO, KC_NO, KC_NO, SGUI(KC_LBRC), SGUI(KC_RBRC), KC_NO,  KC_HOME, KC_WH_U, KC_WH_D, KC_NO, KC_NO, KC_NO,
      KC_NO, KC_NO, KC_ACL2, KC_WWW_BACK, KC_ACL0, KC_WWW_FORWARD, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_NO, KC_NO,
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_END, KC_WH_R, KC_WH_L, KC_NO, KC_NO, KC_NO,
      KC_NO, KC_NO, KC_NO, KC_NO, KC_BTN1, KC_BTN2
     ),
};

tap_dance_action_t tap_dance_actions[] = {
  [TD_PLAY_DO_NOT_DISTURB] = ACTION_TAP_DANCE_DOUBLE(KC_MPLY, KC_F6)
};