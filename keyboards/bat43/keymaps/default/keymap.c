/* Copyright 2020 yfuku
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
    _BASE,
    _LOWER,
    _RAISE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_BSPC,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,    KC_RSFT,
KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    KC_COMM,    KC_DOT,    KC_SLSH,    KC_RCTL,
            KC_LGUI,    KC_EN,    KC_L_SPC,        KC_R_ENT,    KC_JA,    KC_RALT,            
                KC_A,    KC_B,        KC_C,    KC_D,    KC_E,            
    ),
    [_LOWER] = LAYOUT(
KC_TRNS,    KC_BSLS,    KC_EXLM,    KC_AMPR,    KC_PIPE,    KC_NO,        KC_NO,    KC_EQL,    KC_PLUS,    KC_ASTR,    KC_PERC,    KC_TRNS,
KC_TRNS,    KC_HASH,    KC_GRV,    KC_DQT,    KC_QUOT,    KC_TILD,    KC_TRNS,    KC_LEFT,    KC_DOWN,    KC_UP,    KC_RGHT,    KC_DLR,    KC_TRNS,
KC_TRNS,    KC_NO,    KC_NO,    KC_LCBR,    KC_LBRC,    KC_LPRN,        KC_RPRN,    KC_RBRC,    KC_RCBR,    KC_AT,    KC_CIRC,    KC_TRNS,
            KC_TRNS,    KC_TRNS,    KC_BSPC,        KC_NO,    KC_TRNS,    KC_TRNS,            
                KC_TRNS,    KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,            
    ),
    [_RAISE] = LAYOUT(
KC_TRNS,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,        KC_NO,    KC_EQL,    KC_PLUS,    KC_ASTR,    KC_PERC,    KC_TRNS,
KC_TRNS,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_TRNS,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_TRNS,
KC_TRNS,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,        KC_NO,    KC_NO,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
            KC_TRNS,    KC_TRNS,    KC_NO,        KC_DEL,    KC_TRNS,    KC_TRNS,            
                KC_TRNS,    KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,            
    ),
};



