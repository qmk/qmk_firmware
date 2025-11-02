/* Copyright 2025 GSKY <gskyGit@gsky.com.tw>
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

enum layers {
    _Win,
    _Mac,
    _Winfn,
    _Macfn,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: Base Layer (Default Layer)
   */
[_Win] = LAYOUT_75_ansi(
  KC_ESC,  KC_F1,   KC_F2,   KC_F3,      KC_F4,        KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,      KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_PAUS, KC_DEL,
  KC_GRV,  KC_1,    KC_2,    KC_3,       KC_4,         KC_5,    KC_6,    KC_7,    KC_8,    KC_9,       KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,
  KC_TAB,  KC_Q,    KC_W,    KC_E,       KC_R,         KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,       KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_END,
  KC_CAPS, KC_A,    KC_S,    KC_D,       KC_F,         KC_G,    KC_H,    KC_J,    KC_K,    KC_L,       KC_SCLN, KC_QUOT, KC_ENT,  KC_PGUP,
  KC_LSFT, KC_Z,    KC_X,    KC_C,       KC_V,         KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,     KC_SLSH, KC_RSFT, KC_UP,   KC_PGDN,
  KC_LCTL, KC_LGUI, KC_LALT,                           KC_SPC,                    KC_RALT, MO(_Winfn), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

[_Winfn] = LAYOUT_75_ansi(
  KC_TRNS, KC_BRID, KC_BRIU, LGUI(KC_D), LGUI(KC_TAB), KC_MAIL, KC_CALC, KC_MPRV, KC_MPLY, KC_MNXT,    KC_MUTE, KC_VOLD, KC_VOLU, KC_TRNS, KC_TRNS, KC_INS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RM_NEXT,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RM_HUEU,
  KC_TRNS, TO(_Win),TO(_Mac),KC_TRNS,    KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, RM_TOGG,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, RM_VALU, KC_TRNS,
  KC_TRNS, GU_TOGG, KC_TRNS,                           EE_CLR,                    KC_TRNS, KC_TRNS,    KC_TRNS, RM_SPDD, RM_VALD, RM_SPDU),

[_Mac] = LAYOUT_75_ansi(

  KC_ESC,  KC_BRID, KC_BRIU, KC_MCTL,    KC_LPAD,      KC_NO,   KC_NO,   KC_MPRV, KC_MPLY, KC_MNXT,    KC_MUTE, KC_VOLD, KC_VOLU, KC_PSCR, KC_PAUS, KC_DEL,
  KC_GRV,  KC_1,    KC_2,    KC_3,       KC_4,         KC_5,    KC_6,    KC_7,    KC_8,    KC_9,       KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,
  KC_TAB,  KC_Q,    KC_W,    KC_E,       KC_R,         KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,       KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_END,
  KC_CAPS, KC_A,    KC_S,    KC_D,       KC_F,         KC_G,    KC_H,    KC_J,    KC_K,    KC_L,       KC_SCLN, KC_QUOT, KC_ENT,  KC_PGUP,
  KC_LSFT, KC_Z,    KC_X,    KC_C,       KC_V,         KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,     KC_SLSH, KC_RSFT, KC_UP,   KC_PGDN,
  KC_LCTL, KC_LALT, KC_LGUI,                           KC_SPC,                    KC_RGUI, MO(_Macfn), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

[_Macfn] = LAYOUT_75_ansi(
  KC_TRNS, KC_F1,   KC_F2,   KC_F3,      KC_F4,        KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,      KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_TRNS, KC_INS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RM_NEXT,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RM_HUEU,
  KC_TRNS, TO(_Win),TO(_Mac),KC_TRNS,    KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, RM_TOGG,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, RM_VALU, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS,                           EE_CLR,                    KC_TRNS, KC_TRNS,    KC_TRNS ,RM_SPDD, RM_VALD, RM_SPDU)
};
