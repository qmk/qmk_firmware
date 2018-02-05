/* Copyright 2016 Jack Humbert
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
/* Sendstring definitions for the Colemak layout */
#ifndef SENDSTRING_COLEMAK
#define SENDSTRING_COLEMAK

#include "keymap_colemak.h"

const uint8_t ascii_to_keycode_lut[0x80] PROGMEM = {
    0, 0, 0, 0, 0, 0, 0, 0,
    KC_BSPC, KC_TAB, KC_ENT, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, KC_ESC, 0, 0, 0, 0,
    KC_SPC, KC_1, KC_QUOT, KC_3, KC_4, KC_5, KC_7, KC_QUOT,
    KC_9, KC_0, KC_8, KC_EQL, KC_COMM, KC_MINS, KC_DOT, KC_SLSH,
    KC_0, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7,
    KC_8, KC_9, CM_SCLN, CM_SCLN, KC_COMM, KC_EQL, KC_DOT, KC_SLSH,
    KC_2, CM_A, CM_B, CM_C, CM_D, CM_E, CM_F, CM_G,
    CM_H, CM_I, CM_J, CM_K, CM_L, CM_M, CM_N, CM_O,
    CM_P, CM_Q, CM_R, CM_S, CM_T, CM_U, CM_V, CM_W,
    CM_X, CM_Y, CM_Z, KC_LBRC, KC_BSLS, KC_RBRC, KC_6, KC_MINS,
    KC_GRV, CM_A, CM_B, CM_C, CM_D, CM_E, CM_F, CM_G,
    CM_H, CM_I, CM_J, CM_K, CM_L, CM_M, CM_N, CM_O,
    CM_P, CM_Q, CM_R, CM_S, CM_T, CM_U, CM_V, CM_W,
    CM_X, CM_Y, CM_Z, KC_LBRC, KC_BSLS, KC_RBRC, KC_GRV, KC_DEL
};

#endif
