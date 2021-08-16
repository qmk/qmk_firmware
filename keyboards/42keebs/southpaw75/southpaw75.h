 /* 
 Copyright 2020 Kelvin Hall 
  
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

#define LAYOUT( \
    K00, K01, K02, K03,   K04,      K05, K06, K07, K08, K10, K11, K12, K13, K14, K15, K16, K17, K18, \
    K20, K21, K22, K23,   K24,      K25, K26, K27, K28, K30, K31, K32, K33, K34, K35, K36, K37, K38, \
    K40, K41, K42,        K43,      K44, K45, K46, K47, K48, K50, K51, K52, K53, K54, K55,      K56, \
    K57, K58, K60, K61,   K62,      K64, K65, K66, K67, K68, K70, K71, K72, K73, K74, K75,      K87, \
    K76,      K77,        K78, K80, K81,                K82,                K83, K84, K85, K86       \
) { \
	{ K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08 }, \
	{ K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18 }, \
	{ K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28 }, \
	{ K30,   K31,   K32,   K33,   K34,   K35,   K36,   K37,   K38 }, \
	{ K40,   K41,   K42,   K43,   K44,   K45,   K46,   K47,   K48 }, \
	{ K50,   K51,   K52,   K53,   K54,   K55,   K56,   K57,   K58 }, \
	{ K60,   K61,   K62,   KC_NO, K64,   K65,   K66,   K67,   K68 }, \
	{ K70,   K71,   K72,   K73,   K74,   K75,   K76,   K77,   K78 }, \
	{ K80,   K81,   K82,   K83,   K84,   K85,   K86,   K87,   KC_NO } \
}

// KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,    KC_ESC,           KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
// KC_P7,   KC_P8,   KC_P9,   KC_PPLS,    KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
// KC_P4,   KC_P5,   KC_P6,               KC_CAPS,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
// KC_P1,   KC_P2,   KC_P3,   KC_PENT,    KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          MO(1),
// KC_P0,            KC_PDOT,             KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_LALT, KC_LGUI, KC_MENU, KC_LCTL


#define LAYOUT_ISO( \
    K00, K01, K02, K03,   K04,      K05, K06, K07, K08, K10, K11, K12, K13, K14, K15, K16, K17, K18, \
    K20, K21, K22, K23,   K24,      K25, K26, K27, K28, K30, K31, K32, K33, K34, K35, K36, K37, K38, \
    K40, K41, K42,        K43,      K44, K45, K46, K47, K48, K50, K51, K52, K53, K54, K55, K56,      \
    K57, K58, K60, K61,   K62, K63, K64, K65, K66, K67, K68, K70, K71, K72, K73, K74, K75,      K87, \
    K76,      K77,        K78, K80, K81,                K82,                K83, K84, K85, K86       \
) { \
	{ K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08 }, \
	{ K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18 }, \
	{ K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28 }, \
	{ K30,   K31,   K32,   K33,   K34,   K35,   K36,   K37,   K38 }, \
	{ K40,   K41,   K42,   K43,   K44,   K45,   K46,   K47,   K48 }, \
	{ K50,   K51,   K52,   K53,   K54,   K55,   K56,   K57,   K58 }, \
	{ K60,   K61,   K62,   K63,   K64,   K65,   K66,   K67,   K68 }, \
	{ K70,   K71,   K72,   K73,   K74,   K75,   K76,   K77,   K78 }, \
	{ K80,   K81,   K82,   K83,   K84,   K85,   K86,   K87,   KC_NO } \
}

// KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,    KC_ESC,           KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
// KC_P7,   KC_P8,   KC_P9,   KC_PPLS,    KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_ENT,
// KC_P4,   KC_P5,   KC_P6,               KC_CAPS,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSLS,
// KC_P1,   KC_P2,   KC_P3,   KC_PENT,    KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          MO(1),
// KC_P0,            KC_PDOT,             KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, KC_RGUI, KC_MENU, KC_RCTL
