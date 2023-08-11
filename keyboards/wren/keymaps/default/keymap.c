/* Copyright 2021 Walter Hanley
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
enum layer_names {
    _BASE
};

/* This layout preserves the entire keyboard matrix, but only includes keycodes
 * for a numpad/nav cluster configuration. Depending on your configuration, you
 * may need to replace some of the existing KC_NO values with actual keycodes.
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
     KC_PSLS, KC_7,    KC_8,    KC_9,    KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,  KC_INS,  KC_HOME, KC_PGUP, KC_NO,
     KC_PAST, KC_4,    KC_5,    KC_6,    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, KC_DEL,  KC_END,  KC_PGDN, KC_NO,
     KC_PMNS, KC_1,    KC_2,    KC_3,    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NO,   KC_UP,   KC_NO,   KC_NO,
     KC_PPLS, KC_0,    KC_DOT,  KC_ENT,  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,
                                                           KC_NUM,  KC_LALT, KC_LGUI, KC_BSPC, KC_ENT,  KC_SPC,  KC_DEL,  KC_RGUI, KC_RALT, KC_MUTE
    )
};
