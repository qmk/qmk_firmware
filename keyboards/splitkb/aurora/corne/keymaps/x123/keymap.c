/*
Copyright 2022 x123 <@x123>
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

enum layer_names {
    _QWERTY,
    _QWERTY_NOHOMEROW,
    _COLEMAK,
    _COLEMAK_NOHOMEROW,
    _LOWER,
    _RAISE,
    _ADJUST,
    _ONESHOT,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  QWERTY_NOHOMEROW,
  COLEMAK,
  COLEMAK_NOHOMEROW,
  LOWER,
  RAISE,
  ADJUST,
  ONESHOT,
  DT_UP_50,
  DT_DOWN_50,
  DT_UP_X2,
  DT_DOWN_X2,
  DT_200,
  DT_MAX,
};

#define LSFT_KA LSFT_T(KC_A)
#define LCTL_KS LCTL_T(KC_S)
#define LGUI_KD LGUI_T(KC_D)
#define LALT_KF LALT_T(KC_F)
#define LALT_KJ LALT_T(KC_J)
#define RGUI_KK RGUI_T(KC_K)
#define RCTL_KL RCTL_T(KC_L)
#define RS_SCLN RSFT_T(KC_SCLN)

#define LCTL_KR LCTL_T(KC_R)
#define LGUI_KS LGUI_T(KC_S)
#define LALT_KT LALT_T(KC_T)
#define LALT_KN LALT_T(KC_N)
#define RGUI_KE RGUI_T(KC_E)
#define RCTL_KI RCTL_T(KC_I)
#define RSFT_KO RSFT_T(KC_O)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BSPC, LSFT_KA, LCTL_KS, LGUI_KD, LALT_KF,    KC_G,                         KC_H, LALT_KJ, RGUI_KK, RCTL_KL, RS_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT,   LOWER,  KC_SPC,     KC_ENT,   RAISE, OSL(_ONESHOT)
                                      //`--------------------------'  `--------------------------'

  ),

  [_QWERTY_NOHOMEROW] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BSPC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT,   LOWER,  KC_SPC,     KC_ENT,   RAISE, OSL(_ONESHOT)
                                      //`--------------------------'  `--------------------------'

  ),

  [_COLEMAK] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BSPC, LSFT_KA, LCTL_KR, LGUI_KS, LALT_KT,    KC_G,                         KC_M, LALT_KN, RGUI_KE, RCTL_KI, RSFT_KO, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                         KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT,   LOWER,  KC_SPC,     KC_ENT,   RAISE, OSL(_ONESHOT)
                                      //`--------------------------'  `--------------------------'
  ),

  [_COLEMAK_NOHOMEROW] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BSPC,    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                         KC_M,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                         KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT,   LOWER,  KC_SPC,     KC_ENT,   RAISE, OSL(_ONESHOT)
                                      //`--------------------------'  `--------------------------'
  ),

  [_LOWER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_GRV, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, KC_LBRC, KC_LCBR,                      KC_RCBR, KC_RBRC,  KC_EQL, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_RAISE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_ESC, KC_WH_U, KC_WBAK, KC_WFWD, KC_MS_U,                       KC_PGUP, KC_HOME,   KC_UP,  KC_END,  KC_DEL, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_RALT, KC_WH_D, KC_LSFT, KC_LCTL, KC_MS_D,                      KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, C(KC_Z), C(KC_X), C(KC_C), KC_BTN1, C(KC_V),                      KC_BTN2, KC_BTN3, KC_MS_L, KC_MS_R, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_ONESHOT] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, COLEMAK,  QWERTY, _______, _______, _______,                      QK_BOOT, _______, _______, QWERTY_NOHOMEROW, COLEMAK_NOHOMEROW, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case QWERTY_NOHOMEROW:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY_NOHOMEROW);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    case COLEMAK_NOHOMEROW:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK_NOHOMEROW);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ONESHOT:
      if (record->event.pressed) {
        set_oneshot_layer(_ONESHOT, ONESHOT_START);
      } else {
        clear_oneshot_layer_state(ONESHOT_PRESSED);
      }
      return false;
      break;
    case DT_UP_50:
      if (record->event.pressed) {
        g_tapping_term += 50;
      }
      return false;
      break;
    case DT_DOWN_50:
      if (record->event.pressed) {
        g_tapping_term -= 50;
      }
      return false;
      break;
    case DT_UP_X2:
      if (record->event.pressed) {
        g_tapping_term *= 2;
      }
      return false;
      break;
    case DT_DOWN_X2:
      if (record->event.pressed) {
        g_tapping_term /= 2;
      }
      return false;
      break;
    case DT_200:
      if (record->event.pressed) {
        g_tapping_term = 200;
      }
      return false;
      break;
    case DT_MAX:
      if (record->event.pressed) {
        g_tapping_term = 34464;
      }
      return false;
      break;
  }
  return true;
}