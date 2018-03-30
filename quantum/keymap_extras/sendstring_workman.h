/* Copyright 2018 Jacob Jerrell
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
/* Sendstring definitions for the Workman layout */
#ifndef SENDSTRING_WORKMAN
#define SENDSTRING_WORKMAN

#include "keymap_workman.h"

const uint8_t ascii_to_keycode_lut[0x80] PROGMEM = {
    0,       0,      0,       0,       0,       0,       0,      0,
    KC_BSPC, KC_TAB, KC_ENT,  0,       0,       0,       0,      0,
    0,       0,      0,       0,       0,       0,       0,      0,
    0,       0,      0,       KC_ESC,  0,       0,       0,      0,
    KC_SPC,  KC_1,   KC_QUOT, KC_3,    KC_4,    KC_5,    KC_7,   KC_QUOT,
    KC_9,    KC_0,   KC_8,    KC_EQL,  KC_COMM, KC_MINS, KC_DOT, KC_SLSH,
    KC_0,    KC_1,   KC_2,    KC_3,    KC_4,    KC_5,    KC_6,   KC_7,
    KC_8,    KC_9,   KC_SCLN, KC_SCLN, KC_COMM, KC_EQL,  KC_DOT, KC_SLSH,
    KC_2,    WK_A,   WK_B,    WK_C,    WK_D,    WK_E,    WK_F,   WK_G,
    WK_H,    WK_I,   WK_J,    WK_K,    WK_L,    WK_M,    WK_N,   WK_O,
    WK_P,    WK_Q,   WK_R,    WK_S,    WK_T,    WK_U,    WK_V,   WK_W,
    WK_X,    WK_Y,   WK_Z,    KC_LBRC, KC_BSLS, KC_RBRC, KC_6,   KC_MINS,
    KC_GRV,  WK_A,   WK_B,    WK_C,    WK_D,    WK_E,    WK_F,   WK_G,
    WK_H,    WK_I,   WK_J,    WK_K,    WK_L,    WK_M,    WK_N,   WK_O,
    WK_P,    WK_Q,   WK_R,    WK_S,    WK_T,    WK_U,    WK_V,   WK_W,
    WK_X,    WK_Y,   WK_Z,    KC_LBRC, KC_BSLS, KC_RBRC, KC_GRV, KC_DEL
};

#endif