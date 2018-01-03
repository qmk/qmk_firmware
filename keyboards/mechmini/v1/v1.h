/*
Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef V1_H
#define V2_H

#include "../mechmini.h"
#include "keycode.h"
#include "action.h"
#include "quantum.h"

#define KEYMAP( \
    K03, K13, K23, K33, K43, K53, K26, KC6, KC7, K27, KA3, KB3, \
    K02, K12, K22, K32, K42, K52, K36, KD6, KD7, K37, KA2, \
    K01, K11, K21, K31, K41, K51, K46, KE6, KE7, K47, KA1, \
    K00, K10, K20,      K56, K57, KB0,           KC0, K66  \
) \
{ \
    { K00, K10, K20, K56, KC_NO,    K57,    KC_NO, KC_NO,    KB0, KC0, K66, KC_NO,    KC_NO,    KC_NO,    KC_NO }, \
    { K01, K11, K21, K31, K41, K51, K46, KE6, KE7, K47, KA1, KC_NO,    KC_NO,    KC_NO,    KC_NO }, \
    { K02, K12, K22, K32, K42, K52, K36, KD6, KD7, K37, KA2, KC_NO,    KC_NO,    KC_NO,    KC_NO }, \
    { K03, K13, K23, K33, K43, K53, K26, KC6, KC7, K27, KA3, KB3, KC_NO,    KC_NO,    KC_NO }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO } \
}

#endif
