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
#include "keymap_swedish.h"

extern keymap_config_t keymap_config;

enum planck_layers {
                    _COLEMAK,
                    _LOWER,
                    _RAISE,
                    _ADJUST
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

/* These definitions can be removed once keymap_swe is properly vetted against MacOS */
#define SE_DLR_MAC_V  ALGR(LALT(KC_4))
#define SE_AT_MAC_V   ALGR(LALT(KC_2))

/* Esc when pressed, ctrl when used as a modifier */
#define KC_ECTL MT(MOD_LCTL, KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Colemak_se
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   Ö  |  Å   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | ECTR |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  Ä   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | SCSHE|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   -  |SCSHE |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | esc  | CTRL | Alt  | CMD  |Lower |Space |Bksp  |Raise | CMD  | RALT | HYPER| MEH  |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_planck_grid
(
 KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    SE_ODIA, SE_ARNG,
 KC_ECTL,   KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    SE_ADIA,
 KC_SFTENT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  SE_MINS, KC_SFTENT,
 KC_ESC,    KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_BSPC, RAISE,   KC_RGUI, KC_RALT, KC_HYPR, KC_MEH
 ),

/* Lower
* ,-----------------------------------------------------------------------------------.
* |      | PIPE |   '  |   @  |   &  |      | DOWN |      | RIGHT|   `  |   ´  |  ~   |
* |------+------+------+------+------+-------------+------+------+------+------+------|
* |      |   !  |   "  |   #  |   ?  |   %  | LEFT |   /  |   \  |   =  |   +  |  *   |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |      |      |      |   [  |   ]  |      | UP   |   {  |   }  |      |      |      |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* |      |      |      |      |      |      | DEL  |      | Next | Vol- | Vol+ | Play |
* `-----------------------------------------------------------------------------------'
*/
[_LOWER] = LAYOUT_planck_grid
(
 _______, SE_LCBR,     SE_QUOT, SE_AT_MAC_V, SE_AMPR,     _______, KC_DOWN, KC_NO,       KC_RGHT,     SE_GRV,  SE_GRV,  SE_TILD,
 _______, KC_EXLM,     SE_DQUO, KC_HASH,     SE_QUES,     KC_PERC, KC_LEFT, SE_SLSH,     S(SE_LCBR),  SE_EQL,  KC_PPLS, KC_PAST,
 _______, KC_NO,       KC_NO,   SE_LBRC,     SE_RBRC,     KC_NO,   KC_UP,   S(SE_LBRC),  S(SE_RBRC),  KC_NO,   KC_NO,   _______,
 _______, _______,     _______, _______,     _______,     _______, KC_DEL,  _______,     KC_MNXT,     KC_VOLD, KC_VOLU, KC_MPLY
 ),

/* Raise
* ,-----------------------------------------------------------------------------------.
* |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 | F11  | F12  |
* |------+------+------+------+------+-------------+------+------+------+------+------|
* |   ^  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  $   |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |      |      |      |   <  |   >  |      |      |  (   |   )  |Pg Up |Pg Dn |      |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
* `-----------------------------------------------------------------------------------'
*/
[_RAISE] = LAYOUT_planck_grid
(
 KC_F1,   KC_F2,   KC_F3,   KC_F4,       KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,       KC_F10,  KC_F11,  KC_F12,
 SE_CIRC, KC_1,    KC_2,    KC_3,        KC_4,    KC_5,    KC_6,    KC_7,    KC_8,        KC_9,    KC_0,    SE_DLR_MAC_V,
 _______, KC_NO,   KC_NO,   SE_SECT,     SE_HALF, KC_NO,   KC_NO,   SE_LPRN, SE_RPRN,     KC_PGUP, KC_PGDN, KC_NO,
 _______, _______, _______, _______,     _______, _______, _______, _______, KC_MNXT,     KC_VOLD, KC_VOLU, KC_MPLY
 ),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset| Debug|      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid
(
 _______, QK_BOOT, DEBUG,   _______, _______, _______, _______, _______, _______,  _______, _______, _______,
 _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______,
 _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______,
 _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
 )

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
