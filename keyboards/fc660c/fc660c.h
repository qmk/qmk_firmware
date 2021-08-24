/*
Copyright 2017 Balz Guenat

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
#ifndef FC660C_H
#define FC660C_H

#include "quantum.h"


#define LAYOUT( \
    K13, K10, K11, K12, K14, K16, K17, K15, K1B, K18, K19, K1A, K1C, K1E,      K1F, \
    K03, K00, K01, K02, K04, K06, K07, K05, K0B, K08, K09, K0A, K0C, K0E,      K0F, \
    K43, K40, K41, K42, K44, K46, K47, K45, K4B, K48, K49, K4A,      K4E,           \
    K33, K31, K32, K34, K36, K37, K35, K3B, K38, K39, K3A,           K3C, K3D,      \
    K23, K21, K22,                K27,                K28, K2A, K2C, K2E, K2D, K2F  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07,   \
      K08, K09, K0A, K0B, K0C, KC_NO,    K0E, K0F }, \
    { K10, K11, K12, K13, K14, K15, K16, K17,   \
      K18, K19, K1A, K1B, K1C, KC_NO,    K1E, K1F }, \
    { KC_NO,    K21, K22, K23, KC_NO,    KC_NO,    KC_NO,    K27,   \
      K28, KC_NO,    K2A, KC_NO,    K2C, K2D, K2E, K2F }, \
    { KC_NO,    K31, K32, K33, K34, K35, K36, K37,   \
      K38, K39, K3A, K3B, K3C, K3D, KC_NO,    KC_NO    }, \
    { K40, K41, K42, K43, K44, K45, K46, K47,   \
      K48, K49, K4A, K4B, KC_NO,    KC_NO,    K4E, KC_NO    }  \
}
/*
KEYMAP(
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,     _______,
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,     _______,
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,     _______,
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,     _______,
        _______,_______,_______,                _______,                _______,_______,_______,     _______,_______,_______
    )
*/

#endif
