/* Copyright 2021 Altain
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


/* This section is to help viewers visually clarify the physical layout of Blaster 75 PCB. 

ANSI Layout : 
 * ,----------------------------------------------------------------
 * | ESC| F1| F2| F3| F4| F5| F6| F7| F8| F9| F10| F11| F12|PSC|INS|
 * ,---------------------------------------------------------------|
 * | ` |1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | + | BKSPC |HOME|
 * |---------------------------------------------------------------|
 * | TAB | Q | W | E | R | T | Y | U | I | O | P | [ | ] |  \ | DEL|
 * |---------------------------------------------------------------|
 * | CTRL  | A | S | D | F | G | H | J | K | L | ; | ' | ENTER| END|
 * |---------------------------------------------------------------|
 * | LSHIFT | Z | X | C | V | B | N | M | , | . | / |RSHFT | ↑ |   |
 * |---------------------------------------------------------------|
 * |LCTL|LWIN|LALT|       6.25U SPACE       |RALT|RCTL|  ← | ↓ | → |
 * `----------------------------------------------------------------
 * 
 * 


7U Spacebar Layout : 
 * ,----------------------------------------------------------------
 * | ESC| F1| F2| F3| F4| F5| F6| F7| F8| F9| F10| F11| F12|PSC|INS|
 * ,---------------------------------------------------------------|
 * | ` |1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | + | BKSPC |HOME|
 * |---------------------------------------------------------------|
 * | TAB | Q | W | E | R | T | Y | U | I | O | P | [ | ] |  \ | DEL|
 * |---------------------------------------------------------------|
 * | CTRL  | A | S | D | F | G | H | J | K | L | ; | ' | ENTER| END|
 * |---------------------------------------------------------------|
 * | LSHIFT | Z | X | C | V | B | N | M | , | . | / |RSHFT | ↑ |   |
 * |---------------------------------------------------------------|
 * | LCTL |LWIN| LALT |        7U SPACE        | RCTL |  ← | ↓ | → |
 * `----------------------------------------------------------------
 * 
 * */

#define XXX KC_NO

// BLASTER75 DEFAULT ANSI LAYOUT
// 6.25U SPACEBAR
// BOTTOM ROW 1.25 , 1.25 , 1.25 , 6.25 , 1.25 , 1.25 CONFIGURATION
#define LAYOUT( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, \
	K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E, \
	K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C,      K3E, \
	K40, K41, K42, K43, K44, K45, K46, K47, K48, K49,      K4B, K4C, K4D,      \
	K50, K51, K52,           K55,                K59,      K5B, K5C, K5D, K5E  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, XXX, K3E }, \
    { K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, XXX, K4B, K4C, K4D, XXX }, \
    { K50, K51, K52, XXX, XXX, K55, XXX, XXX, XXX, K59, XXX, K5B, K5C, K5D, K5E }  \
}

// BLASTER75 7U LAYOUT
// 7U SPACEBAR
// BOTTOM ROW 1.5 , 1 , 1.5 , 7 , 1.5 CONFIGURATION
#define LAYOUT_7u( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, \
	K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E, \
	K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C,      K3E, \
	K40, K41, K42, K43, K44, K45, K46, K47, K48, K49,      K4B, K4C, K4D,      \
	K50, K51, K52,           K55,                          K5B, K5C, K5D, K5E  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E }, \
    { K20, XXX, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E }, \
    { K30, XXX, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, XXX, K3E }, \
    { K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, XXX, K4B, K4C, K4D, XXX }, \
    { K50, K51, K52, XXX, XXX, K55, XXX, XXX, XXX, XXX, XXX, K5B, K5C, K5D, K5E }  \
}
