/* Copyright 2020 Eye Oh! Designs
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
  _DVORAK,
  _GAME,
  _LOWER,
  _RAISE,
  _ADJUST,
  _FN
};

enum custom_keycodes {
  DVORAK = SAFE_RANGE,
  GAME,
  ADJUST
};

#define LEADER_TIMEOUT 400

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define FN    MO(_FN)

#define LSPA  LT(_RAISE, KC_SPC)
#define RSPA  LT(_FN, KC_SPC)
#define RLEFT LT(_RAISE, KC_LEFT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_DVORAK] = LAYOUT_1u(
    KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC,
    KC_GESC, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_ENT ,
    KC_LSPO, KC_SLSH, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSPC,
    KC_LCTL,                   KC_LGUI, LOWER,   LSPA,    RSPA,    RAISE,   KC_LCTL,                   KC_RALT
  ),

  [_LOWER] = LAYOUT_1u(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_PIPE, KC_COLON, _______,
    _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LBRC, KC_RBRC,  _______,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TILD, _______, KC_LCBR, KC_RCBR,  _______,
    _______,                   _______, _______, _______, _______, _______, _______,                    _______
  ),

  [_RAISE] = LAYOUT_1u(
    _______, _______, _______, _______, _______, _______, _______, KC_MINS,  KC_EQL , KC_BSLS, KC_SCLN, _______,
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,     KC_8,    KC_9,    KC_0,    _______,
    _______, _______, _______, _______, _______, KC_PGDN, KC_PGUP, KC_GRAVE, _______, KC_LBRC, KC_RBRC, _______,
    _______,                   _______, _______, _______, _______, _______,  _______,                   _______
  ),

  [_FN] = LAYOUT_1u(
    _______, _______, _______, _______, _______, _______, _______, KC_TILD, KC_SLSH, KC_BSLS,  _______, KC_DEL,
    _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_SCLN, _______,
    _______, _______, _______, _______, _______, _______, KC_PGDN, KC_PGUP, _______, KC_LBRC,  KC_LBRC, _______,
    _______,                   _______, _______, _______, _______, _______, _______,                    KC_RCTL
  ),

  [_GAME] = LAYOUT_1u(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,   KC_I,     KC_O,     KC_P,    KC_ESC,
    KC_1,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,   KC_K,     KC_L,     KC_QUOT, KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,   KC_COMM,  KC_DOT,   KC_SLSH, KC_RSPC,
    KC_LCTL,                   KC_LALT, RAISE,   KC_SPC,  RSPA,    LOWER,  KC_LGUI,                     _DVORAK
  ),

  [_ADJUST] = LAYOUT_1u(
    _______, _______,  DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, _______,
    _______, _______,  _______, _DVORAK, _______, _GAME,   AG_NORM, AG_SWAP, _______,  CK_TOGG, _______, _______,
    _______, _______,  _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______,
    _______,                    _______, _______, _______, _______, _______, _______,                    RESET
  )
};

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
      break;

    case GAME:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_GAME);
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

    case FN:
      if (record->event.pressed) {
        layer_on(_FN);
        //update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_FN);
        //update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;

    case ADJUST:
      if (record->event.pressed) {
          layer_on(_ADJUST);
      } else {
          layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
