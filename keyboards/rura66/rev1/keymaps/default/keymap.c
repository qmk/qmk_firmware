/*
Copyright 2021 T.Shinohara

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

// Defines names for use in layer keycodes and the keymap
enum layer_number {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
  EISU = SAFE_RANGE,
  KANA,
  ADJUST,
  RGBRST
};

#define KC_LOSP LT(_LOWER, KC_SPC)
#define KC_LODEL LT(_LOWER, KC_DEL)
#define KC_RACOM LT(_RAISE, KC_COMM)
#define KC_RADOT LT(_RAISE, KC_DOT)
#define KC_RASLS LT(_RAISE, KC_SLSH)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
      KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_GRV,                    KC_EQL,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC, KC_ENT,  KC_ESC,  KC_RBRC, KC_B,    KC_N,    KC_M,    KC_BSLS, KC_QUOT, KC_PIPE,
      KC_LCTL, KC_LGUI, KC_LALT,                   KC_LODEL,KC_LOSP, KANA,    KC_RASLS,KC_RACOM,KC_RADOT,                  KC_RCTL, KC_RGUI, KC_RALT
      ),
  [_LOWER] = LAYOUT(
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  XXXXXXX,
      _______, KC_F11,  KC_F12,  KC_PGUP, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, _______,
      _______, XXXXXXX, KC_HOME, KC_PGDN, KC_END,  XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, _______,
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      _______, _______, _______,                   _______, _______, XXXXXXX, _______, _______, _______,                   _______, _______, _______
      ),
  [_RAISE] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, XXXXXXX,
      _______, _______, _______, _______, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, _______,
      _______, XXXXXXX, _______, _______, _______, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, _______, _______, _______, XXXXXXX, _______,
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      _______, _______, _______,                   _______, _______, XXXXXXX, _______, _______, _______,                   _______, _______, _______
      ),
  [_ADJUST] =  LAYOUT(
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, QK_BOOT, RGBRST,  EE_CLR,  XXXXXXX, XXXXXXX,                                     UG_TOGG, UG_HUEU, UG_SATU, UG_VALU, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, AG_NORM,                   AG_SWAP, UG_NEXT, UG_HUED, UG_SATD, UG_VALD, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX,                   _______, _______, XXXXXXX, _______, _______, _______,                   XXXXXXX, XXXXXXX, XXXXXXX
      )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case EISU:
      if (record->event.pressed) {
        if (is_mac_mode()) {
          register_code(KC_LNG2);
        }else{
          tap_code16(LALT(KC_GRAVE));
        }
      } else {
        unregister_code(KC_LNG2);
      }
      return false;
      break;
    case KANA:
      if (record->event.pressed) {
        if (is_mac_mode()) {
          register_code(KC_LNG1);
        }else{
          tap_code16(LALT(KC_GRAVE));
        }
      } else {
        unregister_code(KC_LNG1);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_LOWER);
        layer_on(_RAISE);
      } else {
        layer_off(_LOWER);
        layer_off(_RAISE);
      }
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
        }
      #endif
      break;
  }
  return true;
}
