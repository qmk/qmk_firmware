
/* Copyright 2019 Torben Hoffmann
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
#pragma once

#include "keymap.h"
// For software implementation of norman
#define NM_Q    KC_Q
#define NM_W    KC_W
#define NM_D    KC_E
#define NM_F    KC_R
#define NM_K    KC_T
#define NM_J    KC_Y
#define NM_U    KC_U
#define NM_R    KC_I
#define NM_L    KC_O
#define NM_SCLN KC_P
#define NM_COLN LSFT(NM_SCLN)

#define NM_A    KC_A
#define NM_S    KC_S
#define NM_E    KC_D
#define NM_T    KC_F
#define NM_G    KC_G
#define NM_Y    KC_H
#define NM_N    KC_J
#define NM_I    KC_K
#define NM_O    KC_L
#define NM_H    KC_SCLN

#define NM_Z    KC_Z
#define NM_X    KC_X
#define NM_C    KC_C
#define NM_V    KC_V
#define NM_B    KC_B
#define NM_P    KC_N
#define NM_M    KC_M
#define NM_COMM KC_COMM
#define NM_DOT  KC_DOT
#define NM_SLSH KC_SLSH

// Make it easy to support these in macros
// TODO: change macro implementation so these aren't needed
#define KC_NM_Q    NM_Q
#define KC_NM_W    NM_W
#define KC_NM_F    NM_F
#define KC_NM_P    NM_P
#define KC_NM_G    NM_G
#define KC_NM_J    NM_J
#define KC_NM_L    NM_L
#define KC_NM_U    NM_U
#define KC_NM_Y    NM_Y
#define KC_NM_SCLN NM_SCLN

#define KC_NM_A    NM_A
#define KC_NM_R    NM_R
#define KC_NM_S    NM_S
#define KC_NM_T    NM_T
#define KC_NM_D    NM_D
#define KC_NM_H    NM_H
#define KC_NM_N    NM_N
#define KC_NM_E    NM_E
#define KC_NM_I    NM_I
#define KC_NM_O    NM_O

#define KC_NM_Z    NM_Z
#define KC_NM_X    NM_X
#define KC_NM_C    NM_C
#define KC_NM_V    NM_V
#define KC_NM_B    NM_B
#define KC_NM_K    NM_K
#define KC_NM_M    NM_M
#define KC_NM_COMM NM_COMM
#define KC_NM_DOT  NM_DOT
#define KC_NM_SLSH NM_SLSH

