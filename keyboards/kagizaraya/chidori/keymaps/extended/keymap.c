/* Copyright 2019 ENDO Katsuhiro <ka2hiro@kagizaraya.jp>
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

#include "board.h"

enum layer_number { _QWERTY = 0, _COLEMAK, _DVORAK, _LOWER, _RAISE, _ADJUST };

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes { QWERTY = SAFE_RANGE, COLEMAK, DVORAK };

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ADJUST MO(_ADJUST)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.             ,-----------------------------------------.
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  | Bksp |             |   7  |   8  |   9  |      |NumLck| Esc  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|             |------+------+------|  +   |------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  '   |             |   4  |   5  |   6  |      |   /  | Tab  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |             |   N  |   M  |   ,  |   .  |   /  |Enter |             |   1  |   2  |   3  |      |   *  |  =   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|             |-------------+------|Enter |------+------|
   * |ADJUST| Esc  | Alt  | GUI  |LOWER |Space |             | Space| RAISE| Left | Down |  Up  | Right|             |      0      |   .  |      |   -  | Bksp |
   * `-----------------------------------------'             `-----------------------------------------'             `-----------------------------------------'
   */
    [_QWERTY] = LAYOUT_extended(
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,              KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,         KC_P7,   KC_P8,   KC_P9,  KC_PPLS, KC_NLCK, KC_ESC,
      KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,              KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,         KC_P4,   KC_P5,   KC_P6,  _______, KC_PSLS, KC_TAB,
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,              KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,         KC_P1,   KC_P2,   KC_P3,  KC_PENT, KC_PAST, KC_PEQL,
      ADJUST,  KC_ESC,  KC_LALT, KC_LGUI, LOWER,   KC_SPC,            KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,      KC_P0,   _______, KC_PDOT,_______, KC_PMNS, KC_BSPC
    ),
  /* Colemak
   * ,-----------------------------------------.             ,-----------------------------------------.             ,-----------------------------------------.
   * | Tab  |   Q  |   W  |   F  |   P  |   G  |             |   J  |   L  |   U  |   Y  |   ;  | Bksp |             |   7  |   8  |   9  |      |NumLck| Esc  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|             |------+------+------|  +   |------+------|
   * | Ctrl |   A  |   R  |   S  |   T  |   D  |             |   H  |   N  |   E  |   I  |   O  |  '   |             |   4  |   5  |   6  |      |   /  | Tab  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |             |   K  |   M  |   ,  |   .  |   /  |Enter |             |   1  |   2  |   3  |      |   *  |  =   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|             |-------------+------|Enter |------+------|
   * |ADJUST| Esc  | Alt  | GUI  |LOWER |Space |             | Space| RAISE| Left | Down |  Up  | Right|             |      0      |   .  |      |   -  | Bksp |
   * `-----------------------------------------'             `-----------------------------------------'             `-----------------------------------------'
   */
    [_COLEMAK] = LAYOUT_extended(
      KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,              KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,       KC_P7,   KC_P8,   KC_P9,  KC_PPLS, KC_NLCK, KC_ESC,
      KC_LCTL, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,              KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,       KC_P4,   KC_P5,   KC_P6,  _______, KC_PSLS, KC_TAB,
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,              KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,       KC_P1,   KC_P2,   KC_P3,  KC_PENT, KC_PAST, KC_PEQL,
      ADJUST,  KC_ESC,  KC_LALT, KC_LGUI, LOWER,   KC_SPC,            KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,       KC_P0,   _______, KC_PDOT,_______, KC_PMNS, KC_BSPC
    ),

  /* Dvorak
   * ,-----------------------------------------.             ,-----------------------------------------.             ,-----------------------------------------.
   * | Tab  |   '  |   ,  |   .  |   P  |   Y  |             |   F  |   G  |   C  |   R  |   L  | Del  |             |   7  |   8  |   9  |      |NumLck| Esc  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|             |------+------+------|  +   |------+------|
   * | Ctrl |   A  |   O  |   E  |   U  |   I  |             |   D  |   H  |   T  |   N  |   S  |  /   |             |   4  |   5  |   6  |      |   /  | Tab  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Shift|   ;  |   Q  |   J  |   K  |   X  |             |   B  |   M  |   W  |   V  |   Z  |Enter |             |   1  |   2  |   3  |      |   *  |  =   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|             |-------------+------|Enter |------+------|
   * |ADJUST| Esc  | Alt  | GUI  |LOWER |Space |             | Space| RAISE| Left | Down |  Up  | Right|             |      0      |   .  |      |   -  | Bksp |
   * `-----------------------------------------'             `-----------------------------------------'             `-----------------------------------------'
   */
    [_DVORAK] = LAYOUT_extended(
      KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,              KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_DEL,        KC_P7,   KC_P8,   KC_P9,  KC_PPLS, KC_NLCK, KC_ESC,
      KC_LCTL, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,              KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH,       KC_P4,   KC_P5,   KC_P6,  _______, KC_PSLS, KC_TAB,
      KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,              KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_ENT ,       KC_P1,   KC_P2,   KC_P3,  KC_PENT, KC_PAST, KC_PEQL,
      ADJUST,  KC_ESC,  KC_LALT, KC_LGUI, LOWER,   KC_SPC,            KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,       KC_P0,   _______, KC_PDOT,_______, KC_PMNS, KC_BSPC
    ),

  /* Lower
   * ,-----------------------------------------.             ,-----------------------------------------.             ,-----------------------------------------.
   * |   ~  |   !  |   @  |   #  |   $  |   %  |             |   ^  |   &  |   *  |   (  |   )  |      |             |   7  |   8  |   9  |      |NumLck| Esc  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|             |------+------+------|  +   |------+------|
   * |      |      |      |      |      |      |             |   -  |   _  |   +  |   {  |   }  |  |   |             |   4  |   5  |   6  |      |   /  | Tab  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      |      | Home | End  |      |             |   1  |   2  |   3  |      |   *  |  =   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|             |-------------+------|Enter |------+------|
   * |      |      |      |      |      |      |             |      |      | Next | Vol- | Vol+ | Play |             |      0      |   .  |      |   -  | Bksp |
   * `-----------------------------------------'             `-----------------------------------------'             `-----------------------------------------'
   */
    [_LOWER] = LAYOUT_extended(
      KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,           KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,       KC_P7,   KC_P8,   KC_P9,  KC_PPLS, KC_NLCK, KC_ESC,
      _______, _______, _______, _______, _______, _______,           KC_MINS, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,       KC_P4,   KC_P5,   KC_P6,  _______, KC_PSLS, KC_TAB,
      _______, _______, _______, _______, _______, _______,           _______, _______, _______, KC_HOME, KC_END,  _______,       KC_P1,   KC_P2,   KC_P3,  KC_PENT, KC_PAST, KC_PEQL,
      _______, _______, _______, _______, _______, _______,           _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY,       KC_P0,   _______, KC_PDOT,_______, KC_PMNS, KC_BSPC
    ),

  /* Raise
   * ,-----------------------------------------.             ,-----------------------------------------.             ,-----------------------------------------.
   * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Del  |             |   7  |   8  |   9  |      |NumLck| Esc  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|             |------+------+------|  +   |------+------|
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |   -  |   =  |   [  |   ]  |  \   |             |   4  |   5  |   6  |      |   /  | Tab  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |  F7  |  F8  |  F9  |  F10 |  F11 |             |  F12 |      |      |      |      |                    |   1  |   2  |   3  |      |   *  |  =   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|             |-------------+------|Enter |------+------|
   * |      |      |      |      |      |      |             |      |      | Next | Vol- | Vol+ | Play |             |      0      |   .  |      |   -  | Bksp |
   * `-----------------------------------------'             `-----------------------------------------'             `-----------------------------------------'
   */
    [_RAISE] = LAYOUT_extended(
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,              KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,        KC_P7,   KC_P8,   KC_P9,  KC_PPLS, KC_NLCK, KC_ESC,
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,             KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,       KC_P4,   KC_P5,   KC_P6,  _______, KC_PSLS, KC_TAB,
      _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,            KC_F12,  _______, _______, _______, _______, _______,       KC_P1,   KC_P2,   KC_P3,  KC_PENT, KC_PAST, KC_PEQL,
      _______, _______, _______, _______, _______, _______,           _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY,       KC_P0,   _______, KC_PDOT,_______, KC_PMNS, KC_BSPC
    ),

  /* Adjust (Lower + Raise)
   * ,-----------------------------------------.             ,-----------------------------------------.             ,-----------------------------------------.
   * |      | Reset|      |      |      |      |             |      |Qwerty|Colemk|Dvorak|      | Ins  |             |   7  |   8  |   9  |      |NumLck| Esc  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|             |------+------+------|  +   |------+------|
   * | Caps |      |      |      |      | Mac  |             | Win  |  -   |   =  |Print |ScLock|Pause |             |   4  |   5  |   6  |      |   /  | Tab  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |             |   1  |   2  |   3  |      |   *  |  =   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|             |-------------+------|Enter |------+------|
   * |      |      |      |      |      |      |             |      |      | Home |PageDn|PageUp| End  |             |      0      |   .  |      |   -  | Bksp |
   * `-----------------------------------------'             `-----------------------------------------'             `-----------------------------------------'
   */
    [_ADJUST] = LAYOUT_extended(
      _______, QK_BOOT, _______, _______, _______, _______,           _______, QWERTY,  COLEMAK, DVORAK,  _______, KC_INS,        KC_P7,   KC_P8,   KC_P9,  KC_PPLS, KC_NLCK, KC_ESC,
      KC_CAPS, _______, _______, _______, _______, AG_NORM,           AG_SWAP, KC_MINS, KC_EQL,  KC_PSCR, KC_SLCK, KC_PAUS,       KC_P4,   KC_P5,   KC_P6,  _______, KC_PSLS, KC_TAB,
      _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______,       KC_P1,   KC_P2,   KC_P3,  KC_PENT, KC_PAST, KC_PEQL,
      _______, _______, _______, _______, _______, _______,           _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,        KC_P0,   _______, KC_PDOT,_______, KC_PMNS, KC_BSPC
    )
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
        case DVORAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_DVORAK);
            }
            return false;
    }
    return true;
}

bool led_update_user(led_t led_state) {
    board_set_led_by_index(0, LED_YELLOW, led_state.caps_lock);
    board_set_led_by_index(1, LED_YELLOW, led_state.scroll_lock);
    board_set_led_by_index(2, LED_YELLOW, led_state.num_lock);

    return false;
}
