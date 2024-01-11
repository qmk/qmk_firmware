/* Copyright 2024 @ Grabshell (https://grabshell.site/)

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
#pragma once

#include "quantum.h"

#define LAYOUT(\
 K000,  K001,    K002,    K003,    K004,    K005,             K007,    K008,    K009,           K011,    K012,    K013,             K015,    K016,    K017,    K018,    K019,    K020,\
 K100,  K101,    K102,    K103,    K104,    K105,    K106,    K107,    K108,    K109,           K111,    K112,    K113,    K114,    K115,    K116,    K117,    K118,    K119,    K120, \
        K201,    K202,    K203,    K204,    K205,             K207,    K208,    K209,           K211,    K212,    K213,             K215,    K216,    K217,    K218,    K219,\
        K301,    K302,    K303,    K304,    K305,             K307,    K308,    K309,                             K313,             K315,    K316,    K317,    K318,    K319,\
                                                              K407,                                               K413,\
                                                              K507,    K508,    K509,    K510,  K511,    K512,    K513 \
){\
{K000,  K001,    K002,    K003,    K004,    K005,     KC_NO,  K007,    K008,     K009,   KC_NO,  K011,    K012,   K013,    KC_NO,   K015,    K016,     K017,    K018,    K019,   K020,  KC_NO},\
{K100,  K101,    K102,    K103,    K104,    K105,     K106,   K107,    K108,     K109,   KC_NO,  K111,    K112,   K113,    K114,    K115,    K116,     K117,    K118,    K119,   K120,  KC_NO},\
{KC_NO, K201,    K202,    K203,    K204,    K205,     KC_NO,  K207,    K208,     K209,   KC_NO,  K211,    K212,   K213,    KC_NO,   K215,    K216,     K217,    K218,    K219,   KC_NO, KC_NO},\
{KC_NO, K301,    K302,    K303,    K304,    K305,     KC_NO,  K307,    K308,     K309,   KC_NO,  KC_NO,   KC_NO,  K313,    KC_NO,   K315,    K316,     K317,    K318,    K319,   KC_NO, KC_NO},\
{KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,  K407,    KC_NO,    KC_NO,  KC_NO,  KC_NO,   KC_NO,  K413,    KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_NO,  KC_NO, KC_NO},\
{KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,  K507,    K508,     K509,   K510,   K511,    K512,   K513,    KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_NO,  KC_NO, KC_NO}\
}
