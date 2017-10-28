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

#ifndef KEYMAP_COMMON_H
#define KEYMAP_COMMON_H

#include "keycode.h"
#include "action.h"

#define KEYMAP( \
    K03, K13, K23, K33, K43, K53, K26, KC6, KC7, K27, KA3, KB3, \
    K02, K12, K22, K32, K42, K52, K36, KD6, KD7, K37, KA2, \
    K01, K11, K21, K31, K41, K51, K46, KE6, KE7, K47, KA1, \
    K00, K10, K20,      K56,      K57,      KB0, KC0, K66  \
) \
{ \
    { KC_##K00, KC_##K10, KC_##K20, KC_##K56, KC_NO,    KC_NO,    KC_##K57, KC_NO,    KC_##KB0, KC_##KC0, KC_##K66, KC_NO,    KC_NO,    KC_NO,    KC_NO }, \
    { KC_##K01, KC_##K11, KC_##K21, KC_##K31, KC_##K41, KC_##K51, KC_##K46, KC_##KE6, KC_##KE7, KC_##K47, KC_##KA1, KC_NO,    KC_NO,    KC_NO,    KC_NO }, \
    { KC_##K02, KC_##K12, KC_##K22, KC_##K32, KC_##K42, KC_##K52, KC_##K36, KC_##KD6, KC_##KD7, KC_##K37, KC_##KA2, KC_NO,    KC_NO,    KC_NO,    KC_NO }, \
    { KC_##K03, KC_##K13, KC_##K23, KC_##K33, KC_##K43, KC_##K53, KC_##K26, KC_##KC6, KC_##KC7, KC_##K27, KC_##KA3, KC_##KB3, KC_NO,    KC_NO,    KC_NO }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO } \
}

#endif
