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
#include "muse.h"


enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};


enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  PAREN,
  BRACK,
  ANGLE,
  SQUAR,
  DOT,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |0000000000000000000
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Ctrl | Alt  |GUI   |Lower |    Space    |Raise | Left |  Up  | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
    _______, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT
),


/* Lower
 * ,-----------------------------------------------------------------------------------.
 * | PgUp | Home |  Up  | End  |      |      |  ^   | -/_  | [/]  |  $   |  !   | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |PgDown| Left | Down |Right |      |      |  *   | =/+  | (/)  | {/}  |  |   |   `  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |  @   |  %   |  #   | </>  | ./,  |  &   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |ALeft | Spot |Finder|ARight|
 * `-------------------------------------------------------- ---------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_PGUP,   KC_HOME, KC_UP,   KC_END , _______, _______, S(KC_6), KC_MINS, SQUAR,     S(KC_4),     S(KC_1),        KC_DEL,
    KC_PGDOWN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, S(KC_8), KC_EQL,  PAREN,     BRACK,       S(KC_BSLS),     KC_GRAVE,
    _______,   _______, _______, _______, _______, S(KC_1), S(KC_5), S(KC_3), ANGLE,     DOT,         S(KC_7),        _______,
    _______,   _______, _______, _______, _______, _______, _______, _______, G(KC_TAB), G(KC_SPACE), G(A(KC_SPACE)), SGUI(KC_TAB)
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |   1  |   2  |   3  | -/_  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |SFind | Find | Cut  | Copy |Paste |      |      |   4  |   5  |   6  |  0   |  *   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   7  |   8  |   9  |  +   | ./,  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |DLeft | DUp  |DDown |DRight|
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______,  KC_1,    KC_2,          KC_3,        KC_PMNS,        KC_DEL,
    C(KC_P), C(KC_F), C(KC_X), C(KC_C), C(KC_P), _______, _______,  KC_4,    KC_5,          KC_6,        KC_0,           KC_PAST,
    _______, _______, _______, _______, _______, _______, _______,  KC_7,    KC_8,          KC_9,        KC_PPLS,        DOT,
    _______, _______, _______, _______, _______, _______, _______,  _______, LCTL(KC_LEFT), LCTL(KC_UP), LCTL(KC_DOWN),  LCTL(KC_RIGHT)
),
/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | BOOT |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case PAREN:
      if (record->event.pressed) {
        if (keyboard_report->mods & MOD_BIT(KC_LSFT) || keyboard_report->mods & MOD_BIT(KC_RSFT)){
          clear_mods();
          register_code(KC_LSFT);
          register_code(KC_0);
        } else {
          register_code(KC_LSFT);
          register_code(KC_9);
        }
        clear_keyboard();
      }
      return false;
      break;
    case BRACK:
      if (record->event.pressed) {
        if (keyboard_report->mods & MOD_BIT(KC_LSFT) || keyboard_report->mods & MOD_BIT(KC_RSFT)){
          clear_mods();
          register_code(KC_LSFT);
          register_code(KC_RBRACKET);
        } else {
          register_code(KC_LSFT);
          register_code(KC_LBRACKET);
        }
        clear_keyboard();
      }
      return false;
      break;
    case ANGLE:
      if (record->event.pressed) {
        if (keyboard_report->mods & MOD_BIT(KC_LSFT) || keyboard_report->mods & MOD_BIT(KC_RSFT)){
          clear_mods();
          register_code(KC_LSFT);
          register_code(KC_DOT);
        } else {
          register_code(KC_LSFT);
          register_code(KC_COMMA);
        }
        clear_keyboard();
      }
      return false;
      break;
    case SQUAR:
      if (record->event.pressed) {
        if (keyboard_report->mods & MOD_BIT(KC_LSFT) || keyboard_report->mods & MOD_BIT(KC_RSFT)){
          clear_mods();
          register_code(KC_RBRC);
        } else {
          register_code(KC_RBRC);
        }
        clear_keyboard();
      }
      return false;
      break;
    case DOT:
      if (record->event.pressed) {
        if (keyboard_report->mods & MOD_BIT(KC_LSFT) || keyboard_report->mods & MOD_BIT(KC_RSFT)){
          clear_mods();
          register_code(KC_DOT);
        } else {
          register_code(KC_COMMA);
        }
        clear_keyboard();
      }
      return false;
      break;
  }
  return true;
}