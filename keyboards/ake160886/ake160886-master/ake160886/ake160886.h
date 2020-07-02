/* Copyright 2020 Hugh Mungis
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

#include "quantum.h"

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
// in my_keyboard_name.h 
// Key numbers correspond to AKE160886/5 pcb silkscreen (https://i.imgur.com/TugBf0N.jpg)
#define LAYOUT( \
K1,         K2,   K3,   K4,   K5,   K6,   K7,   K8,   K9,   K10,  K11,  K12,  K13,  K14,  K15,  K16,  K17,  K18,  K19,  K20,  K21,  K22,  K23,  K24,\
K25,  K26,  K27,  K28,  K29,  K30,  K31,  K32,  K33,  K34,  K35,  K36,  K37,  K38,  K39,  K40,  K41,  K42,  K43,  K44,  K45,  K46,  K47,  K48,  K49,\
K50,  K51,  K52,  K53,  K54,  K55,        K56,        K57,        K58,  K59,  K60,  K61,  K62,        K63,  K64,  K65,        K66,  K67,  K68,  K69,\
K70,  K71,  K72,  K73,  K74,  K75,  K76,  K77,  K78,  K79,  K80,  K81,  K82,  K83,  K84,  K85,  K86,  K87,  K88,  K89,  K90,  K91,  K92,  K93,  K94,\
K95,  K96,  K97,  K98,  K99,  K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, K115, K116, K117, K118, K119,\
K120, K121, K122, K123, K124, K125, K126, K127, K128, K129, K130, K131, K132, K133, K134, K135, K136, K137, K138, K139, K140, K141, K142, K143, K144,\
K145,       K146, K147, K148, K149,       K150,             K151,             K152,       K153, K154, K155, K156, K157,       K158, K159, K160\
) { \
{ KC_##K1,   KC_##K2,   KC_##K3,   KC_##K4,   KC_##K5,   KC_##K6,   KC_##K7,   KC_##K8   }, \
{ KC_##K9,   KC_##K10,  KC_##K11,  KC_##K12,  KC_##K13,  KC_##K14,  KC_##K15,  KC_##K16  }, \
{ KC_##K17,  KC_##K18,  KC_##K19,  KC_##K20,  KC_##K21,  KC_##K22,  KC_##K23,  KC_##K24  }, \
{ KC_##K25,  KC_##K26,  KC_##K27,  KC_##K28,  KC_##K29,  KC_##K30,  KC_##K31,  KC_##K32  }, \
{ KC_##K33,  KC_##K34,  KC_##K35,  KC_##K36,  KC_##K37,  KC_##K38,  KC_##K39,  KC_##K40  }, \
{ KC_##K41,  KC_##K42,  KC_##K43,  KC_##K44,  KC_##K45,  KC_##K46,  KC_##K47,  KC_##K48  }, \
{ KC_##K49,  KC_##K50,  KC_##K51,  KC_##K52,  KC_##K53,  KC_##K54,  KC_##K55,  KC_##K56  }, \
{ KC_##K57,  KC_##K58,  KC_##K59,  KC_##K60,  KC_##K61,  KC_##K62,  KC_##K63,  KC_##K64  }, \
{ KC_##K65,  KC_##K66,  KC_##K67,  KC_##K68,  KC_##K69,  KC_##K70,  KC_##K71,  KC_##K72  }, \
{ KC_##K73,  KC_##K74,  KC_##K75,  KC_##K76,  KC_##K77,  KC_##K78,  KC_##K79,  KC_##K80  }, \
{ KC_##K81,  KC_##K82,  KC_##K83,  KC_##K84,  KC_##K85,  KC_##K86,  KC_##K87,  KC_##K88  }, \
{ KC_##K89,  KC_##K90,  KC_##K91,  KC_##K92,  KC_##K93,  KC_##K94,  KC_##K95,  KC_##K96  }, \
{ KC_##K97,  KC_##K98,  KC_##K99,  KC_##K100, KC_##K101, KC_##K102, KC_##K103, KC_##K104 }, \
{ KC_##K105, KC_##K106, KC_##K107, KC_##K108, KC_##K109, KC_##K110, KC_##K111, KC_##K112 }, \
{ KC_##K113, KC_##K114, KC_##K115, KC_##K116, KC_##K117, KC_##K118, KC_##K119, KC_##K120 }, \
{ KC_##K121, KC_##K122, KC_##K123, KC_##K124, KC_##K125, KC_##K126, KC_##K127, KC_##K128 }, \
{ KC_##K129, KC_##K130, KC_##K131, KC_##K132, KC_##K133, KC_##K134, KC_##K135, KC_##K136 }, \
{ KC_##K137, KC_##K138, KC_##K139, KC_##K140, KC_##K141, KC_##K142, KC_##K143, KC_##K144 }, \
{ KC_##K145, KC_##K146, KC_##K147, KC_##K148, KC_##K149, KC_##K150, KC_##K151, KC_##K152 }, \
{ KC_##K153, KC_##K154, KC_##K155, KC_##K156, KC_##K157, KC_##K158, KC_##K159, KC_##K160 }  \
}
