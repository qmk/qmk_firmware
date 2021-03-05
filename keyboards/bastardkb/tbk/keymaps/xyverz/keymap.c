/* 
 * Copyright 2021 Ian Sterling <xyverz on Github.com>
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

enum layer_names { _WINDOWS, _MAC, _LOWER, _RAISE, _ADJUST };

enum custom_keycodes { WINDOWS = SAFE_RANGE, MAC, ADJUST };

// Aliases to keep the keymap tidy
#define GUIBSPC GUI_T(KC_BSPC)  // GUI when held, BSPC when tapped.
#define RGB_SWR RGB_M_SW        // Swirl Animation alias
#define RGB_SNK RGB_M_SN        // Snake Animation alias
#define MACLOCK LGUI(LCTL(KC_Q)) // Lock my MacBook!
#define WINLOCK LGUI(KC_L)      // Lock my PC!
#define DELGUI GUI_T(KC_DEL)
#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)


#define MACLOCK LGUI(LCTL(KC_Q)) // Lock my MacBook!

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_WINDOWS] = LAYOUT_split_4x6_5(
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
  KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,        KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH,
  KC_GRV,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,        KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS,
  KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,        KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,
                             LOWER,   KC_BSPC, KC_DEL,      KC_ENT,  KC_SPC,  RAISE,
                                      KC_LCTL, KC_LALT,     KC_RGUI, KC_RCTL
  ),

[_MAC] = LAYOUT_split_4x6_5(
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
  KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,        KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH,
  KC_GRV,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,        KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS,
  KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,        KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,
                             LOWER,   KC_BSPC, DELGUI,      KC_ENT,  KC_SPC,  RAISE,
                                      KC_LCTL, KC_LALT,     KC_RGUI, KC_RCTL
  ),

[_LOWER] = LAYOUT_split_4x6_5(
  KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12, 
  RESET,   _______, _______, KC_UP,   _______, _______,     _______, KC_PSCR, KC_SLCK, KC_PAUS, _______, _______,
  KC_CAPS, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_HOME,     KC_PGUP, _______, KC_PLUS, KC_LCBR, KC_RCBR, _______,
  _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_END,      KC_PGDN, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,
                             _______, KC_DEL,  _______,     _______, _______, _______,
                                      MACLOCK, _______,     _______, WINLOCK
  ),

[_RAISE] = LAYOUT_split_4x6_5(
  KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12, 
  _______, _______, _______, KC_UP,   _______, _______,     _______, KC_PSCR, KC_SLCK, KC_PAUS, _______, RESET,
  KC_CAPS, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_HOME,     KC_PGUP, _______, KC_EQL,  KC_LBRC, KC_RBRC, _______,
  _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_END,      KC_PGDN, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,
                             _______, KC_DEL,  _______,     _______, _______, _______,
                                      MACLOCK, _______,     _______, WINLOCK
  ),

[_ADJUST] = LAYOUT_split_4x6_5(
  _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______,
  _______, RESET,   _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,     _______, WINDOWS, MAC,     _______, _______, _______,
  _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______,
                             _______, _______, _______,     _______, _______, _______,
                                      _______, _______,     _______, _______
  ),

};

layer_state_t layer_state_set_user(layer_state_t state) { return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST); };

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case WINDOWS:
                set_single_persistent_default_layer(_WINDOWS);
                return false;
            case MAC:
                set_single_persistent_default_layer(_MAC);
                return false;
        }
    }
    return true;
}
