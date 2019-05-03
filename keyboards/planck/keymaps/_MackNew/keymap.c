<<<<<<< HEAD:keyboards/planck/keymaps/_MackNew/keymap.c
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

=======
>>>>>>> parent of ee4e25aea... Merge branch 'master' of https://github.com/JMackWoodie/qmk_firmware:keyboards/jj40/keymaps/default/keymap.c
#include QMK_KEYBOARD_H
#include "muse.h"

extern keymap_config_t keymap_config;

<<<<<<< HEAD:keyboards/planck/keymaps/_MackNew/keymap.c
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
=======

#define _QWERTY 0
#define _LOWER  1
#define _RAISE  2

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
};
>>>>>>> parent of ee4e25aea... Merge branch 'master' of https://github.com/JMackWoodie/qmk_firmware:keyboards/jj40/keymaps/default/keymap.c

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
<<<<<<< HEAD:keyboards/planck/keymaps/_MackNew/keymap.c
[_QWERTY] = LAYOUT_planck_grid(
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,              KC_BSPC,
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,              KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, MT(MOD_RSFT, KC_ENT),
  KC_LCTL, KC_APP, KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE, KC_LEFT, KC_DOWN,   KC_UP,              KC_RGHT
=======
[_QWERTY] = LAYOUT_2U_space( \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT , \
  _______, KC_LCTL, KC_LALT, KC_LGUI, MO(_LOWER),  KC_SPC,  MO(_RAISE),   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
>>>>>>> parent of ee4e25aea... Merge branch 'master' of https://github.com/JMackWoodie/qmk_firmware:keyboards/jj40/keymaps/default/keymap.c
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |      |      |      |      |      |      |      |  &   |   *  |      | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | DTL  | DTR  |      |      | PgUp | Home |   _  |  $   |   %  |   ^  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      | PgDn |  End |   =  |  !   |   @  |   #  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Left | Down |  Up  | Rght |
 * `-----------------------------------------------------------------------------------'
 */
<<<<<<< HEAD:keyboards/planck/keymaps/_MackNew/keymap.c
[_LOWER] = LAYOUT_planck_grid(
  KC_TILD,                    ,                    ,        ,        ,        ,        ,        , KC_AMPR, KC_ASTR,        ,  KC_DEL,
  _______, LCTL(LGUI(KC_LEFT)), LCTL(LGUI(KC_RGHT)), _______, _______, KC_PGUP, KC_HOME, KC_UNDS,  KC_DLR, KC_PERC, KC_CIRC, KC_PIPE,
  _______,             _______,             _______, _______, _______, KC_PGDN,  KC_END,  KC_EQL, KC_EXLM,  KC_AT,  KC_HASH, _______,
  _______,             _______,             _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT
=======
[_LOWER] = LAYOUT_2U_space( \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,S(KC_NUHS),S(KC_NUBS),_______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
>>>>>>> parent of ee4e25aea... Merge branch 'master' of https://github.com/JMackWoodie/qmk_firmware:keyboards/jj40/keymaps/default/keymap.c
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
<<<<<<< HEAD:keyboards/planck/keymaps/_MackNew/keymap.c
[_RAISE] = LAYOUT_planck_grid(
  KC_GRV,         ,        ,        ,        , KC_LPRN, KC_RPRN, KC_PLUS,    KC_7,    KC_8,    KC_9, KC_BSPC,
  _______,        ,        ,        ,        , KC_LCBR, KC_RCBR, KC_MINS,    KC_4,    KC_5,    KC_6, KC_BSLS,
  _______,        ,        ,        ,        , KC_LBRC, KC_RBRC,  KC_EQL,    KC_1,    KC_2,    KC_3, _______,
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
  _______,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, _______,         ,        ,        , _______,
  _______, _______, _______, _______, _______, _______, _______, _______,         ,        ,        , _______
=======
[_RAISE] = LAYOUT_2U_space( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
>>>>>>> parent of ee4e25aea... Merge branch 'master' of https://github.com/JMackWoodie/qmk_firmware:keyboards/jj40/keymaps/default/keymap.c
)


};

<<<<<<< HEAD:keyboards/planck/keymaps/_MackNew/keymap.c
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


=======
// Loop
void matrix_scan_user(void) {
  // Empty
};
>>>>>>> parent of ee4e25aea... Merge branch 'master' of https://github.com/JMackWoodie/qmk_firmware:keyboards/jj40/keymaps/default/keymap.c
