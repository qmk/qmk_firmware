/* Copyright 2019 Yiancar
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

#define XXX KC_NO
#include "quantum.h"

#define KEYMAP( \
	K000,  K001,  K002,  K003,  K004,  K005, \
	K100,  K101,  K102,  K103,  K104,  K105, \
	K200,  K201,  K202,  K203,  K204,  K205, \
	K300,  K301,  K302,  K303,  K304,  K305, \
	K400,  K401,  K402,  K403,  K404,  K405, \
	K500,  K501,  K502,  K503,  K504,  K505, \
	K600,  K601,  K602,  K603,  K604,  K605, \
	K700,  K701,  K702,  K703,  K704,  K705, \
	K800,  K801,  K802,  K803,  K804,  K805, \
	K900,  K901,  K902,  K903,  K904,  K905  \
) { \
    { K001, K003, K005, K101, K103, K105},\
    { K000, K002, K004, K100, K102, K104},\
    { K200, K202, K204, K300, K302, K304},\
    { K201, K203, K205, K301, K303, K305},\
    { K401, K403, K405, K501, K503, K505},\
    { K400, K402, K404, K500, K502, K504},\
    { K600, K602, K604, K700, K702, K704},\
    { K601, K603, K605, K701, K703, K705},\
    { K801, K803, K900, K901, K903, K905},\
    { K800, K802, K804, K805, K902, K904}\
}

#define LED_RED C5
#define LED_GREEN C4

#define LAYOUT_preonic_grid  KEYMAP //preonic keymap compatibility
#define LAYOUT KEYMAP //jj50 keymap compatibility

