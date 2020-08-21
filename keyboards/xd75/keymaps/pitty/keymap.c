/* Copyright 2017 Wunder
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
#include "keymap_hungarian.h" 

enum XD75_layers {
  _QWERTY,
  _GAME,
  _LOWER,
  _RAISE
};


// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  GAME,
  LOWER,
  RAISE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


/* Qwerty
 * ,--------------------------------------------------------------------------------------------------------.
 * |  0   |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   Ö  |  Ü   |  Ó   |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | TAB  |   Q  |   W  |   E  |   R  |   T  |   Z  |   U  |   I  |   O  |   P  |  Ő   |  Ú   |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   É  |  Á   |  Ű   |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------+------+------+------|
 * | Shift|   Y  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   -  | Shift|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |  GUI |  ALt |Lower |    Space    | Enter| Bksp |AltGr | Raise|      |      |      |      |      |
 * `--------------------------------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_5x15( \
  HU_0,                  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    HU_OE,    HU_UE,   HU_OO,   KC_INS,  KC_PGUP, \
  KC_TAB,                KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    HU_Z,    KC_U,    KC_I,    KC_O,    KC_P,     HU_OEE,  HU_UU,   KC_DEL,  KC_PGDN,  \
  KC_ESC,                KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    HU_EE,    HU_AA,   HU_UEE,  _______, KC_HOME, \
  MT(MOD_LSFT, KC_NUBS), HU_Y,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    HU_COMM, HU_DOT,  HU_MINS,  KC_RSFT, HU_EQL,  KC_UP,   KC_END,  \
  KC_LCTL,               KC_LGUI, KC_LALT, TT(_LOWER),   KC_SPC,  _______, KC_ENT,  KC_BSPC, KC_RALT, TT(_RAISE),   _______,  _______, KC_LEFT, KC_DOWN, KC_RIGHT  \
),


/* Game
 * ,--------------------------------------------------------------------------------------------------------.
 * |  0   |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   Ö  |  Ü   |  Ó   |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | TAB  |   Q  |   W  |   E  |   R  |   T  |   Z  |   U  |   I  |   O  |   P  |  Ő   |  Ú   |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   É  |  Á   |  Ű   |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------+------+------+------|
 * | Shift|   Y  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   -  | Shift|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |  GUI |  ALt |Raise |    Space    | Enter| Bksp |AltGr | Lower|      |      |      |      |      |
 * `--------------------------------------------------------------------------------------------------------'
 */
[_GAME] = LAYOUT_ortho_5x15( \
  HU_0,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    HU_OE,    HU_UE,    HU_OO,   KC_INS,  KC_PGUP, \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    HU_Z,    KC_U,    KC_I,    KC_O,    KC_P,     HU_OEE,   HU_UU,   KC_DEL,  KC_PGDN,  \
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    HU_EE,    HU_AA,    HU_UEE,  _______, KC_HOME, \
  KC_LSFT, HU_Y,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    HU_COMM, HU_DOT,  HU_MINS,  KC_RSFT,  HU_EQL,  KC_UP,   KC_END,  \
  KC_LCTL, KC_LGUI, KC_LALT, TT(_RAISE),   KC_SPC,  _______, KC_ENT,  KC_BSPC, KC_RALT, TT(_LOWER),   _______,  _______,  KC_LEFT, KC_DOWN, KC_RIGHT  \
),


/* Lower
 * ,--------------------------------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |   7  |   8  |   9  |   +  |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |  Up  |      |      |      |      |   4  |   5  |   6  |   -  |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------+------+------+------|
 * |      | Left | Down | Right|      |      |      |   1  |   2  |   3  |   *  |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------+------+------+------|
 * |      |      |      |Lnxcpy|Lnxpst|      |      |   0  |      |      |   /  |  =   |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Home |PageDn|PageUp|  End |      |      |      |
 * `--------------------------------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_5x15( \
  _______, _______, _______, _______, _______, _______, _______, HU_7,    HU_8,    HU_9,    HU_PLUS,   _______,     _______, _______, _______, \
  _______, _______, KC_UP,   _______, _______, _______, _______, HU_4,    HU_5,    HU_6,    HU_MINS,   _______,     _______, _______, _______,  \
  _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, HU_1,    HU_2,    HU_3,    HU_ASTR,   _______,     _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, HU_0,    _______, _______, HU_SLSH,   HU_EQL,      _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, TO(_GAME), TO(_QWERTY), _______, _______, _______  \
),

/* Raise
 * ,--------------------------------------------------------------------------------------------------------.
 * |  F12 |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |  Up  |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------+------+------+------|
 * |      | Left | Down | Right|      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Home |PageDn|PageUp|  End |      |      |      |
 * `--------------------------------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_5x15( \
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,    KC_F11,      KC_F12,  _______, _______, \
  _______, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, _______,   _______,     _______, _______, _______,  \
  _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______,   _______,     _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______,     _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, TO(_GAME), TO(_QWERTY), _______, _______, _______  \
),



};



layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _RAISE:
        rgblight_setrgb (0xC3,  0xFF, 0xFF);
		rgblight_mode(5);
        break;
    case _LOWER:
        rgblight_setrgb (0xFF, 0xFF, 0xFF);
		rgblight_mode(5);
        break;
    case _GAME:
        rgblight_mode(8);
        break;
    default: //  for any other layers, or the default layer
        rgblight_mode(14);
        break;
    }
  return state;
}
