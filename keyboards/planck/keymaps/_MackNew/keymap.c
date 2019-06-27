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

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Menu |  Gui |  Alt |Lower |    Space    |Raise | Left | Down |  Up  | Rght |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,              KC_BSPC,
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,              KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, MT(MOD_RSFT, KC_ENT),
  KC_LCTL, KC_APP, KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE, KC_LEFT, KC_DOWN,   KC_UP,              KC_RGHT
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |      |      |  (   |  )   |      |      |      |  &   |   *  |      | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | DTL  | DTR  |  {   |  }   | PgUp | Home |   _  |  $   |   %  |   ^  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |  [   |  ]   | PgDn |  End |   =  |  !   |   @  |   #  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Left | Down |  Up  | Rght |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
  KC_TILD,             _______,             _______, KC_LPRN, KC_RPRN, _______, _______, _______, KC_AMPR, KC_ASTR, _______,  KC_DEL,
  _______, LCTL(LGUI(KC_LEFT)), LCTL(LGUI(KC_RGHT)), KC_LCBR, KC_RCBR, KC_PGUP, KC_HOME, KC_UNDS,  KC_DLR, KC_PERC, KC_CIRC, KC_PIPE,
  _______,             _______,             _______, KC_LBRC, KC_RBRC, KC_PGDN,  KC_END,  KC_EQL, KC_EXLM,  KC_AT,  KC_HASH, _______,
  _______,             _______,             _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |      |      |      |      |   (  |   )  |   +  |   7  |   8  |   9  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |   {  |   }  |   -  |   4  |   5  |   6  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |   [  |   ]  |   =  |   1  |   2  |   3  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |   0  |   .  |   /  |  *   |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
  KC_GRV,  _______, _______, _______, _______, _______, _______, KC_PLUS,    KC_7,    KC_8,    KC_9, KC_BSPC,
  _______, _______, _______, _______, _______, _______, _______, KC_MINS,    KC_4,    KC_5,    KC_6, KC_BSLS,
  _______, _______, _______, _______, _______, _______, _______,  KC_EQL,    KC_1,    KC_2,    KC_3, _______,
  _______, _______, _______, _______, _______, _______, _______, _______,    KC_0,  KC_DOT, KC_SLSH, KC_ASTR
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      | PScr |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
  _______,   RESET, _______, _______, _______, _______, _______, _______,  _______, _______, KC_PSCR, KC_DEL ,
  _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6, _______,  _______, _______, _______, _______,
  _______,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, _______,  _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______
)


};

uint32_t layer_state_set_user(uint32_t state) {
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
  }
  return true;
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}


