 /* Copyright HarshitGoel96 2020
  * With permission from mattdibi, the original maintainer of the Redox hardware.
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


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum custom_keycodes {
  _QWERTY,
  _MOVEMENT,
  _SYMBOLS,
  _MISC,
  _GAMING,
  _LOL,
  _WOW,
  _WOW2,
  _MINECRAFT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_split_3x5_3_encoder(
      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
      KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,    LT(_MOVEMENT,KC_SCLN),
      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    TO(_GAMING),    KC_MPLY, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                      KC_LGUI, KC_LSFT, KC_SPC, LCTL_T(KC_TAB),          MO(_SYMBOLS), LCTL_T(KC_BSPC), LALT_T(KC_ENT), MO(_MISC)
  ),
  [_MOVEMENT] = LAYOUT_split_3x5_3_encoder(
      KC_ACL1,   KC_MS_BTN1,  KC_MS_UP,      KC_MS_BTN2,    KC_MS_WH_UP,                               KC_INSERT,  KC_HOME,    KC_UP,    KC_END,      KC_NO,
      KC_ACL2,   KC_MS_LEFT,  KC_MS_DOWN,    KC_MS_RIGHT,   KC_MS_BTN3,                                KC_TAB,     KC_LEFT,    KC_DOWN,  KC_RIGHT,    KC_TRNS,
      KC_NO,   KC_MS_BTN4,  KC_ESCAPE,     KC_MS_BTN5,    KC_MS_WH_DOWN,    KC_MPRV,            KC_MNXT, KC_DEL,     KC_CUT,     KC_COPY,  KC_PASTE,    KC_NO,
                                                          KC_LGUI, KC_LSFT, KC_SPC, LCTL_T(KC_TAB),           KC_NO, LCTL_T(KC_BSPC), LALT_T(KC_ENT), KC_NO
  ),
  [_SYMBOLS] = LAYOUT_split_3x5_3_encoder(
      KC_1,    KC_2,    KC_3,    KC_PPLS,    KC_PAST,                          KC_GRV,  KC_LPRN,    KC_RPRN,    KC_BSLS,    KC_NO,
      KC_4,    KC_5,    KC_6,    KC_PMNS,    KC_EQL,                         KC_QUOT,    KC_LBRC,    KC_RBRC,    KC_AMPR,    KC_CIRC,
      KC_7,    KC_8,    KC_9,    KC_0,    KC_UNDS,    KC_NO,    KC_NO,    KC_GRAVE,    KC_NO,    KC_NO, KC_NO,  KC_NO,
                        KC_LGUI, KC_LSFT, KC_SPC, LCTL_T(KC_TAB),                KC_TRNS, LCTL_T(KC_BSPC), LALT_T(KC_ENT), KC_NO
  ),
  [_MISC] = LAYOUT_split_3x5_3_encoder(
      KC_F1,    KC_F2,    KC_F3,    KC_F10,    KC_PSCR,                       KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,
      KC_F4,    KC_F5,    KC_F6,    KC_F11,    KC_NO,                         KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
      KC_F7,    KC_F8,    KC_F9,    KC_F12,    KC_NO,    QK_BOOT,    QK_BOOT, KC_NO,    KC_NO,    KC_NO, KC_NO,  KC_NO,
                      KC_LGUI,    KC_NO,       KC_NO,    KC_NO,         KC_NO, KC_NO, KC_NO, KC_TRNS
  ),
  [_GAMING] = LAYOUT_split_3x5_3_encoder(
      KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,                         KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,
      KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,                         KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
      KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_G,    TO(_QWERTY), KC_NO,    KC_NO,    KC_NO, KC_NO,  KC_NO,
                       KC_G, KC_LGUI, KC_SPC, KC_LALT,           TO(_WOW), TO(_MINECRAFT), KC_NO, TO(_LOL)
  ),
  [_LOL] = LAYOUT_split_3x5_3_encoder(
      KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                          KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
      KC_LSFT, KC_Q,    KC_W,    KC_E,    KC_R,                          KC_NO,    KC_MPRV,    KC_MPLY,    KC_MNXT,    KC_NO,
      KC_TAB,    KC_H,    KC_T,    KC_D,    KC_F,    KC_B,    TO(_QWERTY), KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
                       KC_V, LALT_T(KC_ESCAPE), LCTL_T(KC_SPC), KC_C,           KC_NO, KC_NO, KC_NO, KC_NO
  ),
  [_WOW] = LAYOUT_split_3x5_3_encoder(
      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                          KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
      KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                          KC_TAB,    KC_MPRV,    KC_MPLY,    KC_MNXT,    KC_NO,
      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_H,    TO(_QWERTY), KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
                       KC_N, MO(_WOW2), KC_SPC, KC_ESCAPE,           KC_NO, KC_NO, KC_NO, KC_NO
  ),
  [_WOW2] = LAYOUT_split_3x5_3_encoder(
      KC_1,    KC_2,    KC_E,    KC_3,    KC_4,                                   KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
      KC_5,    KC_S,    KC_D,    KC_F,    KC_6,                                    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
      KC_7,    KC_8,    KC_9,    KC_0,    KC_UNDS,    KC_MPLY,       KC_TAB,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
                        KC_NO, KC_TRNS, KC_NO, KC_NO,                           KC_NO, KC_NO, KC_NO, KC_NO
  ),
  [_MINECRAFT] = LAYOUT_split_3x5_3_encoder(
        KC_1,    KC_Q,    KC_W,    KC_E,    KC_F3,                                   KC_H,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
        KC_2,    KC_A,    KC_S,    KC_D,    KC_ESCAPE,                                    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
        KC_3,    KC_4,    KC_5,    KC_6,       KC_7,    TO(_QWERTY),       KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
                          KC_NO, KC_LSFT, KC_SPC, KC_LCTL,                           KC_NO, KC_NO, KC_NO, KC_NO
    )
};
