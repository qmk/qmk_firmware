/* Copyright 2020 winterNebs <winternebs@gmail.com>
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
enum layers {
    _QWERTY,
    _WORKMAN,
    _LOWER,
    _ADJUST,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  WORKMAN,
};

#define LOWER MO(_LOWER)
#define ADJUST MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  |      | Alt  |Lower |Space | Bksp |Adjust|      | Left | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT( 
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, 
  KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL, 
  KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, 
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT , 
  KC_LCTL, KC_LGUI, _______, KC_LALT, LOWER,   KC_SPC,  KC_BSPC, ADJUST,  z, KC_LEFT, KC_DOWN,   KC_RGHT 
),
/* Workman
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   Q  |   D  |   R  |   W  |   B  |   J  |   F  |   U  |   P  |   ;  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   H  |   T  |   G  |   Y  |   N  |   E  |   O  |   I  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   M  |   C  |   V  |   K  |   L  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  |      | Alt  |Lower |Space | Bksp |Adjust|      | Left | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_WORKMAN] = LAYOUT( 
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, 
  KC_ESC,  KC_Q,    KC_D,    KC_R,    KC_W,    KC_B,    KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN, KC_DEL, 
  KC_TAB,  KC_A,    KC_S,    KC_H,    KC_T,    KC_G,    KC_Y,    KC_N,    KC_E,    KC_O,    KC_I,	 KC_QUOT, 
  KC_LSFT, KC_Z,    KC_X,    KC_M,    KC_C,    KC_V,    KC_K,    KC_L,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT , 
  KC_LCTL, KC_LGUI, _______, KC_LALT, LOWER,   KC_SPC,  KC_BSPC, ADJUST,  _______, KC_LEFT, KC_DOWN, KC_RGHT 
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   `  |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      |Pg Up |  UP  |Pg Dn |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |PrScr |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT( 
  KC_GRV,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
  KC_DEL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, 
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, 
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, KC_PGUP, KC_UP,	 KC_PGDN, 
  _______, _______, KC_PSCR, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * | Reset|RGB Tg|RGB Md|Hue Up|Hue Dn|      |      |      |      | ScrL | ScrR |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Sat Up|Sat Dn|Val Up|Val Dn|AGnorm|AGswap| Home |  M1  |  ^   |  M2  |ScrUp |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Qwerty|WORKMN|      | End  |  <   |  v   |  >   |Scrdn |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      | Left | Down | Up   |Right | Vol+ |Pause |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | NKRO |      |      |      |      |             |      |      | Last | Vol- | Next |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] =  LAYOUT( 
  RESET,   RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, _______, _______, _______, _______, KC_WH_L, KC_WH_R, _______,
  RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, AG_NORM, AG_SWAP, KC_HOME, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U, _______, 
  _______, _______, _______, QWERTY,  WORKMAN, _______, KC_END,  KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, _______,
  _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_VOLU, KC_MPLY, 
  MAGIC_TOGGLE_NKRO, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_VOLD, KC_MNXT 
)


};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case WORKMAN:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_WORKMAN);
      }
      return false;
      break;
  }
  return true;
}
