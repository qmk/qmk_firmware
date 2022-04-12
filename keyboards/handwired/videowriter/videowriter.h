/* Copyright 2019 DmNosachev
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

/* 
 * ,---------------------------------------------------------------------------------------.
 * |   ,----------------.  ,-----------------------.  ,--------------.          | up |     |
 * |   |menu|print|spell|  |page|center|split|find |  |copy|move|goto|     |left|down|right|
 * |---------------------------------------------------------------------------------------|
 * |del|  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  = |   BSp| do  |
 * |---------------------------------------------------------------------------------------|
 * |Tab  |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |   | help|
 * |-----------------------------------------------------------------------------'   |-----|
 * |Caps  |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  "  | return | undo|
 * |---------------------------------------------------------------------------------------|
 * |  Shift  |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  <  |  >  |  ?  |   Shift   |     |
 * '---------------------------------------------------------------------------------------'
 *        | style|                     Space                         | insert|             
 *        '------------------------------------------------------------------'
 */
 
#define LAYOUT( \
	K17, K16, K15,      K14, K13, K12, K11,    K10, K27, K26,   K80, K97, K81, K96, \
	K25, K24, K23, K22, K21, K20, K37, K36, K35, K34, K33, K32, K31, K30, K95, \
	K47, K46, K45, K44, K43, K42, K41, K40, K57, K56, K55, K54, K53,      K94, \
	K07, K51, K50, K67, K66, K65, K64, K63, K62, K61, K60, K77,      K52, K93, \
	K06, K76, K75, K74, K73, K72, K71, K70, K87, K86, K85, K92, \
	K84,                     K83,                          K82 \
) \
{ \
	{ XXX, XXX, XXX, XXX, XXX, XXX, K06, K07 }, \
	{ K10, K11, K12, K13, K14, K15, K16, K17 }, \
	{ K20, K21, K22, K23, K24, K25, K26, K27 }, \
	{ K30, K31, K32, K33, K34, K35, K36, K37 }, \
	{ K40, K41, K42, K43, K44, K45, K46, K47 }, \
	{ K50, K51, K52, K53, K54, K55, K56, K57 }, \
	{ K60, K61, K62, K63, K64, K65, K66, K67 }, \
	{ K70, K71, K72, K73, K74, K75, K76, K77 }, \
	{ K80, K81, K82, K83, K84, K85, K86, K87 }, \
	{ XXX, XXX, K92, K93, K94, K95, K96, K97 }  \
}
