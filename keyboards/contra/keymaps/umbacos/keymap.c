/* Copyright 2015-2017 Jack Humbert
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
#include "keymap_italian.h"

//Friendly Layer Names
enum prototype30_layers {
  _QWERTY,
  _SHIFT,
  _NUMBER,
  _ACCENT,
  _SERVICE,
  _SYMBOL
};

keymap_config_t keymap_config;
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

      [_QWERTY] = LAYOUT_ortho_4x12(
          KC_ESC,       KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_BSPC,  \
          KC_TAB,       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,   IT_APOS,   KC_SFTENT,  \
          LT(_SHIFT, KC_DEL),  KC_Z,  KC_X,  KC_C,  KC_V,   KC_B,    KC_N,    KC_M,    IT_SLSH, IT_SCLN,  KC_UP,   LT(_SHIFT, IT_COLN), \
          KC_LCTL, KC_LALT, MO(_SERVICE), KC_LGUI, LT(_NUMBER, KC_DEL), XXXXXXX, XXXXXXX, LT(_ACCENT, KC_SPC),  LT(_NUMBER, KC_COMM),   KC_LEFT, KC_DOWN, KC_RGHT  \
      ),
      [_SHIFT] = LAYOUT_ortho_4x12(
          S(KC_ESC),  S(KC_Q),    S(KC_W), S(KC_E), S(KC_R), S(KC_T), S(KC_Y), S(KC_U), S(KC_I), S(KC_O), S(KC_P), S(KC_BSPC),  \
          S(KC_TAB),  S(KC_A),    S(KC_S), S(KC_D), S(KC_F), S(KC_G), S(KC_H), S(KC_J), S(KC_K), S(KC_L), IT_DQOT, S(KC_ENT), \
          IT_QST,    S(KC_Z),    S(KC_X), S(KC_C), S(KC_V), S(KC_B), S(KC_N), S(KC_M), IT_QST,  IT_COLN, S(KC_UP), _______,  \
          S(KC_LCTL), S(KC_LALT), MO(_SERVICE), S(KC_LGUI), LT(_SYMBOL, KC_DEL), XXXXXXX, XXXXXXX, LT(_ACCENT, KC_SPC),  LT(_SYMBOL, IT_DOT), S(KC_LEFT), S(KC_DOWN), S(KC_RGHT)  \
      ),
      [_NUMBER] = LAYOUT_ortho_4x12(
        IT_LESS,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    IT_EQL, \
        KC_TAB, KC_PPLS, KC_PMNS, KC_PSLS, KC_PAST, XXXXXXX, XXXXXXX, KC_4,    KC_5,    KC_6, KC_0, KC_SFTENT,
        LT(_SYMBOL, KC_DEL), IT_EQL,  IT_LBRC, IT_RBRC,   KC_DOT,   XXXXXXX,   XXXXXXX,   KC_1,    KC_2,    KC_3, KC_VOLU, LT(_SYMBOL, KC_DEL),
        KC_F1,   KC_F2,   KC_F3,   KC_F4, _______, XXXXXXX, XXXXXXX, _______, _______, _______, KC_VOLD, KC_MUTE \
      ),
      [_SYMBOL] = LAYOUT_ortho_4x12(
          IT_MORE, IT_EXLM, IT_AT,   IT_SHRP, IT_DLR,  IT_PERC, IT_CRC,  IT_AMPR, IT_ASTR, IT_LPRN, IT_RPRN, IT_PLUS, \
          S(KC_TAB), IT_EQL, IT_UNDS, KC_PSLS, KC_PAST,XXXXXXX, IT_MORE, IT_LESS,  IT_LCBR, IT_LCBR, IT_RCBR, KC_SFTENT,
          KC_LSFT, _______, _______, _______, _______, _______, IT_BKSL,  IT_PIPE, IT_UNDS, IT_PLUS, _______, IT_QST, \
          KC_F5,   KC_F6,   KC_F7,   KC_F8, _______, XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______ \
      ),
      [_ACCENT] = LAYOUT_ortho_4x12(
          _______, IT_EURO, IT_AT, IT_EACC, _______, _______, _______, IT_UACC, IT_IACC, IT_OACC, _______, _______,  \
          _______, IT_AACC, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   \
          KC_LSFT, _______, _______, _______, _______, _______, _______, _______, IT_SCLN, IT_COLN, _______, _______,   \
          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
      ),
      [_SERVICE] = LAYOUT_ortho_4x12(
        RESET,   RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, _______, _______, _______, _______, _______,  _______, _______,  \
        _______, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, _______, _______, _______, _______,  _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, KC_VOLU, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______,  KC_MUTE, KC_VOLD, KC_MUTE \
      )
};

/*
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
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
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        PORTE &= ~(1<<6);
      } else {
        unregister_code(KC_RSFT);
        PORTE |= (1<<6);
      }
      return false;
      break;
  }
  return true;
}
*/
