/* Copyright 2017 REPLACE_WITH_YOUR_NAME
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
#ifndef MT40_H
#define MT40_H

#include "quantum.h"


// This a shortcut to help you visually see your layout.
// The following is an example using the Planck MIT layout
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array
#define LAYOUT_planck_mit( \
    K00,  K01,  K02,  K03,  K04,  K05,  K06,  K07,  K08,  K09,  K0A,  K0B, \
    K10,  K11,  K12,  K13,  K14,  K15,  K16,  K17,  K18,  K19,  K1A,  K1B, \
    K20,  K21,  K22,  K23,  K24,  K25,  K26,  K27,  K28,  K29,  K2A,  K2B, \
    K30,  K31,  K32,  K33,  K34,     K35,     K37,  K38,  K39,  K3A,  K3B \
) { \
    { K31,   K32,   K33,   KC_NO, K34,   K35,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K37,   KC_NO, KC_NO, KC_NO }, \
    { K20,   K21,   K22,   K23,   K24,   K25,   KC_NO, KC_NO, KC_NO, KC_NO, K2A,   KC_NO, KC_NO, KC_NO, KC_NO }, \
    { K30,   K11,   K12,   K13,   K14,   K15,   KC_NO, KC_NO, KC_NO, KC_NO, K1A,   K1B,   KC_NO, KC_NO, KC_NO }, \
    { K10,   K01,   K02,   K03,   K04,   K05,   KC_NO, KC_NO, KC_NO, KC_NO, K0A,   KC_NO, KC_NO, KC_NO, KC_NO }, \
    { K00,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K0B   }, \
    { KC_NO, KC_NO, K06,   K16,   K26,   K35,   K38,   K3A,   K39,   K3B,   KC_NO, KC_NO, K07,   K17,   K27   }, \
    { KC_NO, KC_NO, K09,   K19,   K29,   KC_NO, K2B,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K08,   K18,   K28   }  \
}

#define LAYOUT LAYOUT_planck_mit

#endif
