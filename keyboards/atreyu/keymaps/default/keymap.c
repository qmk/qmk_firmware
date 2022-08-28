/* Copyright 2022 Jesus Climent  (@climent)
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


enum custom_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LWR,
  RSE,
  ADJ
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT(
     KC_ESC  , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                   KC_6   , KC_7   , KC_8   , KC_9   , KC_0    ,KC_GRV  ,
     KC_TAB  , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                   KC_Y   , KC_U   , KC_I   , KC_O   , KC_P    ,KC_BSPC ,
     KC_LCTRL, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                   KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN ,KC_QUOT ,
     KC_LSFT , KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                   KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH ,KC_RSFT ,
     KC_LCTL,           LWR    , KC_LALT, KC_LGUI, KC_ENT , KC_LBRC, KC_RBRC, KC_SPC , RSE    , KC_NO  ,  KC_NO ,          KC_RCTL 
                
  ),

[_RAISE] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                    KC_HOME, KC_END , _______, KC_LCBR, KC_RCBR, KC_TILD,
  _______, _______, _______, _______, KC_HOME, KC_END ,                    KC_PGUP, XXXXXXX, KC_UP  , KC_LBRC, KC_RBRC, KC_DEL ,
  _______, _______, _______, _______, _______, _______,                    KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_PIPE, KC_ENT ,
  _______, _______, _______, _______, _______, _______,                    KC_UNDS, KC_MINS, KC_EQL , KC_PLUS, KC_BSLS, _______,
  _______,          _______, _______, _______, KC_SPC , KC_HOME, KC_END  , _______, _______, KC_RGUI, KC_RALT,          _______
),

[_LOWER] = LAYOUT(
  KC_GRV , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                   KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , _______,
  _______, KC_VOLU, _______, _______, TG(_RAISE), AG_TOGG,                _______, _______, _______, _______, _______, KC_DEL ,
  _______, KC_VOLD, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, 
  _______, KC_CAPS, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______,          _______, _______, _______, KC_SPC , KC_VOLD, KC_VOLU, _______, _______, _______, _______, _______
),

[_ADJUST] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  _______,          _______, _______, _______, _______ , _______, _______ , _______, _______, _______, _______,         _______
)

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LWR:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;

    case RSE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;

    case KC_ESC:
     if ((get_mods() & MOD_BIT(KC_LGUI)) == MOD_BIT(KC_LGUI)) {
        if (record->event.pressed) {
          register_code(KC_GRV);
        } else {
          unregister_code(KC_GRV);
        }
        return false;
      }
      return true;
      break;
  }
  return true;
}

