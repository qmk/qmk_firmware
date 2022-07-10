/* Copyright 2021 Jay Morrow
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

enum planck_layers {
  _QWERTY,
  _COLEMAK,
  _LEAGUE,
  _LOWER,
  _RAISE,
  _ADJUST,
  _LRAISE,
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  LEAGUE,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJUST MO(_ADJUST)
#define LRAISE MO(_LRAISE)

#define KC_LQ LCTL(KC_Q)
#define KC_LW LCTL(KC_W)
#define KC_LE LCTL(KC_E)
#define KC_LR LCTL(KC_R)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Adjst| Ctrl | Alt  | GUI  | SPC  | Lower| Raise| Enter| Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    ADJUST,  KC_LCTL, KC_LALT, KC_LGUI, KC_SPC,  LOWER,   RAISE,   KC_ENT,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Adjst| Ctrl | Alt  | GUI  | SPC  | Lower| Raise| Enter| Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
    KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    ADJUST,  KC_LCTL, KC_LALT, KC_LGUI, KC_SPC,  LOWER,   RAISE,   KC_ENT,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* League
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |  1   |  2   |  3   |  4   |  5   |  6   |  7   |      |      |      | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |  Q   |  W   |  E   |  R   |  G   |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   P  |  B   |  S   |  D   |  F   |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Adjust|      |      |      |      | Spc  | Raise|      | Ent  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LEAGUE] = LAYOUT_planck_grid(
    KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    XXXXXXX,  XXXXXXX, XXXXXXX, KC_BSPC,
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_G,    XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,
    KC_P,    KC_B,    KC_S,    KC_D,    KC_F,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,
    ADJUST,  XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC,  LRAISE,  XXXXXXX, KC_ENT,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   `  |      |   _  |   +  |   \  |   {  |   }  |      |   7  |   8  |   9  |  /   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   ~  |      |   _  |   =  |   |  |   [  |   ]  |      |   4  |   5  |   6  |  *   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |   (  |   )  |      |   1  |   2  |   3  |  -   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |  0   |   ,  |  .   |  +   |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_GRV,  XXXXXXX, KC_MINS, KC_PLUS, KC_BSLS, KC_LCBR, KC_RCBR, XXXXXXX,  KC_7,    KC_8,    KC_9,    KC_SLSH,
    KC_TILD, XXXXXXX, KC_UNDS,  KC_EQL, KC_PIPE, KC_LBRC, KC_RBRC, XXXXXXX,  KC_4,    KC_5,    KC_6,    KC_ASTR,
    _______, _______, _______, _______, _______, KC_LPRN, KC_RPRN, XXXXXXX,  KC_1,    KC_2,    KC_3,    KC_MINS,
    _______, _______, _______, _______, _______, _______, _______, _______,  KC_0,    KC_COMM, KC_DOT,  KC_PLUS
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   F1 |   F2 |   F3 |   F4 |   F5 |  F6  |  F7  |  F8  |  F9  |  F10 | Home |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |   !  |   @  |  #   |   $  |  %   |  ^   |  &   |  *   |      |      | PgUp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | Vol- |  BR- |  BR+ | Vol+ |      |      |      | PgDn |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_TILD, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_HOME,
    KC_DEL,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR,  _______, _______, KC_PGUP,
    _______, _______, _______, _______, KC_VOLD, KC_BRMD, KC_BRMU, KC_VOLU,  _______, _______, _______, KC_PGDN,
    _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, KC_END
),

/* Adjust
 * ,-----------------------------------------------------------------------------------.
 * |Reset |Debug |      |      |      |      |      |      |      |      |      |Qwerty|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |Colmk |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |League|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    RESET,   DEBUG,   _______, _______, _______, _______, _______, _______, _______, _______, _______, QWERTY,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, COLEMAK,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, LEAGUE,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* League Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |  F2  |  F3  |  F4  |  F5  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Ctrl-Q|Ctrl-W|Ctrl-E|Ctrl-R|      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LRAISE] = LAYOUT_planck_grid(
    _______, KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______, _______, _______,  _______, _______, _______,
    _______, KC_LQ,   KC_LW,   KC_LE,   KC_LR,   _______, _______, _______, _______,  _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
),


};

// set the default layer in ROM so that we preserve state across power transitions
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
   case LEAGUE:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_LEAGUE);
      }
      return false;
      break;
  }
  return true;
}
