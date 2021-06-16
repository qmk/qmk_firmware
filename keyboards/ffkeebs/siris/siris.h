/*
Copyright 2021 Swiftrax <swiftrax@gmail.com>

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

// readability
#define XXX KC_NO

#define LAYOUT( \
	K00, K01, K02, K03, K04, K05,		K06, K07, K08, K09, K0A, K0B, \
    K10, K11, K12, K13, K14, K15,		K16, K17, K18, K19, K1A, K1B, \
    K20, K21, K22, K23, K24, K25,		K26, K27, K28, K29, K2A, K2B, \
    K30, K31, K32, K33, K34, K35,		K36, K37, K38, K39, K3A, K3B, \
    		  K42, K43, K44, K45,		K46, K47, K48, K49  		  \
) { \
	{ K00, K01, K02, K03, K04, K05,		K06, K07, K08, K09, K0A, K0B }, \
	{ K10, K11, K12, K13, K14, K15,		K16, K17, K18, K19, K1A, K1B }, \
	{ K20, K21, K22, K23, K24, K25,		K26, K27, K28, K29, K2A, K2B }, \
	{ K30, K31, K32, K33, K34, K35,		K36, K37, K38, K39, K3A, K3B }, \
	{ XXX, XXX, K42, K43, K44, K45,		K46, K47, K48, K49, XXX, XXX }  \
}
