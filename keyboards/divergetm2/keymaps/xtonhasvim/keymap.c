 /* Copyright 2018 Christon DeWan
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
#include "xtonhasvim.h"

/************************************
 * states
 ************************************/

enum layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
  _MOVE,
  _MOUSE,
  _CMD
};

extern uint8_t vim_cmd_layer(void) { return _CMD; }

enum keymap_keycodes {
  RAISE = VIM_SAFE_RANGE,
  LOWER
};

/************************************
 * keymaps!
 ************************************/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl*|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;* |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | chkwm|      | Alt  | GUI  |   Lower*    |    Raise*   | SPC  | GUI  |      | Vim  |
 * `-----------------------------------------------------------------------------------'
 *
 * - Ctrl acts as Esc when tapped.
 * - Holding ; switches to movement layer.
 * - Tapping raise or lower produces space.
 */
[_QWERTY] = LAYOUT_ortho_4x12_2x2u( \
  KC_TAB,  KC_Q,           KC_W,    KC_E,    KC_R,          KC_T,    KC_Y,    KC_U,          KC_I,    KC_O,    KC_P,              KC_BSPC, \
  LCTL_T(KC_ESC), KC_A, KC_S,    KC_D,    KC_F,          KC_G,    KC_H,    KC_J,          KC_K,    KC_L,    LT(_MOVE,KC_SCLN), KC_QUOT, \
  KC_LSFT, KC_Z,           KC_X,    KC_C,    KC_V,          KC_B,    KC_N,    KC_M,          KC_COMM, KC_DOT,  KC_SLSH,   RSFT_T(KC_ENT) , \
  LSFT(KC_LALT), MO(_MOVE),  KC_LALT, KC_LGUI, LT(_LOWER, KC_SPC), LT(_RAISE, KC_SPC),   KC_RGUI, KC_RALT, MO(_MOVE), VIM_START \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  ~   |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  Del |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      | Next | Vol- | Vol+ | Play |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Bail |      |      |             |   Raise     |      |      | Bail |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_4x12_2x2u( \
  KC_TILD,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_BSPC, \
  KC_DEL, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_PIPE, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  X_____X, X_____X, X_____X, X_____X, FIREY_RETURN, \
  RESET, TO(_QWERTY), _______, _______, _______,              MO(_RAISE), _______, _______, TO(_QWERTY), X_____X \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  Del |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      | Next | Vol- | Vol+ | Play |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Bail |      |      |   Lower     |             |      |      | Bail |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_4x12_2x2u( \
  KC_GRV,  X_____X,   X_____X,   X_____X,   X_____X,   X_____X,   X_____X,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSPC, \
  KC_DEL,  KC_1,      KC_2,      KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, \
  _______, X_____X, X_____X,   X_____X,   X_____X,  X_____X,  X_____X,  X_____X, X_____X, X_____X, X_____X, FIREY_RETURN, \
  X_____X, TO(_QWERTY), _______, _______, MO(_LOWER),                      _______, _______, _______, TO(_QWERTY), RESET \
),


/* Adjust (Lower + Raise)
 * ,-------------------------------------------------------------------------------------.
 * |BL Raise|      |      |      |      |      |      |      |      |      |      |      |
 * |--------+------+------+------+------+-------------+------+------+------+------+------|
 * |BL Lower|      |      |      |      |      |      |      |      |      |      |      |
 * |--------+------+------+------+------+------|------+------+------+------+------+------|
 * |BL STEP |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |      |
 * |--------+------+------+------+------+------+------+------+------+------+------+------|
 * |Backlite| Mouse|      |      |             |             |      |      | Bail |      |
 * `-------------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_ortho_4x12_2x2u( \
  BL_INC, X_____X,   X_____X,   X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, \
  BL_DEC, X_____X, X_____X,  X_____X,   X_____X,  X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, \
  BL_STEP, X_____X,  X_____X,  X_____X,  X_____X,  X_____X, X_____X,  KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY, X_____X, \
  BL_TOGG, TO(_MOUSE), _______, _______, _______,                 _______, _______, _______, TO(_QWERTY), X_____X \
),


/* movement layer (hold semicolon) */
[_MOVE] = LAYOUT_ortho_4x12_2x2u( \
  TO(_QWERTY), X_____X, X_____X, X_____X, X_____X, X_____X, KC_HOME, KC_PGDN, KC_PGUP, KC_END, X_____X, X_____X, \
  _______,     X_____X, LGUI(KC_LBRC), LGUI(LSFT(KC_LBRC)), LGUI(LSFT(KC_RBRC)), LGUI(KC_RBRC), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, X_____X, \
  _______,     X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, _______, \
  _______,     _______, _______, _______, _______,                   _______, _______, _______, _______, X_____X \
),

/* mouse layer
 */
[_MOUSE] = LAYOUT_ortho_4x12_2x2u( \
  TO(_QWERTY), X_____X, X_____X, KC_MS_UP, X_____X, X_____X, KC_MS_WH_LEFT, KC_MS_WH_DOWN, KC_MS_WH_UP, KC_MS_WH_RIGHT, X_____X, X_____X  , \
  _______,     X_____X, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, X_____X, X_____X, KC_MS_BTN1, KC_MS_BTN2, KC_MS_BTN3, X_____X, X_____X, \
  _______,     X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, _______, \
  _______,     TO(_QWERTY), _______, _______, _______,                    _______, _______, _______, TO(_QWERTY), X_____X \
),

/* vim command layer.
 */
[_CMD] = LAYOUT_ortho_4x12_2x2u( \
  X_____X, X_____X, VIM_W, VIM_E, X_____X, X_____X, VIM_Y, VIM_U, VIM_I, VIM_O, VIM_P, X_____X, \
  VIM_ESC,    VIM_A, VIM_S, VIM_D, X_____X, VIM_G, VIM_H, VIM_J, VIM_K, VIM_L, X_____X, X_____X, \
  VIM_SHIFT,     X_____X, VIM_X, VIM_C, VIM_V, VIM_B, X_____X, X_____X, VIM_COMMA, VIM_PERIOD, X_____X, VIM_SHIFT, \
  _______,     TO(_QWERTY), _______, _______, X_____X,                 X_____X, _______, _______, TO(_QWERTY), X_____X \
)

};

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
}
