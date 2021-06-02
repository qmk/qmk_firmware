/* Copyright 2021 rookiebwoy
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

#include "keymap_italian.h"

enum layers {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |  Esc |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Canc |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  Tab |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   '  |   \  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   -  | Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  End | Ctrl | GUI  |  Alt | Lower| Bksp | Space| Raise| Left | Down |  Up  | Right|
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_4x12( \
  KC_ESC,  IT_Q,    IT_W,    IT_E,    IT_R,    IT_T,    IT_Y,    IT_U,    IT_I,    IT_O,    IT_P,    KC_DEL,  \
  KC_TAB,  IT_A,    IT_S,    IT_D,    IT_F,    IT_G,    IT_H,    IT_J,    IT_K,    IT_L,    IT_QUOT, IT_BSLS, \
  KC_LSFT, IT_Z,    IT_X,    IT_C,    IT_V,    IT_B,    IT_N,    IT_M,    IT_COMM, IT_DOT,  IT_MINS, KC_ENT , \
  KC_END,  KC_LCTL, KC_LGUI, KC_LALT, LOWER,   KC_BSPC, KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * | Reset|      |      |Alt+F4|      |      |      |      |   7  |   8  |   9  |   *  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |Prntsc| Explr| Trmnl|      |      |      |   4  |   5  |   6  |   /  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      | Menu |      |  F2  |      |      |      |   1  |   2  |   3  |   +  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |   0  |   .  |   =  |   -  |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_4x12( \
  RESET,   _______, _______,    A(KC_F4), _______,   _______, _______, _______, IT_7,    IT_8,    IT_9,    IT_ASTR, \
  _______, _______, S(KC_PSCR), G(IT_E),  LCA(IT_T), _______, _______, _______, IT_4,    IT_5,    IT_6,    IT_SLSH, \
  _______, _______, KC_APP,     _______,  KC_F2,     _______, _______, _______, IT_1,    IT_2,    IT_3,    IT_PLUS, \
  _______, _______, _______,    _______,  _______,   _______, _______, _______, IT_0,    IT_DOT,  IT_EQL,  IT_MINS  \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |   €  |   $  |   %  |   &  |   {  |   }  |   ~  |      |      |   `  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   =  |   !  |   ?  |   (  |   [  |   ]  |   )  |   #  |   @  |   "  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |   °  |   ^  |   |  |   <  |   >  |      |   ;  |   :  |   _  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_4x12( \
  _______, IT_EURO, IT_DLR,  IT_PERC, IT_AMPR, IT_LCBR, IT_RCBR, RALT(IT_IGRV), _______, _______, RALT(IT_QUOT), _______, \
  _______, IT_EQL,  IT_EXLM, IT_QUES, IT_LPRN, IT_LBRC, IT_RBRC, IT_RPRN,       IT_HASH, IT_AT,   IT_DQUO,       _______, \
  _______, _______, IT_DEG,  IT_CIRC, IT_PIPE, IT_LABK, IT_RABK, _______,       IT_SCLN, IT_COLN, IT_UNDS,       _______, \
  _______, _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______,       _______  \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |   è  |   é  |      |      |   ù  |   ì  |   ò  |      | Hue  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   à  |      |Nxttab|Dskt D|Wndw D|Wndw U|Dskt U|Prvtab|      |      | Sat  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      | Brigt|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |RGBtog|RGBmod|
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] =  LAYOUT_ortho_4x12( \
  _______, _______, _______, IT_EGRV,    IT_EACU,    _______,       _______,       IT_UGRV,    IT_IGRV,    IT_OGRV, _______, RGB_HUI, \
  _______, IT_AGRV, _______, C(KC_PGDN), G(KC_PGDN), SGUI(KC_PGDN), SGUI(KC_PGUP), G(KC_PGUP), C(KC_PGUP), _______, _______, RGB_SAI, \
  _______, _______, _______, _______,    _______,    _______,       _______,       _______,    _______,    _______, _______, RGB_VAI, \
  _______, _______, _______, _______,    _______,    _______,       _______,       _______,    _______,    _______, RGB_TOG, RGB_MOD  \
)
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
