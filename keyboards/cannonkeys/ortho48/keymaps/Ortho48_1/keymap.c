/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BASE 0
#define _RAISE 1
#define _LOWER 2
#define _RAISE2 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  RAISE2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Raise2| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_BASE] = LAYOUT_ortho_4x12(
    KC_GESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
    MO(_RAISE2), KC_LCTL, KC_LALT, KC_LGUI, MO(_LOWER),   KC_SPC,  KC_SPC,  MO(_RAISE),   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),
/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |      |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      |      |BriUp | Home | PgUp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |BriDn | End  | PgDn |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_4x12(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_DEL,
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6, _______,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, _______,  _______,    _______,    KC_BRIU, KC_HOME, KC_PGUP,
    RESET,   _______, _______, _______, _______, _______, _______, _______,    _______,    KC_BRID, KC_END,  KC_PGDN
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |      |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      |      | Vol+ | Play | Next |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      | Vol- |      | Prev |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_4x12(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6, _______,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, _______,  _______, _______, KC_VOLU, KC_MPLY, KC_MNXT,
    RGB_TOG, RGB_MOD, BL_INC,  BL_DEC, _______, _______, _______, _______,  _______, KC_VOLD, _______, KC_MPRV
),
/* Raise2 -- Numpad Layer
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |NUM_7 |NUM_8 |NUM_9 |NUM_/ |NUM_- | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |NUM_4 |NUM_5 |NUM_6 |NUM_* |NUM_+ |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |NUM_0 |NUM_1 |NUM_2 |NUM_3 |NUM_. |NUM_= |nEnter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE2] = LAYOUT_ortho_4x12(
    _______,  _______,  _______, _______, _______,  _______,  KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_SLASH,    KC_KP_MINUS, KC_BSPC,
    _______,  _______,  _______, _______, _______,  _______,  KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_ASTERISK, KC_KP_PLUS,  _______,
    _______,  _______,  _______, _______, _______,  KC_KP_0,  KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_DOT,      KC_KP_EQUAL, KC_KP_ENTER,
    _______,  _______,  _______, _______, _______,  _______,  _______, _______, _______, _______, _______, _______
),
};
