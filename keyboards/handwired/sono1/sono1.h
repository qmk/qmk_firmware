/* Copyright 2020 DmNosachev
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

#define XXX KC_NO

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

/*
,---------------------------------------------------------------------------------------------------------,  ,-----,
|  <  |  |NumLk|  |  f1  |  f2  |  f3  |  f4  |  f5  |   |  f6  |  f7  |  f8  |  f9  | f10  | |RlUp |RlDn |  |CurLk|
|-------------------------------------------------------------------------------------------| |-----------|  |-----|-----------------,
| Esc  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  | = - |  ^  |  ^  |  BS  | |Home |Help |  |  *  |  /  |  -  |  +  |
|-------------------------------------------------------------------------------------------| |-----------|  |-----------------------|
|  Tab  |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  | ~@  | {[  |   Return  | | Ins | Del |  |  7  |  8  |  9  |  =  |
|--------------------------------------------------------------------------------|          | `-----------'  |-----------------------|
|  Ctrl  |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  | +;  | *:  | }]  |          | |    Up     |  |  4  |  5  |  6  |  .  |
|--------------------------------------------------------------------------------`----------' |-----------|  |-----------------------|
|   Shift  |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  | ?/  | --  |    Shift     | |Left |Right|  |  1  |  2  |  3  |  ,  |
|-------------------------------------------------------------------------------------------| |-----------|  |-----------------------|
|Caps | Opt |Kana | Cmd |   Space1    |    Space2   |    Space3       | Enter |       | Alt | |   Down    |  |  0  | 000 |   Enter   |
`-------------------------------------------------------------------------------------------' `-----------'  '-----------------------'
                               |Thumb1|Thumb2|
                               `-------------'
*/
#define LAYOUT( \
    K00,   K01,   K02,  K03,  K04,  K05,  K06,     K07,  K10,  K11,  K12,  K13,  K97, KA0,   KD6, \
    K14,  K15, K16, K17, K20, K21, K22, K23, K24, K25, K26, K27, K30, K31, K74,  KA1, KA2,   KC0, KD0, KE0, KC1, \
    K75,   K32, K33, K34, K35, K36, K37, K40, K41, K42, K43, K44, K45,     K76,  KA3, KA4,   KD1, KE1, KC2, KD2, \
    K77,    K47, K50, K51, K52, K53, K54, K55, K56, K57, K60, K80, K81,            KB0,      KE2, KC3, KD3, KE3, \
    K82,     K61, K62, K63, K64, K65, K66, K67, K70, K71, K72, K73, K83,         KB1, KB2,   KC4, KD4, KE4, KC5,\
    K84,  K85,  K86,  K87,      K90,      K91,      K92,     K93,   K94,           KB3,      KD5, KE5,   KC6, \
                                K95, K96 \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07 }, \
    { K10, K11, K12, K13, K14, K15, K16, K17 }, \
    { K20, K21, K22, K23, K24, K25, K26, K27 }, \
    { K30, K31, K32, K33, K34, K35, K36, K37 }, \
    { K40, K41, K42, K43, K44, K45, XXX, K47 }, \
    { K50, K51, K52, K53, K54, K55, K56, K57 }, \
    { K60, K61, K62, K63, K64, K65, K66, K67 }, \
    { K70, K71, K72, K73, K74, K75, K76, K77 }, \
    { K80, K81, K82, K83, K84, K85, K86, K87 }, \
    { K90, K91, K92, K93, K94, K95, K96, K97 }, \
    { KA0, KA1, KA2, KA3, KA4, XXX, XXX, XXX }, \
    { KB0, KB1, KB2, KB3, XXX, XXX, XXX, XXX }, \
    { KC0, KC1, KC2, KC3, KC4, KC5, KC6, XXX }, \
    { KD0, KD1, KD2, KD3, KD4, KD5, KD6, XXX }, \
    { KE0, KE1, KE2, KE3, KE4, KE5, XXX, XXX } \
}

#define LAYOUT_debug( \
    K00, K01, K02, K03, K04, K05, K06, K07, \
    K10, K11, K12, K13, K14, K15, K16, K17, \
    K20, K21, K22, K23, K24, K25, K26, K27, \
    K30, K31, K32, K33, K34, K35, K36, K37, \
    K40, K41, K42, K43, K44, K45, K46, K47, \
    K50, K51, K52, K53, K54, K55, K56, K57, \
    K60, K61, K62, K63, K64, K65, K66, K67, \
    K70, K71, K72, K73, K74, K75, K76, K77, \
    K80, K81, K82, K83, K84, K85, K86, K87, \
    K90, K91, K92, K93, K94, K95, K96, K97, \
    KA0, KA1, KA2, KA3, KA4, KA5, KA6, KA7, \
    KB0, KB1, KB2, KB3, KB4, KB5, KB6, KB7, \
    KC0, KC1, KC2, KC3, KC4, KC5, KC6, KC7, \
    KD0, KD1, KD2, KD3, KD4, KD5, KD6, KD7, \
    KE0, KE1, KE2, KE3, KE4, KE5, KE6, KE7  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07 }, \
    { K10, K11, K12, K13, K14, K15, K16, K17 }, \
    { K20, K21, K22, K23, K24, K25, K26, K27 }, \
    { K30, K31, K32, K33, K34, K35, K36, K37 }, \
    { K40, K41, K42, K43, K44, K45, K46, K47 }, \
    { K50, K51, K52, K53, K54, K55, K56, K57 }, \
    { K60, K61, K62, K63, K64, K65, K66, K67 }, \
    { K70, K71, K72, K73, K74, K75, K76, K77 }, \
    { K80, K81, K82, K83, K84, K85, K86, K87 }, \
    { K90, K91, K92, K93, K94, K95, K96, K97 }, \
    { KA0, KA1, KA2, KA3, KA4, KA5, KA6, KA7 }, \
    { KB0, KB1, KB2, KB3, KB4, KB5, KB6, KB7 }, \
    { KC0, KC1, KC2, KC3, KC4, KC5, KC6, KC7 }, \
    { KD0, KD1, KD2, KD3, KD4, KD5, KD6, KD7 }, \
    { KE0, KE1, KE2, KE3, KE4, KE5, KE6, KE7 } \
}
