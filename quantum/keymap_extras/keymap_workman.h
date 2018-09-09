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
#ifndef KEYMAP_WORKMAN_H
#define KEYMAP_WORKMAN_H

#include "keymap.h"
// For software implementation of workman
#define WK_Q    KC_Q
#define WK_D    KC_W
#define WK_R    KC_E
#define WK_W    KC_R
#define WK_B    KC_T
#define WK_J    KC_Y
#define WK_F    KC_U
#define WK_U    KC_I
#define WK_P    KC_O
#define WK_SCLN KC_P

#define WK_A    KC_A
#define WK_S    KC_S
#define WK_H    KC_D
#define WK_T    KC_F
#define WK_G    KC_G
#define WK_Y    KC_H
#define WK_N    KC_J
#define WK_E    KC_K
#define WK_O    KC_L
#define WK_I    KC_SCLN

#define WK_Z    KC_Z
#define WK_X    KC_X
#define WK_M    KC_C
#define WK_C    KC_V
#define WK_V    KC_B
#define WK_K    KC_N
#define WK_L    KC_M

// Make it easy to support these in macros
// TODO: change macro implementation so these aren't needed
#define KC_WK_Q    WK_Q
#define KC_WK_D    WK_D
#define KC_WK_R    WK_R
#define KC_WK_W    WK_W
#define KC_WK_B    WK_B
#define KC_WK_J    WK_J
#define KC_WK_F    WK_F
#define KC_WK_U    WK_U
#define KC_WK_P    WK_P
#define KC_WK_SCLN WK_SCLN

#define KC_WK_A    WK_A
#define KC_WK_S    WK_S
#define KC_WK_H    WK_H
#define KC_WK_T    WK_T
#define KC_WK_G    WK_G
#define KC_WK_Y    WK_Y
#define KC_WK_N    WK_N
#define KC_WK_E    WK_E
#define KC_WK_O    WK_O
#define KC_WK_I    WK_I

#define KC_WK_Z    WK_Z
#define KC_WK_X    WK_X
#define KC_WK_M    WK_M
#define KC_WK_C    WK_C
#define KC_WK_V    WK_V
#define KC_WK_K    WK_K
#define KC_WK_L    WK_L

#endif
