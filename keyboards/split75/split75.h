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

#pragma once

#include "quantum.h"

#define KEYMAP( \
            K05, K15, K25, K35, K45, K55, K65, K75, K85, K95, K105, K115, K125, K135, K86, K87, \
  K47, K46, K04, K14, K24, K34, K44, K54, K64, K74, K84, K94, K104, K114, K124,       K96, K97, \
  K37, K36, K03, K13, K23, K33, K43, K53,      K73, K83, K93, K103, K113, K123, K133, K106, K107, \
  K27, K26, K02, K12, K22, K32, K42, K52,      K72, K82, K92, K102, K112, K122,       K116, K117, \
  K17, K16, K01,      K21, K31, K41, K51, K61, K71, K81, K91, K101, K111,       K131, K126, K127, \
  K07, K06, K00, K10, K20, K30, K40,           K70,           K100, K110, K120, K130, K136, K137  \
){ \
  { K00,    K10,    K20,    K30,    K40,    KC_NO,  KC_NO,  K70,    KC_NO,  KC_NO,  K100,   K110,   K120,   K130 }, \
  { K01,    KC_NO,  K21,    K31,    K41,    K51,    K61,    K71,    K81,    K91,    K101,   K111,   KC_NO,  K131 }, \
  { K02,    K12,    K22,    K32,    K42,    K52,    KC_NO,  K72,    K82,    K92,    K102,   K112,   K122,        }, \
  { K03,    K13,    K23,    K33,    K43,    K53,    KC_NO,  K73,    K83,    K93,    K103,   K113,   K123,   K133 }, \
  { K04,    K14,    K24,    K34,    K44,    K54,    K64,    K74,    K84,    K94,    K104,   K114,   K124,        }, \
  { K05,    K15,    K25,    K35,    K45,    K55,    K65,    K75,    K85,    K95,    K105,   K115,   K125,   K135 }, \
  { K06,    K16,    K26,    K36,    K46,    KC_NO,  KC_NO,  KC_NO,  K86,    K96,    K106,   K116,   K126,   K136 }, \
  { K07,    K17,    K27,    K37,    K47,    KC_NO,  KC_NO,  KC_NO,  K87,    K97,    K107,   K117,   K127,   K137 }  \
}

#define NUMLOCK led0
#define CAPSLOCK led1
#define SCROLLOCK led2

void indicator_init(void);
