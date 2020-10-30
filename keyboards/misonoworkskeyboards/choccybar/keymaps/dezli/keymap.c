/* Copyright 2020 dezli
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
    DEFAULT,
    NUMSYM,
    NAV,
    QWERTY,
    GAMING,
    GAMINGCHAT,
};

enum my_keycodes {
     KC_CHAT = SAFE_RANGE, // Activate chat and go to chat layer
     KC_COMMAND, // activate chat with commands, and go to chat layer
     KC_MCENT, // exit chat with enter, and go back to gaming layer
     KC_MCESC, // above, but with escape
     };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [DEFAULT] = LAYOUT(
		KC_QUOT, KC_COMM, KC_DOT, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, KC_SLSH, KC_BSPC, KC_1, KC_2, KC_3,
		KC_A, KC_O, KC_E, KC_U, KC_I, KC_D, KC_H, KC_T, KC_N, KC_S, KC_ENT, KC_4, KC_5, KC_6,
		KC_SCLN, KC_Q, KC_J, KC_K, KC_X, KC_B, KC_M, KC_W, KC_V, KC_Z, KC_UP, KC_7, KC_8, KC_9,
		KC_LCTL, LM(QWERTY, MOD_LGUI), KC_LALT, LT(NUMSYM, KC_SPC), KC_LSFT, MO(NAV), KC_LGUI, KC_LEFT, KC_DOWN, KC_RGHT, KC_0, KC_LSFT),

    [NUMSYM] = LAYOUT(
		KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_SLSH, KC_LPRN, KC_RPRN, KC_BSPC, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSLS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_NO, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, KC_GRAVE, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),


	  [NAV] = LAYOUT(
		KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, RGB_MOD, RGB_RMOD, RGB_SAI,
		TO(GAMING), TO(GAMING), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_ENT, RGB_HUI, RGB_HUD, RGB_SAD,
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_UP, RGB_VAI, RGB_VAD, KC_NO,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, RGB_TOG),

    [QWERTY] = LAYOUT(
		KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    [GAMING] = LAYOUT(
		KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_NO, TO(DEFAULT), TO(DEFAULT), TO(DEFAULT),
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_CHAT, KC_CHAT, KC_CHAT, KC_CHAT, KC_CHAT, KC_NO, TO(DEFAULT), TO(DEFAULT), TO(DEFAULT),
		KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_C, KC_COMMAND, KC_COMMAND, KC_COMMAND, KC_COMMAND, KC_W, TO(DEFAULT), TO(DEFAULT), TO(DEFAULT),
		KC_LCTL, KC_LALT, KC_SPC, KC_SPC, KC_BSPC, KC_NO, KC_COMMAND, KC_A, KC_S, KC_D, TO(DEFAULT), TO(DEFAULT)),

    [GAMINGCHAT] = LAYOUT(
		KC_MCESC, KC_COMM, KC_DOT, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, KC_SLSH, KC_BSPC, KC_1, KC_2, KC_3,
		KC_A, KC_O, KC_E, KC_U, KC_I, KC_D, KC_H, KC_T, KC_N, KC_S, KC_MCENT, KC_4, KC_5, KC_6,
		KC_SCLN, KC_Q, KC_J, KC_K, KC_X, KC_B, KC_M, KC_W, KC_V, KC_Z, KC_UP, KC_7, KC_8, KC_9,
		KC_MCESC, KC_MCESC, KC_MCESC, KC_SPC, KC_LSFT, KC_MCENT, KC_MCENT, KC_LEFT, KC_DOWN, KC_RGHT, KC_0, KC_LSFT),


};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case KC_CHAT:
    if (record->event.pressed) {
      tap_code(KC_T);
  //    tap_code16(TO(5));
      layer_on(GAMINGCHAT);
      return false;
    }
//    break;
  case KC_MCESC:
    if (record->event.pressed) {
      tap_code(KC_ESC);
      //      tap_code16(TO(4));
      layer_off(GAMINGCHAT);
      layer_on(GAMING);
      return false;
    }
//    break;
  case KC_COMMAND:
    if (record->event.pressed) {
      tap_code(KC_SLSH);
      //    tap_code16(TO(5));
      layer_on(5);
      return false;
    }
//    break;
  case KC_MCENT:
    if (record->event.pressed) {
      tap_code(KC_ENT);
//      tap_code16(TO(4));
      layer_off(5);
      layer_on(4);
      return false;
    }
//    break;
//  return false; // Skip all further processing of this key
    default:
      return true; // Process all other keycodes normally
  }
}
