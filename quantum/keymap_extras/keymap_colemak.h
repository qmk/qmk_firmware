/* Copyright 2015-2016 Jack Humbert
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
#ifndef KEYMAP_COLEMAK_H
#define KEYMAP_COLEMAK_H

#include "keymap.h"
// For software implementation of colemak
#define CM_Q KC_Q
#define CM_W KC_W
#define CM_F KC_E
#define CM_P KC_R
#define CM_G KC_T
#define CM_J KC_Y
#define CM_L KC_U
#define CM_U KC_I
#define CM_Y KC_O
#define CM_SCLN KC_P

#define CM_A KC_A
#define CM_R KC_S
#define CM_S KC_D
#define CM_T KC_F
#define CM_D KC_G
#define CM_H KC_H
#define CM_N KC_J
#define CM_E KC_K
#define CM_I KC_L
#define CM_O KC_SCLN
#define CM_COLN LSFT(CM_SCLN)

#define CM_Z KC_Z
#define CM_X KC_X
#define CM_C KC_C
#define CM_V KC_V
#define CM_B KC_B
#define CM_K KC_N
#define CM_M KC_M
#define CM_COMM KC_COMM
#define CM_DOT KC_DOT
#define CM_SLSH KC_SLSH

// Make it easy to support these in macros
// TODO: change macro implementation so these aren't needed
#define KC_CM_Q CM_Q
#define KC_CM_W CM_W
#define KC_CM_F CM_F
#define KC_CM_P CM_P
#define KC_CM_G CM_G
#define KC_CM_J CM_J
#define KC_CM_L CM_L
#define KC_CM_U CM_U
#define KC_CM_Y CM_Y
#define KC_CM_SCLN CM_SCLN

#define KC_CM_A CM_A
#define KC_CM_R CM_R
#define KC_CM_S CM_S
#define KC_CM_T CM_T
#define KC_CM_D CM_D
#define KC_CM_H CM_H
#define KC_CM_N CM_N
#define KC_CM_E CM_E
#define KC_CM_I CM_I
#define KC_CM_O CM_O

#define KC_CM_Z CM_Z
#define KC_CM_X CM_X
#define KC_CM_C CM_C
#define KC_CM_V CM_V
#define KC_CM_B CM_B
#define KC_CM_K CM_K
#define KC_CM_M CM_M
#define KC_CM_COMM CM_COMM
#define KC_CM_DOT CM_DOT
#define KC_CM_SLSH CM_SLSH

#endif
