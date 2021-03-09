
/* Copyright 2021 Charlotte Brolan
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
    _BASE,
    _LAYER1
};

// Example of custom keycodes used by macros in process_record_user
/*
 enum custom_keycodes {
};
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Reproduce the layout as close as we can get to what it is on the board - this might not be a nice layout, but it is what's on the keycaps
 * ,-----------------------------------------------------------. ,-----------. ,---------------.
 * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =| BSpc  | |VlU|Hom|BrU| | ` |  =|  /|  *|
 * |-----------------------------------------------------------| |-----------| |---------------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  | |VlD|   |BrD| |  7|  8|  9|  -|
 * |-----------------------------------------------------------| `---'   `---' |---------------|
 * |LCtl  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  Return|               |  4|  5|  6|  +|
 * |-----------------------------------------------------------|     ,---.     |---------------|
 * |Shft    | Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|     Shift |     |Up |     |  1|  2|  3|   |
 * |-----------------------------------------------------------| ,-----------. |-----------|   |
 * |LAlt |LGui |              Space                |Rgui | Fn  | |Lef|Dow|Rig| |  0    |  .|Ent|
 * `-----------------------------------------------------------' `-----------' `---------------'
 */
  [_BASE] = LAYOUT_next(
		 KC_ESC,  KC_1,    KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,     KC_VOLU, KC_HOME, KC_BRIU,    KC_GRV, KC_EQL, KC_PSLS, KC_PAST,
     KC_TAB,  KC_Q,    KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,     KC_VOLD,          KC_BRID,    KC_P7,  KC_P8,  KC_P9,   KC_PMNS,
     KC_LCTL, KC_A,    KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,                                             KC_P4,  KC_P5,  KC_P6,   KC_PPLS,
     KC_LSFT, KC_Z,    KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                                 KC_UP,              KC_P1,  KC_P2,  KC_P3,
     KC_LALT, KC_LGUI,                     KC_SPC,                           KC_RGUI, MO(_LAYER1),                   KC_LEFT, KC_DOWN, KC_RIGHT,   KC_P0,          KC_PDOT, KC_PENT
  ),
/* 
 *
 * Replicate the front legend functions that are on the caps, and add some quality of life stuff - F keys on top row, some nav cluster options, backslash if you are unlucky enough to have ABP model
 * which is short one key
 * ,-----------------------------------------------------------. ,-----------. ,---------------.
 * |` | F1| F2| F3| F4| F5| F6| F7| F8| F9| F10| F11| F12| Del | |   |End|PgU| |Rst|   |  \|   |
 * |-----------------------------------------------------------| |-----------| |---------------|
 * |     |   |   |   |   |   |   |   |   |   |   |   |   |     | |Mut|   |PgD| |   |   |   |   |
 * |-----------------------------------------------------------| `---'   `---' |---------------|
 * |      |   |   |   |   |   |   |   |   |   |   |   |        |               |   |   |   |   |
 * |-----------------------------------------------------------|     ,---.     |---------------|
 * |Caps   |Und|Cut|Cpy|Pst|   |   |   |   |   |   |     CapsL |     |PgU|     |   |   |   |   |
 * |-----------------------------------------------------------| ,-----------. |-----------|   |
 * |     |     |                                   |     |     | |Hom|PgD|End| |       |   |   |
 * `-----------------------------------------------------------' `-----------' `---------------'
 */
  [_LAYER1] = LAYOUT_next(
      KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,        _______, KC_END,  KC_PGUP,    RESET,   KC_NLCK, KC_BSLS, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,       KC_MUTE,          KC_PGDN,    _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PENT,                                              _______, _______, _______, _______,
      KC_CAPS, LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), _______, _______, _______, _______, _______, _______, KC_CAPS,                                  KC_PGUP,             _______, _______, _______,
		  _______, _______,                                _______,                                          _______, _______,                KC_HOME, KC_PGDN, KC_END,     _______,          _______, _______
  )
};

/*
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}
*/

