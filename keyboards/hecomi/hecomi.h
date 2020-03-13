/* Copyright 2018 takashiski
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

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */



/*
Left hand :
7
7
6
6
6

32

Right hand:

8
8
7
8
6

37
*/

#define LAYOUT(\
	K00, K01, K02, K03, K04, K05, K06,        K50, K51, K52, K53, K54, K55, K56, K57, \
	K10,   K11, K12, K13, K14, K15, K16,    K60, K61, K62, K63, K64, K65, K66,   K67, \
	K20,    K21, K22, K23, K24, K25,          K71, K72, K73, K74, K75, K76,      K77,\
	K30,     K31, K32, K33, K34, K35,      K80, K81, K82, K83, K84, K85, K86,    K87, \
	K40,  K41, K42, K43, K44, K45,        K92, K93, K94, K95, K96, K97\
) {\
	{K00, K01, K02, K03, K04, K05, K06, KC_NO},\
	{K10, K11, K12, K13, K14, K15, K16, KC_NO},\
	{K20, K21, K22, K23, K24, K25, KC_NO,    KC_NO},\
	{K30, K31, K32, K33, K34, K35, KC_NO,    KC_NO},\
	{K40, K41, K42, K43, K44, K45, KC_NO,    KC_NO},\
	{K50, K51, K52, K53, K54, K55, K56, K57},\
	{K60, K61, K62, K63, K64, K65, K66, K67},\
	{KC_NO,    K71, K72, K73, K74, K75, K76, K77},\
	{K80, K81, K82, K83, K84, K85, K86, K87},\
	{KC_NO,    KC_NO,    K92, K93, K94, K95, K96, K97}\
}

#define LAYOUT_kc(\
K00, K01, K02, K03, K04, K05, K06,        K50, K51, K52, K53, K54, K55, K56, K57, \
K10,   K11, K12, K13, K14, K15, K16,    K60, K61, K62, K63, K64, K65, K66,   K67, \
K20,    K21, K22, K23, K24, K25,          K71, K72, K73, K74, K75, K76,      K77,\
K30,     K31, K32, K33, K34, K35,      K80, K81, K82, K83, K84, K85, K86,    K87, \
    K40,  K41, K42, K43, K44, K45,        K92, K93, K94, K95, K96, K97\
) {\
{KC_##K00, KC_##K01, KC_##K02, KC_##K03, KC_##K04, KC_##K05, KC_##K06, KC_NO},\
{KC_##K10, KC_##K11, KC_##K12, KC_##K13, KC_##K14, KC_##K15, KC_##K16, KC_NO},\
{KC_##K20, KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_NO,    KC_NO},\
{KC_##K30, KC_##K31, KC_##K32, KC_##K33, KC_##K34, KC_##K35, KC_NO,    KC_NO},\
{KC_##K40, KC_##K41, KC_##K42, KC_##K43, KC_##K44, KC_##K45, KC_NO,    KC_NO},\
{KC_##K50, KC_##K51, KC_##K52, KC_##K53, KC_##K54, KC_##K55, KC_##K56, KC_##K57},\
{KC_##K60, KC_##K61, KC_##K62, KC_##K63, KC_##K64, KC_##K65, KC_##K66, KC_##K67},\
{KC_NO,    KC_##K71, KC_##K72, KC_##K73, KC_##K74, KC_##K75, KC_##K76, KC_##K77},\
{KC_##K80, KC_##K81, KC_##K82, KC_##K83, KC_##K84, KC_##K85, KC_##K86, KC_##K87},\
{KC_NO,    KC_NO,    KC_##K92, KC_##K93, KC_##K94, KC_##K95, KC_##K96, KC_##K97}\
}

