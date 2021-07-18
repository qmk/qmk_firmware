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
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST
};

#define LOWER LT(_LOWER, KC_ENT)
#define RAISE LT(_RAISE, KC_BSPC)

#define HYP_ESC HYPR_T(KC_ESC)
#define SHF_TAB LSFT_T(KC_TAB)
#define CMD_EQL LGUI_T(KC_EQUAL)
#define SHFTDEL LSFT_T(KC_DEL)
#define CTL_EQL LCTL_T(KC_EQUAL)
#define SHF_QUO LSFT_T(KC_QUOT)
#define UNDO LCMD(KC_Z)
#define REDO LCMD(LSFT(KC_Z))

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   -  |'
 * | Hyper|      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * | Shift|      |      |      |      |      |      |      |      |      |      |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |  =+  |Enter |    Space    |Bksp  | Del  |      |      |      |
 * |      | UNDO | Alt  |  CMD |Lower |             |Raise | Shift| Ctrl | REDO |      |
 * `-----------------------------------------------------------------------------------'
 */
[_BASE] = LAYOUT_planck_grid(
    HYP_ESC, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,    KC_MINUS,
    SHF_TAB, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,     KC_SCLN, SHF_QUO,
    _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH, _______,
    _______, UNDO, KC_LALT, CMD_EQL,   LOWER,  KC_SPC,  KC_SPC,   RAISE,    SHFTDEL, KC_LCTRL, REDO,    _______
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |   !  |   @  |   #  |   $  |   £  |      |   (  |   )  |  [   |   ]  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   ^  |   &  |   *  |   %  |   €  |      |   {  |   }  |  =   |  +   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |   ~  | Undo | Redo |      |      |   |  |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    _______, KC_EXLM, KC_AT,   A(KC_3), KC_DLR,  KC_HASH, _______, KC_LPRN,    KC_RPRN,    KC_LBRC, KC_RBRC, _______,
    _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_PERC, A(KC_2), _______, S(KC_LBRC), S(KC_RBRC), KC_EQUAL, KC_PLUS, _______,
    _______, _______, KC_TILD, UNDO,    REDO,    _______, _______, KC_PIPE,    _______,    _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______,    _______,    _______, _______, _______
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |   1  |   2  |   3  |   4  |   5  |      |  ⏯  |  ⏮️   |  ⏭️  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   6  |   7  |   8  |   9  |   0  |      | Left | Right|  Up  | Down |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | Mute | Vol- | Vol+ |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_MPLY, KC_MPRV, KC_MNXT, _______, _______,
    _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, KC_LEFT, KC_RGHT, KC_UP,   KC_DOWN, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Reset |      |      |      |      |      |      |      |      |      |      |Debug |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______,
    RESET  , _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, DEBUG  ,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
)

};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
