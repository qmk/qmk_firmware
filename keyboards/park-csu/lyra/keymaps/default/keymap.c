/* Copyright 2021 Changsu Park
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

// Defines names for use in layer keycodes and the keymap
enum layer {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJUST MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base
     * ,------------------------------------------  ------------------------------------------.
     * | Tab  |   Q  |   W  |   E  |   R  |   T  |  |   Y  |   U  |   I  |   O  |   P  | Bksp |
     * |------+------+------+------+------+------|  |------+------+------+------+------+------|
     * | Ctrl |   A  |   S  |   D  |   F  |   G  |  |   H  |   J  |   K  |   L  |   ;  |  "   |
     * |------+------+------+------+------+------|  |------+------+------+------+------+------|
     * | Shift|   Z  |   X  |   C  |   V  |   B  |  |   N  |   M  |   ,  |   .  |   /  |Enter |
     * |------+------+------+------+------+------|  |------+------+------+------+------+------|
     * | Caps | ESC  | GUI  | Alt  |Lower | Space|  |Space |Raise | Left | Down |  Up  |Right |
     * `------------------------------------------  ------------------------------------------'
     */
    [_BASE] = LAYOUT(
       KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
       KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
       KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                     KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT , \
       KC_CAPS,  KC_ESC,  KC_LGUI, KC_LALT, LOWER,   KC_SPC, KC_MUTE, KC_MPLY, KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
    ),

    /* Lower
     * ,------------------------------------------  ------------------------------------------.
     * |   ~  |   !  |   @  |   #  |   $  |   %  |  |   ^  |   &  |   *  |   (  |   )  | Del  |
     * |------+------+------+------+------+------|  |------+------+------+------+------+------|
     * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  |  F6  |   -  |   +  |   {  |   }  |  |   |
     * |------+------+------+------+------+------|  |------+------+------+------+------+------|
     * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  |  F12 |      |      |      |      |      |
     * |------+------+------+------+------+------|  |------+------+------+------+------+------|
     * |      |      |      |      |      |      |  |      |      |      |      |      |      |
     * `------------------------------------------  ------------------------------------------'
     */
    [_LOWER] = LAYOUT( \
      KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL, \
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
      _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,                    KC_F12,  _______, _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
    ),

    /* Raise
     * ,------------------------------------------  ------------------------------------------.
     * |   `  |   1  |   2  |   3  |   4  |   5  |  |   6  |   7  |   8  |   9  |   0  | Del  |
     * |------+------+------+------+------+------|  |------+------+------+------+------+------|
     * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  |  F6  |   _  |   =  |   [  |   ]  |  \   |
     * |------+------+------+------+------+------|  |------+------+------+------+------+------|
     * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  |  F12 |      |      |      |      |      |
     * |------+------+------+------+------+------|  |------+------+------+------+------+------|
     * |      |      |      |      |      |      |  |      |      |      |      |      |      |
     * `------------------------------------------  ------------------------------------------'
     */
    [_RAISE] = LAYOUT( \
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, \
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_UNDS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
      _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,                    KC_F12,  _______, _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
    ),

    /* Adjust (Lower + Raise)
     * ,------------------------------------------  ------------------------------------------.
     * |      | Reset|      |      |      |      |  |      |      |      |      |      |  Del |
     * |------+------+------+------+------+------|  |------+------+------+------+------+------|
     * |      |      |      |      |      |      |  |      |      |      |      |      |      |
     * |------+------+------+------+------+------|  |------+------+------+------+------+------|
     * |      |      |      |      |      |      |  |      |      |      |      |      |      |
     * |------+------+------+------+------+------|  |------+------+------+------+------+------|
     * |      |      |      |      |      |      |  |      |      |      |      |      |      |
     * `------------------------------------------  ------------------------------------------'
     */
    [_ADJUST] = LAYOUT( \
      _______, RESET,   _______, _______, _______, _______,                   _______, _______, _______, _______, _______, KC_DEL, \
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
    )
};

layer_state_t layer_state_set_user(layer_state_t state) { return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST); }
