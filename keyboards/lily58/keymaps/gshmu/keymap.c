/* Copyright 2022 gshmu
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

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  ~   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ⌥(⇥) |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  =   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ⌥(⎋) |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * | ⇧(←) |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  | ⇧(→) |
 * `-----------------------------------------/      /     \      \-----------------------------------------'
 *                  | ⌃(⌦) | ⇧(↑) | L2(␣)|  / ⌘(↵) /       \ ⌘(⌫) \  |L1(␣))| ⇧(↓) | ⌥(⌦) |
 *                  |      |      |      |/       /         \      \ |      |      |      |
 *                  `-------------------''-------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT(
  KC_GRV,          KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
  LALT_T(KC_TAB),  KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,
  LALT_T(KC_ESC),  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  LSFT_T(KC_LEFT), KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_RGHT),
  LCTL_T(KC_DEL),  LSFT_T(KC_UP),  LT(_RAISE, KC_SPC),  LGUI_T(KC_ENTER),  RGUI_T(KC_BSPC),  LT(_LOWER, KC_SPC),  RSFT_T(KC_DOWN), RALT_T(KC_DEL)
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|   \   |    |   |   |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      | L3(␣)| /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `-------------------''-------'           '------''--------------------'
 */
[_LOWER] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, KC_BSLS, KC_PIPE, _______, _______, _______, _______, _______, _______,
                          _______, _______, LT(_ADJUST, KC_SPC), _______, _______,  _______, _______, _______
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F1  |  F2  |  F3  |  F4  |  F5  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  F6  |  F7  |  F8  |  F9  |  F10 |                    |  F6  |  F7  |  F8  |  F9  |  F10 |  \   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  F11 |  F12 |  F13 |  F14 |  F15 |-------.    ,-------|  F11 |  F12 |  F13 |  F14 |  F15 |      |
 * |------+------+------+------+------+------|   \   |    |   |   |------+------+------+------+------+------|
 * |      | AG(Z)| CA(A)|Cmd(C)| SG(V)| SG(B)|-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |L3(␣))|      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `-------------------''-------'           '------''--------------------'
 */

[_RAISE] = LAYOUT(
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,
  _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,                      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
  _______, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,                      KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  _______,
  _______, LAG(KC_Z), C(G(KC_A)), LGUI(KC_C), LSG(KC_V), LSG(KC_B),  KC_BSLS, KC_PIPE,  _______, _______, _______, _______, _______, _______,
                             _______, _______, _______,  _______, _______,  LT(_ADJUST, KC_SPC), _______, _______
),

/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * | Home |      |      |      |      |      |-------|    |-------|      |      |      |      |      |  End |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      | PGUP |      | /       /       \      \  |      | PGDN |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______,
  DT_PRNT, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______,
  KC_HOME, _______, _______, _______, _______, _______,  DT_UP,   DT_DOWN,  _______, _______, _______, _______, _______, KC_END,
                             _______, KC_PGUP, _______,  _______, _______,  _______, KC_PGDN, _______
  )
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_ENABLE
    set_keylog(keycode, record);
#endif
  }
  return true;
}
