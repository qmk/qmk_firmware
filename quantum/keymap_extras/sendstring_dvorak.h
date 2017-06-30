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
/* Sendstring definitions for the Dvorak layout */
#ifndef SENDSTRING_DVORAK
#define SENDSTRING_DVORAK

#include "keymap_dvorak.h"

const uint8_t ascii_to_keycode_lut[0x80] PROGMEM = {
    0, 0, 0, 0, 0, 0, 0, 0,
    KC_BSPC, KC_TAB, KC_ENT, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, KC_ESC, 0, 0, 0, 0,
    KC_SPC, DV_1, DV_QUOT, DV_3, DV_4, DV_5, DV_7, DV_QUOT,
    DV_9, DV_0, DV_8, DV_EQL, DV_COMM, DV_MINS, DV_DOT, DV_SLSH,
    DV_0, DV_1, DV_2, DV_3, DV_4, DV_5, DV_6, DV_7,
    DV_8, DV_9, DV_SCLN, DV_SCLN, DV_COMM, DV_EQL, DV_DOT, DV_SLSH,
    DV_2, DV_A, DV_B, DV_C, DV_D, DV_E, DV_F, DV_G,
    DV_H, DV_I, DV_J, DV_K, DV_L, DV_M, DV_N, DV_O,
    DV_P, DV_Q, DV_R, DV_S, DV_T, DV_U, DV_V, DV_W,
    DV_X, DV_Y, DV_Z, DV_LBRC, DV_BSLS, DV_RBRC, DV_6, DV_MINS,
    DV_GRV, DV_A, DV_B, DV_C, DV_D, DV_E, DV_F, DV_G,
    DV_H, DV_I, DV_J, DV_K, DV_L, DV_M, DV_N, DV_O,
    DV_P, DV_Q, DV_R, DV_S, DV_T, DV_U, DV_V, DV_W,
    DV_X, DV_Y, DV_Z, DV_LBRC, DV_BSLS, DV_RBRC, DV_GRV, KC_DEL
};

#endif
